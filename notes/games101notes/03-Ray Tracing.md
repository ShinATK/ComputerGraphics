
> 阅读材料：[Fundamentals of Computer Graphics, Fourth Edition](Fundamentals%20of%20Computer%20Graphics,%20Fourth%20Edition.pdf)
> 第 4 章（Ray Tracing）

---

# Why Ray Tracing?

Whitted-Style Ray Tracing

光栅化的不足：

- Rasterization couldn't handle **global** effects well
  - (Soft) shadows
  - especially when the light bounces **more than once**
  - ![why光线追踪](./img/why光线追踪.png)
- Rasterization is fast, but **quality is relatively low**

光线追踪的对比点：

- Ray tracing is accurate, but is **very slow**
  - rasterization: **real-time**
  - ray tracing: offline

# 基础的光线追踪算法

## Ray Casting 光线投射

![光线投射](./img/光线投射.png)

- 沿着光路反向追踪直至接触到物体
- 再从该点与光源连线检查该点是否对光源可见
- 最后产生阴影结果

#### Generating Eye Rays

一般把eye point就认为是相机所在位置，如图中所示。

- 从眼睛/相机位置投射一条光线，这条光线会与世界中的物体相交（可能会出现与多个物体相交）；选取最近相交的物体，记录该交点

![](img/PinholeCameraModel.png)

#### Shading Pixels （Local Only）

然后开始考虑该点会不会被照亮

- 从该交点向光源连一条线（shadow ray）
- 如果这条线没有被任何物体遮挡，说明该点被照亮；反之，说明该点处于阴影里
- 之后开始计算该点的着色（Blinn-Phong等着色模型），并写入对应像素

![Shading Pixels](img/ShadingPixels.png)

## Whitted-Style Ray tracing

但实际上光线会进行多次的反射折射等等，利用Whitted-Style方法可以解决这个问题

### Recursive Ray tracing








