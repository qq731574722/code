# -*- coding: utf-8 -*-
import math
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from PIL import Image


def sample(length):
    res = []
    interval = math.ceil(length/50)
    val = 0
    while val<=length:
        res.append(val)
        val+=interval
    return res

r_list = []
g_list = []
b_list = []
color_list = []
# 读取图片，保存RGB至list中
im = Image.open(r'image\e.jpg')
pix = im.load()
width = im.size[0]
height = im.size[1]
# print(pix[0, 0])
ax = plt.subplot(projection='3d')  # 创建一个三维的绘图工程
plt.title("RGB Value Disply")
for x in sample(width):
    for y in sample(height):
        r, g, b = pix[x, y]
        r_list.append(r)
        g_list.append(g)
        b_list.append(b)
        color = (r/255, g/255, b/255, 0.5)
        color_list.append(color)


ax.scatter(r_list, g_list, b_list, c=color_list)  # 绘制数据点,颜色是红色
ax.set_zlabel('Blue')  # 坐标轴
ax.set_ylabel('Green')
ax.set_xlabel('Red')

plt.draw()
plt.pause(1000)
plt.savefig('../3D View/3D2.jpg')
plt.close()
