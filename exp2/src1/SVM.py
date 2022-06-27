from asyncio import constants
import numpy as np
import cvxpy as cvx

class SupportVectorMachine:
    def __init__(self, C=1, kernel='Linear', epsilon=1e-4):
        self.C = C
        self.epsilon = epsilon
        self.kernel = kernel
        self.SV_alpha = None
        self.SV_b = None
        self.SV = None
        self.SV_label = None
        # Hint: 你可以在训练后保存这些参数用于预测
        # SV即Support Vector，表示支持向量，SV_alpha为优化问题解出的alpha值，
        # SV_label表示支持向量样本的标签。
    
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
        '''
        TODO：实现软间隔SVM训练算法
        train_data：训练数据，是(N, 7)的numpy二维数组，每一行为一个样本
        train_label：训练数据标签，是(N,)的numpy数组，和train_data按行对应
        '''
        N = train_data.shape[0]
        P = np.zeros((N,N))
        temp = train_data
        for i in range(N):
            for j in range(N):
                P[i][j] = self.KERNEL(temp[i],temp[j])*train_label[i]*train_label[j]
        result = cvx.Variable((N,1))
        #print(result.shape[0])
        G1 = np.eye(N,dtype = int)
        G2 = np.eye(N,dtype = int)
        G2 = -1*G2
        G = np.r_[G1,G2]
        #print(G.shape[0],G.shape[1])
        #print(G)
        # 构造h
        h1 = np.zeros((N,1))
        for i in range(N):
            h1[i] = self.C
        h2 = np.zeros((N,1))
        h = np.r_[h1,h2]
        #print(h.shape[0],h.shape[1])
        # 构造A
        A = train_label.reshape(1,N) 
        #print(A)
        b = np.zeros((1,1))
        #print(b)
        constraints = [G@result <= h,A@result == b]
        obj = cvx.Minimize(cvx.quad_form(result,P)/2.0 - cvx.sum(result))
        prob = cvx.Problem(obj, constraints)
        print("no problem")
        prob.solve(solver='ECOS')
        print("no problem")
        #print("status:", prob.status)
        #print("optimal value ", prob.value)
        #print("optimal var", result.value)
        self.SV_alpha = np.array(result.value)
        #print("alpha = ",self.SV_alpha)
        accurate = np.where(self.SV_alpha > self.epsilon)[0]
        self.SV = np.array([train_data[i] for i in accurate])
        self.SV_label = np.array([train_label[i] for i in accurate])
        #print(self.SV)
        #print(self.SV_label)
        self.SV_b = np.mean(
            [train_label[i] - 
            sum([train_label[i] * self.SV_alpha[i] * self.KERNEL(x, train_data[i]) 
            for x in train_data[accurate]]) 
            for i in accurate])

    def predict(self, test_data):
        '''
        TODO：实现软间隔SVM预测算法
        train_data：测试数据，是(M, 7)的numpy二维数组，每一行为一个样本
        必须返回一个(M,)的numpy数组，对应每个输入预测的标签，取值为1或-1表示正负例
        '''
        M = test_data.shape[0]
        count = self.SV.shape[0]
        print(count)
        predictions = []
        prediction = self.SV_b
        for j in range(M):
            prediction = self.SV_b +  sum([self.SV_label[i] * self.SV_alpha[i] * self.KERNEL(test_data[j], self.SV[i]) for i in range(count)])
            if prediction > 0:
                predictions.append(1)
            else:
                predictions.append(-1)
        prediction = np.array(predictions).reshape(M,1)
        return predictions
