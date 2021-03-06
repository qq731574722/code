# -*- coding: utf-8 -*-
import math
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
from mpl_toolkits.mplot3d import Axes3D
from sklearn.cluster import KMeans

def sample(length):
    res = []
    interval = math.ceil(length/50)
    val = 0
    while val<=length:
        res.append(val)
        val+=interval
    return res

data = []
im = Image.open(r'image\e.jpg')
pix = im.load()
width = im.size[0]
height = im.size[1]
for x in sample(width):
    for y in sample(height):
        r, g, b = pix[x, y]
        data.append([r, g, b])

data = np.array(data)

# K-means聚类获取数据
estimator = KMeans(n_clusters=4)            # 构造聚类器
estimator.fit(data)                         # 聚类
label_pred = estimator.labels_              # 获取聚类标签
centroids = estimator.cluster_centers_      # 获取聚类中心
inertia = estimator.inertia_                # 获取聚类准则的总和
#print(label_pred)
print(centroids)
#print(inertia)

# 绘制结果
ax = plt.subplot(projection='3d')  # 创建一个三维的绘图工程
plt.title("K-means Result Disply")
'''
color_list = []
for i in centroids:
    color_list.append(i/256)
'''
color_list = []
for center in centroids:        #将簇标记为质心的颜色
    color = []
    for i in center:
        color.append(i/255)
    color_list.append(color)

color_list=['r','y','g','b']

points = []
for i in label_pred:
    points.append(color_list[i])
ax.scatter(data[:, 2], data[:, 0], data[:, 1], c=points, alpha=0.1)
ax.scatter(centroids[:, 2], centroids[:, 0], centroids[:, 1],
           marker='s', c=color_list, s=100, alpha=1)


#ax.scatter(data[:, 0], data[:, 1], data[:, 2])
ax.set_zlabel('Green')  # 坐标轴
ax.set_ylabel('Red')
ax.set_xlabel('Blue')
plt.draw()
plt.pause(100)
plt.savefig('../3D View/K-means2.jpg')
plt.close()
