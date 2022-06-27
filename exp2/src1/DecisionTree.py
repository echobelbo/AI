from math import log2
from operator import index
from re import A
import numpy as np

class Node(object):
    value = None
    children = []
    item = None
    num = None
    #表示节点类型，0为叶节点，1为其他节点

    def __init__(self, val, item, num):
        self.setValue(val)
        self.children = []
        self.setItem(item)
        self.num = num
    
    def setValue(self, val):
        self.value = val

    def setItem(self, item):
        self.item = item

class valueCount:
    def __init__(self) -> None:
        self.count = np.array([0,0,0,0,0,0,0,0,0,0,0])
        self.value_list = []
        for i in range (11):
            self.value_list.append([])




def value_count(value_mat, index):
    valuecount = valueCount()
    length = value_mat.shape[0]
    for i in range(length):
        flag = value_mat[i, index]
        # flag.astype('int64')
        valuecount.count[flag] += 1
        valuecount.value_list[flag].append(i)
    return valuecount
        
def value_count_1di(value_mat):
    valuecount = valueCount()
    # print("value_count_1diIN")
    # print(value_mat)
    length = value_mat.shape[0]
    for i in range(length):
        flag = value_mat[i]
        # flag.astype('int64')
        # print(valuecount.count[flag])
        valuecount.count[flag] += 1
        valuecount.value_list[flag].append(i)
    # print("value_count_1diOUT")
    return valuecount

def calEnt(features, labels):
    # print("calEnt IN")
    data_count = features.shape[0]
    # features_count = features.shape[1]
    # for i in range(0,features_count-1):
    valuecount = value_count_1di(labels)
    # print(valuecount.count)
    p = valuecount.count/data_count
    # print(p)
    # print(p)
    #ent = (-p*np.log2(p)).sum()
    ent = 0
    for i in range(11):
        if p[i] > 0:
            ent += -p[i]*log2(p[i])
    # print("calEnt OUT")
    # print(ent)
    return ent

def bestSplit(features, labels):
    # print("bestSplitin\n")
    # print("labels=", labels)
    baseEnt = calEnt(features, labels)
    # print("baseEnt cal end")
    # print(baseEnt)
    bestGain = 0
    axis = -1
    data_count = features.shape[0]
    for i in range(features.shape[1]):
        # print("value_countIN\n")
        # print(features, i)
        valuecount=value_count(features, i)
        # print(valuecount.value_list, "!!!!!!!!!")

        ents = 0
        for j in valuecount.value_list:
            # chil_features = features[features.iloc[:, i] == j]
            # chil_lables = lables[features.iloc[:, i] == j]
            # ent = calEnt(chil_features, chil_lables)
            # ents += (chil_features.shape[0] / data_count) * ent
            length = len(j)
            if length == 0:
                continue
            chil_features = np.empty((length, features.shape[1]), dtype=np.int64)
            chil_labels = np.empty(length, dtype=np.int64)
            for k in range(length):
                # print(k)
                # print(features[k, :])
                chil_features[k, :] = features[j[k], :]
                # print(chil_features)
                chil_labels[k] = labels[j[k]]
            # chil_features.reshape((features.shape[1], length))
            # print(j, chil_features, chil_labels)
            # print("start",chil_features, chil_labels)
            ent = calEnt(chil_features, chil_labels)
            # print(ent, "end")
            ents += (chil_features.shape[0] / data_count) * ent

        # print(baseEnt)
        infoGain = baseEnt - ents
        # print(infoGain)
        if(infoGain >= bestGain):
            bestGain = infoGain
            axis = i
    # print("bestSplitOUT\n")
    # print(bestGain)
    return axis


def mySplit(features, labels, axis, value):
    
    # re_features = features.loc[features[col] == value, :].drop(col, axis = 1)
    # re_lables = labels.loc[features[col]== value, :]
    # print(features, labels, axis, value)
    re_features1 = np.delete(features, axis, 1)
    # print(re_features1)
    data_count = re_features1.shape[0]
    index = []
    for i in range(data_count):
        if(features[i, axis] == value):
            index.append(i)
    re_labels = np.empty(len(index), dtype=np.int64)
    re_features2 = np.empty((len(index), re_features1.shape[1]), dtype=np.int64)
    # print(re_features2)
    for i in range(len(index)):
        re_labels[i] = labels[index[i]]
        re_features2[i] = re_features1[index[i]]
    # for i in range(data_count):
    #     if(features[i, axis] == value):
    #         np.row_stack((re_features2, re_features1[i, :]))
    #         np.row_stack((re_labels, labels[i]))
    # print(re_features2, re_labels)
    # re_features2 = np.delete(re_features2, 0, 1)
    # re_labels = np.delete(re_labels, 0, 1)
    # print(re_features2, re_labels)
    return re_features2, re_labels


def creatTree(features, labels, num):
        # featlist = list(features.columns)
        # node = None
        valuecount = value_count_1di(labels)
        if valuecount.count[0] == 0:
            node = Node(1, 0, num)
            return node
        if valuecount.count[1] == 0:
            node = Node(0, 0, num)
            return node
        if features.shape[1] == 0:
            if valuecount.count[0] >= valuecount.count[1]:
                node = Node(0, 0, num)
                return node
            else:
                node = Node(1, 0, num)
                return node
        axis = bestSplit(features, labels)
        # print("here\n")
        node = Node(axis, 1, num)
        # print(node.value, node.item, node.num)
        valueList = set(features[:, axis])
        for value in valueList:
            re_features, re_lables = mySplit(features, labels, axis, value)
            # print(node)
            node.children.append(creatTree(re_features, re_lables, value))
        return node

class DecisionTree:
    tree = None
    def fit(self, train_features, train_labels):
        # '''
        # TODO: 实现决策树学习算法.
        # train_features是维度为(训练样本数,属性数)的numpy数组
        # train_labels是维度为(训练样本数, )的numpy数组
        # '''
        # print(train_features)
        # print(train_labels)
        self.tree = creatTree(train_features, train_labels, -1)
        
        
    
    
        # bestfeat = featlist[axis]
        # myTree = {bestfeat:{}}
        # del featlist[axis]
        # 

        # for value in valueList:
        #     myTree[bestfeat][value]=creatTree(mySplit(features, labels, axis, value))
        # return myTree
    
    def preTree(self, features, node):
        # node = self.tree
        # value = node.value
        # feat = features[value]
        # while node.item > 0:
        #     value = node.value
        #     feat = features[value]
        #     for next_node in node.children:
        #         if next_node.value == value:
        #             node = next_node
        #             break
        # return node.value
        # print(node.item, node.value)    
        if node.item == 0:
            return node.value
        feat = features[node.value]
        for next_node in node.children:
            if next_node.num == feat:
                return self.preTree(np.delete(features, node.value, 0), next_node)



    def predict(self, test_features):
        # '''
        # TODO: 实现决策树预测.
        # test_features是维度为(测试样本数,属性数)的numpy数组
        # 该函数需要返回预测标签，返回一个维度为(测试样本数, )的numpy数组
        # '''
        test_num = test_features.shape[0]
        output_lable = np.empty(test_num)
        for i in range(test_num):
            output_lable[i] = self.preTree(test_features[i, :], self.tree)
            # if output_lable[i] != 0:
            #     print (test_features[i,:])
        return output_lable


    
        

# treenode: [attr, feat[attr] == 1, feat[attr] == 2, feat[attr] == 3]


    
