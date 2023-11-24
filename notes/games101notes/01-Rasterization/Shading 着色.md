阅读材料：[Fundamentals of Computer Graphics, Fourth Edition](Fundamentals%20of%20Computer%20Graphics,%20Fourth%20Edition.pdf)

- 第10章 surface shading
  - 10.1、10.2
- 第17章 Using Graphics Hardware
  - 17.1

# Shading 着色

shading: the process of applying a material to an object

## 着色模型

**A simple shading model: Blinn-Phong Reflectance Model**

明确三个主要事情:

- **镜面高光** Specular hightlights
- **漫反射** Diffuse reflection
- **环境照明** Ambient lighting

**Compute light reflected toward camera at a specific shading point**

先给出一些定义：

![](img/Pasted image 20231122160830.png)

*Shading is local, no shadows will be generated!(shading != shadows)*

- 如何描述一个表面接收了多少 light/engergy？
  - 计算表面法线和光源方向向量的点积
  - ![](Pasted%20image%2020231122161044.png)

光源随着距离的一个衰减：![](Pasted%20image%2020231122161144.png)

**Lambertian (Diffuse) Shading**

### 漫反射项 Diffuse

shading independent of view direction

![](Pasted%20image%2020231122161258.png)

- kd 表示漫反射系数，kd=1表示完全不吸收，写成三维向量还可以分别描述RGB三通道各自的吸收情况
- 看到公式中，漫反射项和view的方向无关

kd系数变化导致的结果变化：![img](Pasted%20image%2020231122161446.png)

### 高光项 Specular Term（Blinn-Phong）

- ![](Pasted%20image%2020231122163300.png)
- 观测方向和镜面反射方向越接近，高光越亮
- *但反射方向不好计算*
- Blinn-Phong模型对上的修改

  - ![](Pasted%20image%2020231122164115.png)
  - 将判断观测方向和镜面反射方向是否接近转换为判断*法线方向和半程方向是否接近*
  - 衡量两个方向是否接近：点乘，接近->结果接近1，远离->结果接近0
  - ks 镜面反射系数
  - 简化掉了是否吸收光线的部分即n和l的点乘
  - 计算n和h的点乘上的指数系数p
    - 观察余弦的变化，发现余弦结果对各个角度的区别不大，但按照现实中的观察，高光一定是在某些角度会特别强，即需要让这个点乘项对某个范围内敏感，而对其他大部分角度较弱
    - ![](Pasted%20image%2020231122164511.png)
- ks和p的变化对结果的影响示意图：![](Pasted%20image%2020231122164636.png)

### 环境光照项 ambient term

- 假设：任何一个点接收到环境的光都是相同的

![](Pasted%20image%2020231122164735.png)

**环境光项+漫反射项+高光项=Blinn-Phong反射模型**
![](Blinn-Phong反射模型.png)

**着色模型**：目前只是针对一个点进行的

对多个点则涉及到*着色频率*问题

## 着色频率 **Shading Frequencies**

![](Pasted%20image%2020231122165248.png)

- 考虑着色要在哪些点上进行？
  - 左：对整个平面；
  - 中：对每个顶点；
  - 右：对每个像素。

### 逐面着色 Flat Shading: Shade each triangle

对每个三角形进行着色

![](Pasted%20image%2020231122165545.png)

### 逐顶点着色 Gouraud Shading: Shade each vertex

对每个顶点着色

![](img/Pasted %20image%2020231122165611.png)

### 逐像素着色 Phong Shading：Shade each pixel

对每个像素着色

![](Pasted%20image%2020231122165655.png)

### 三种着色的区别

![](Pasted%20image%2020231122165905.png)

观察发现，几何形体同样会对最后的着色结果起到影响

### 思考问题

#### 如何计算逐顶点计算法线？

通过对某个顶点周围几个面的法线计算平均，或各个面法向量的加权平均

![](Pasted%20image%2020231122170302.png)

*要注意计算向量要进行归一化*

#### 如何得到内部平滑过渡的法线？

![](Pasted%20image%2020231122170448.png)

**通过重心坐标 Barycentric Interpolation**

## Graphics（Real-time Rendering Pipeline）

图形/实时渲染管线

从开始的场景到最后的一张图，这中间经历的一系列过程

![](Pasted%20image%2020231122170735.png)
