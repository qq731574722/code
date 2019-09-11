# 岳麓山

时间限制：1s 内存限制：128M

## 题目描述

>岳麓山因南朝宋时《南岳记》中“南岳周围八百里，回燕为首，岳麓为足”而得名，融中国古文化精华的儒、佛、道为一体，包容了历史上思想巨子、高僧名道、骚人墨客共同开拓的岳麓山文化内涵。景区内有岳麓书院、爱晚亭、麓山寺、云麓宫、新民学会旧址、黄兴墓、蔡锷墓、第九战区司令部战时指挥部旧址等景点。

今天zc与ly等人前往岳麓山游玩，zc一向是个好强的人，想要爬到全场最靓的山峰，他的要求是山峰的高度不低于其左边的山峰，且山峰上的树木数量不低于其右边的山峰，你可以帮他快速找到满足其条件的山峰吗？

![](1.jpg)

## 输入

单组输入数据
第一行为$N$，表示山峰的数量（$0<N<10^6$），
第二行为$N$个正整数$a_i$（$0<a_i<10^6$），表示第$i$座山峰的高度，从左至右依次排列。
第三行为$N$个正整数$b_i$（$0<b_i<10^6$），表示第$i$座山峰的树木数量，从左至右依次排列。


## 输出

输出所有满足条件的山峰序号，从左至右依此输出，并用空格隔开。（注意不要有行末多余空格）
如果没有任何一座山峰满足条件，则输出none。

## 样例输入

```
5
1 3 2 4 2
3 1 2 1 1
```

## 样例输出

```
1 4
```

## 注意

海量输入数据，请使用scanf代替cin