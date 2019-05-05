import math
import matplotlib.pyplot as plt
import matplotlib
import numpy as np
from PIL import Image

def rgb2hsv(r, g, b):
    r, g, b = r/255.0, g/255.0, b/255.0
    mx = max(r, g, b)
    mn = min(r, g, b)
    df = mx-mn
    if mx == mn:
        h = 0
    elif mx == r:
        h = (60 * ((g-b)/df) + 360) % 360
    elif mx == g:
        h = (60 * ((b-r)/df) + 120) % 360
    elif mx == b:
        h = (60 * ((r-g)/df) + 240) % 360
    if mx == 0:
        s = 0
    else:
        s = df/mx
    v = mx
    return [h, s, v]


def hsv2rgb(h, s, v):
    h = float(h)
    s = float(s)
    v = float(v)
    h60 = h / 60.0
    h60f = math.floor(h60)
    hi = int(h60f) % 6
    f = h60 - h60f
    p = v * (1 - s)
    q = v * (1 - f * s)
    t = v * (1 - (1 - f) * s)
    r, g, b = 0, 0, 0
    if hi == 0:
        r, g, b = v, t, p
    elif hi == 1:
        r, g, b = q, v, p
    elif hi == 2:
        r, g, b = p, v, t
    elif hi == 3:
        r, g, b = p, q, v
    elif hi == 4:
        r, g, b = t, p, v
    elif hi == 5:
        r, g, b = v, p, q
    r, g, b = int(r * 255), int(g * 255), int(b * 255)
    return [r, g, b]


def l(h, s, v):
    H=0
    S=0
    V=0
    if h>=316 or h<=20:
        H=0
    elif 21<=h<=40:
        H=1
    elif 41<=h<=75:
        H=2
    elif 76<=h<=155:
        H=3
    elif 156<=h<=190:
        H=4
    elif 191<=h<=270:
        H=5
    elif 271<=h<=295:
        H=6
    elif 296<=h<=315:
        H=7
    if 0<=s<=0.2:
        S=0
    elif 0.2<s<=0.7:
        S=1
    else:
        S=2
    if 0<=h<=0.2:
        H=0
    elif 0.2<h<=0.7:
        H=1
    else:
        H=2    
    return 9*H+3*S+V

# 取区间的中间值
def sample(length):
    res = []
    interval = math.ceil(length/50)
    val = 0
    while val<length:
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
        h, s, v = rgb2hsv(r,g,b)
        data.append(l(h,s,v))

data = np.array(data)
bins = np.arange(0, 72, 1)
# 设置matplotlib正常显示中文和负号
#matplotlib.rcParams['font.sans-serif']=['SimHei']   # 用黑体显示中文
plt.hist(data, bins=bins, normed=0, facecolor="blue", edgecolor="black", alpha=0.7)
# 显示横轴标签
plt.xlabel("l=9H+3S+V")
# 显示纵轴标签
plt.ylabel("Times")
# 显示图标题
plt.title("Color Quantification Result")
plt.show()