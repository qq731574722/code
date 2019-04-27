# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image
from mpl_toolkits.mplot3d import Axes3D
from sklearn.cluster import KMeans

#data = np.random.rand(100, 3)
data = []
im = Image.open(r'..\image\a.jpg')
pix = im.load()
width = im.size[0]
height = im.size[1]
for x in range(width):
    for y in range(height):
        r, g, b = pix[x, y]
        data.append([r, g, b])

data = np.array(data)
print(data)
# K-means聚类获取数据
estimator = KMeans(n_clusters=4)            # 构造聚类器
estimator.fit(data)                         # 聚类
label_pred = estimator.labels_              # 获取聚类标签
centroids = estimator.cluster_centers_      # 获取聚类中心
inertia = estimator.inertia_                # 获取聚类准则的总和
print(label_pred)
print(centroids)
print(inertia)

# 绘制结果
ax = plt.subplot(projection='3d')  # 创建一个三维的绘图工程
plt.title("K-means Result Disply")

color_list = ['r', 'y', 'g', 'b']
ax.scatter(data[:, 0], data[:, 1], data[:, 2], alpha=0.1)
ax.scatter(centroids[:, 0], centroids[:, 1], centroids[:, 2],
           marker='s', c=color_list, s=100, alpha=1)


#ax.scatter(data[:, 0], data[:, 1], data[:, 2])
ax.set_zlabel('Blue')  # 坐标轴
ax.set_ylabel('Green')
ax.set_xlabel('Red')
plt.draw()
plt.pause(100)
plt.savefig('../3D View/K-means.jpg')
plt.close()
