from tabnanny import verbose
import numpy as np
import cvxpy as cvx

class SupportVectorMachine:
    def __init__(self, C=1, kernel='Linear', epsilon=1e-4):
        self.C = C
        self.epsilon = epsilon
        self.kernel = kernel

        # Hint: 你可以在训练后保存这些参数用于预测
        # SV即Support Vector，表示支持向量，SV_alpha为优化问题解出的alpha值，
        # SV_label表示支持向量样本的标签。
        self.SV = None
        self.SV_alpha = None
        self.SV_label = None
        self.SV_b = None

    def KERNEL(self, x1, x2, d=2, sigma=1):
        #d for Poly, sigma for Gauss
        if self.kernel == 'Gauss':
            K = np.exp(-(np.sum((x1 - x2) ** 2)) / (2 * sigma ** 2))
        elif self.kernel == 'Linear':
            K = np.dot(x1,x2)
        elif self.kernel == 'Poly':
            K = (np.dot(x1,x2) + 1) ** d
        else:
            raise NotImplementedError()
        return K
    
    def fit(self, train_data, train_label):
        # '''
        # TODO：实现软间隔SVM训练算法
        # train_data：训练数据，是(N, 7)的numpy二维数组，每一行为一个样本
        # train_label：训练数据标签，是(N,)的numpy数组，和train_data按行对应
        # '''
        
        print (cvx.__version__)
        data_count = train_data.shape[0]
        # print(data_count)
        #计算kernel
        Kernel = np.empty((data_count, data_count))
        for i in range(data_count):
            for j in range(data_count):
                Kernel[i][j] = self.KERNEL(train_data[i], train_data[j]) * train_label[i] * train_label[j]
        Alpha = cvx.Variable((data_count,1))
        obj = cvx.Maximize(-cvx.quad_form(Alpha, Kernel)/2.0 + cvx.sum(Alpha))
        constraints = [train_label.reshape(1,data_count) @ Alpha == 0, Alpha <= self.C, Alpha >= 0] 
        print("no problem")
        cvx.Problem(obj, constraints).solve(solver = cvx.ECOS)
        print("no problem")
        temp_result = np.array(Alpha.value)
        print("no problem")
        self.SV_alpha = np.where(temp_result < self.epsilon, 0, temp_result)
        print("no problem")
        acc = np.where((self.SV_alpha > 0) & (self.SV_alpha < self.C))[0]
        self.SV = np.array([train_data[i] for i in acc])
        self.SV_label = np.array([train_label[i] for i in acc])
        self.SV_b = np.mean(
            [train_label[i] - 
            sum([train_label[i] * self.SV_alpha[i] * self.KERNEL(x, train_data[i]) 
            for x in train_data[acc]]) for i in acc])



    def predict(self, test_data):
        # '''
        # TODO：实现软间隔SVM预测算法
        # train_data：测试数据，是(M, 7)的numpy二维数组，每一行为一个样本
        # 必须返回一个(M,)的numpy数组，对应每个输入预测的标签，取值为1或-1表示正负例
        # '''
        data_count = test_data.shape[0]
        acc_count = self.SV.shape[0]
        print(acc_count)
        result = []
        for j in range (data_count):
            # print(j)
            pred = self.SV_b
            # print(pred)
            for i in range(acc_count):
                # print(self.SV_label, self.SV_alpha, self.SV)
                pred += self.SV_label[i] * self.KERNEL(test_data[j], self.SV[i]) * self.SV_alpha[i] * self.SV_label[i]
            if pred > 0:
                result.append(1)
            else:
                result.append(-1)
        np.array(result).reshape(data_count,1)
        return result
