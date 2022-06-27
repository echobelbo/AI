from cProfile import label
from pickletools import optimize
import torch
import torch.nn as nn
import numpy as np
import torch.nn.functional as F
from matplotlib import pyplot as plt
class pytorch_MLP(nn.Module):
    def __init__(self):
        super(pytorch_MLP,self).__init__()
        ########################################################################
        #这里需要写MyNet的卷积层、池化层和全连接层
        self.fc1 = nn.Linear(10, 10)
        self.fc2 = nn.Linear(10, 8)
        self.fc3 = nn.Linear(8, 8)
        self.fc4 = nn.Linear(8, 4)

    def forward(self, x):
        ########################################################################
        #这里需要写MyNet的前向传播
        # print(x)
        x = F.tanh(self.fc1(x))
        x = F.tanh(self.fc2(x))
        x = F.tanh(self.fc3(x))
        # x = F.softmax(self.fc4(x))
        return self.fc4(x)   
class MLP():
    def __init__(self):
        # layer size = [10, 8, 8, 4]
        # 初始化所需参数
        self.x = np.zeros((1,10))
        self.W1 = np.random.uniform(0, 0.3, (10, 10))
        self.b1 = np.random.uniform(0, 0.3, (1,10))
        self.W2 = np.random.uniform(0, 0.3, (10, 8))
        self.b2 = np.random.uniform(0, 0.3, (1,8))
        self.W3 = np.random.uniform(0, 0.3, (8, 8))
        self.b3 = np.random.uniform(0, 0.3, (1,8))
        self.W4 = np.random.uniform(0, 0.3, (8, 4))
        self.b4 = np.random.uniform(0, 0.3, (1,4))
        # temp = np.zeros(4)
        self.u1 = np.zeros((1,10))
        self.u2 = np.zeros((1,8))
        self.u3 = np.zeros((1,8))
        self.u4 = np.zeros((1,4))

        self.y1 = np.zeros((1,10))
        self.y2 = np.zeros((1,8))
        self.y3 = np.zeros((1,8))
        self.y4 = np.zeros((1,4))
        self.loss = 0.0
        self.loss_torch = 0.0
        # self.y =  np.exp(temp) / np.sum(np.exp(temp)) 

        pass

    def forward(self, x):
        # 前向传播
        self.x = x.reshape((1,10))
        # print(self.x)
        self.u1 = self.x@self.W1 + self.b1
        # print(self.u1)
        self.y1 = np.tanh(self.u1)
        # print(self.y1)
        # print(self.)
        self.u2 = self.y1@self.W2 + self.b2
        # print(self.u2)
        self.y2 = np.tanh(self.u2)
        self.u3 = self.y2@self.W3 + self.b3
        self.y3 = np.tanh(self.u3)
        self.u4 = self.y3@self.W4 + self.b4
        # print(self.u4)
        self.y4 = np.exp(self.u4) / np.sum(np.exp(self.u4))
        # print(self.y4)
        pass

    def backward(self, labels, lr): # 自行确定参数表
        self.loss = CrossEntropyLoss_my(self.y4, labels)
        # print("IN")
        # print(self.b1, self.b2, self.b3, self.b4)
        # print(self.W1, self.W2, self.W3, self.W4)
        # print (self.loss)
        delta4 = self.y4-labels
        self.b4 = self.b4 - lr * delta4
        # print(self.y3, delta4)
        dW4 = lr * (self.y3.T @ delta4)
        delta3 = (delta4 @ self.W4.T) * (1-self.y3*self.y3)
        self.b3 = self.b3 - lr * delta3
        dW3 = lr * (self.y2.T @ delta3)
        delta2 = (delta3 @ self.W3.T) * (1-self.y2*self.y2)
        self.b2 = self.b2 - lr * delta2
        dW2 = lr * (self.y1.T @ delta2)
        delta1 = (delta2 @ self.W2.T) * (1-self.y1*self.y1)
        # print(delta1, delta2, delta3, delta4)
        self.b1 = self.b1 - lr * delta1
        dW1 = lr * (self.x.T @ delta1)
        self.W1 -= dW1
        self.W2 -= dW2
        self.W3 -= dW3
        self.W4 -= dW4
        # print(self.b1, self.b2, self.b3, self.b4)
        # print(self.W1, self.W2, self.W3, self.W4)
        # print("OUT")
        # 反向传播
        pass
    
    # def backward_torch(self, labels, lr):

    #     # My_loss = torch.nn.CrossEntropyLoss()
    #     # LOSS = My_loss(torch.tensor(self.y4.T).float(), torch.tensor(labels.T).float())
    #     # print(self.y4, labels)
    #     # optimizeer = torch.optim.Adam(self.parameters(), )
    #     output = torch.log(torch.tensor(self.y4).float())
    #     labels_ = torch.tensor(labels).reshape(4,1).float()
    #     # print(output.shape[1], labels_.shape[1])
    #     # print(output, labels)
    #     # print("123")
    #     # print(torch.mm(output, labels_))
    #     LOSS = -torch.tensor(torch.mm(output, labels_), requires_grad = True)
    #     # print(LOSS)
    #     LOSS.backward()
    #     self.loss_torch = LOSS.data.sum().item()
    #     # print(self.loss_torch)
        
def CrossEntropyLoss_my(y, labels):
    return -np.dot(np.log(y), labels)

def train(mlp: MLP, epochs, lr, inputs, labels):
    '''
        mlp: 传入实例化的MLP模型
        epochs: 训练轮数
        lr: 学习率
        inputs: 生成的随机数据
        labels: 生成的one-hot标签
    '''
    Loss = []
    for epoch in range(epochs):
        loss = 0
        # loss_torch = 0
        for i in range(inputs.shape[0]):
            mlp.forward(inputs[i, :])
            mlp.backward(labels[i, :], lr)
            # mlp.backward_torch(labels[i, :], lr)
            loss += mlp.loss
            # loss_torch += mlp.loss_torch
            # print(loss_torch)
        Loss.append(loss/inputs.shape[0])
        # Loss_torch.append(loss_torch/inputs.shape[0])
    return Loss

def pytorch_train(net, train_loader, labels, epochs, optimizer, loss_function):
    # train_loader = torch.tensor(train_loader).float
    # labels = torch.tensor(labels)
    net.train()
    result = []
    for epoch in range(epochs):
        optimizer.zero_grad()
        # print(train_loader)
        outputs = net.forward(train_loader)
        loss = loss_function(outputs, labels)
        result.append(loss.item())
        loss.backward()
        optimizer.step()
    return result
if __name__ == '__main__':
    # 设置随机种子,保证结果的可复现性
    np.random.seed(1)
    mlp = MLP()
    # 生成数据
    inputs = np.random.randn(100, 10)

    # 生成one-hot标签
    labels = np.eye(4)[np.random.randint(0, 4, size=(1, 100))].reshape(100, 4)

    # 训练
    
    epochs = 1000
    lr = 0.02
    net = pytorch_MLP()
    l = train(mlp, epochs, lr, inputs, labels)
    optimizer = torch.optim.Adam(net.parameters(),lr)
    loss_function = nn.CrossEntropyLoss()
    torch_l = pytorch_train(net, torch.from_numpy(inputs).float(), torch.from_numpy(labels), epochs, optimizer, loss_function)
    # print(mlp.W1)
    # for i in range(len(l)):
    #     print(i, l[i], torch_l[i])
    fig, ax = plt.subplots()
    ax.plot(np.array(l), color='red')
    ax.plot(np.array(torch_l), color='blue')
    plt.show()