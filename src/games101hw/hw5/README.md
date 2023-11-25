# 作业5：光线与三角形相交

# 问题

光线追踪中最重要的操作之一：找到光线与物体的交点。一旦找到光线与物体的交点，就可以执行着色并返回像素颜色。

本次需要实现两个部分：光线的生成和光线与三角形的相交

- `Renderer.cpp`中的`Redner()`：为每个像素生成一条对应的光线，然后调用函数 `castRay()` 来得到颜色，最后将颜色存储在帧缓冲区的相应像素中
- `Triangle.hpp`中的`rayTriangleIntersect()`：v0、v1、v2是三角形的三个顶点，orig是光线的起点，dir是光线单位化的方向向量。tnear、u、v是需要使用Moller-Trumbore算法来更新的参数

# 确定思路

参考：[03-RayTracing](../../../notes/games101notes/03-Ray%20Tracing.md)

## 计算交点

先来解决计算交点的问题，这一步简单，直接带入Moller-Trumbore算法公式计算即可。

不过还是需要先回顾一下这部分的内容和思路。

- 这里使用到的思路主要是ray casting，即从eye position开始与image plane上的一个像素做一条光线投射到空间中，这条光线也叫做primary ray，其他的从该点发生折射、反射等作用后产生的次级光线统一叫做 secondary ray。随后检测primary ray这条光线路径上与哪些物体相交，并记录最近的对象的交点。
- 再从这些交点向光源所在位置做新的光线，这些被称为shadow ray。如果shadow ray在连接到光源位置前被其他物体遮挡，则说明这条shadow ray的出发点无法被光源照亮，也即产生了阴影。

那么如何找到primary ray和物体的交点呢？

这里暂时只考虑0和1个交点，以及模型使用triangle mesh进行显式描述，从而光线与物体交点转换为了光线与三角形的交点。

我们还可以继续转化问题，光线与三角形求交等价于：
- 光线与三角形所在平面求交
- 如果有交点查询该交点是否在三角形内（之前作业中已经实现）

### 计算光线与平面的交点

那么，问题只剩下了如何计算光线与平面的交点了

我们可以写出光线的ray equation：

$$\vec{r}(t) = \vec{o} + t \cdot \vec{d}$$

其中$0 \leq t < \infty$

以及平面的plane equation：

$$(\vec{p} - \vec{p'}) \cdot \vec{N} = 0$$

其中，$\vec{p}$为平面上任意一点，$\vec{p'}$为平面上一个确定的点，$\vec{N}$为平面的法线

从而可以知道，交点同时满足上边两个equation，从而可以联立求解得到：

$$t = \frac{(\vec{p'}-\vec{o})\cdot \vec{N}}{\vec{d}\cdot \vec{N}}$$

**一定要记得确定计算得到的 $t$ 是否满足条件 $0 \leq t < \infty$**

### Moller Trumbore Algorithm

利用这个算法，可以直接判断该点是否在三角形内。

之前学习过利用重心坐标来描述三角形内的任意一个点，这里同理，由于从光源发出的光线在时间t后到达三角形的交点处，所以可以很容易写出下边的公式：

$$\vec{O} + t \cdot \vec{D} = (1-b_1-b_2)\vec{P_0} + b_1 \cdot \vec{P_1} + b_2 \cdot \vec{P_2}$$

最后可以通过公式直接计算得到参数 $t \ b_1 \ b_2$

$$
\begin{bmatrix}
    t \\
    b_1 \\ 
    b_2
\end{bmatrix} = \frac{1}{\vec{S_1}\cdot\vec{E_1}} \cdot
\begin{bmatrix}
    \vec{S_2} \cdot \vec{E_2} \\
    \vec{S_1} \cdot \vec{S} \\
    \vec{S_2} \cdot \vec{D} \\
\end{bmatrix}$$

其中，

$$\begin{align*}
    &\vec{E_1} = \vec{P_1} - \vec{P_0} \\
    &\vec{E_2} = \vec{P_2} - \vec{P_0} \\
    &\vec{S} = \vec{O} - \vec{P_0} \\
    &\vec{S_1} = \vec{D} \times \vec{E_2} \\
    &\vec{S_2} = \vec{S} \times \vec{E_1}
\end{align*}$$

### 确定点在三角形内

之前作业中已经实现，但这里需要用 Moller Trumbore Algorithm计算交点，可以直接通过参数t、b_1、b_2来判断是否在平面内。

- 参数t满足：$0\leq t < \infty$
- 参数b_1和b_2满足：$b_1 > 0 \  and \ b_1 > 0 \ and \ (1-b_1-b_2)>0$

## 生成每条像素对应的光线

参考：[# rat tracing generating camera rays](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html)

这里的详细过程在上边的参考链接。

### 明确几个概念

- 相机默认位于世界坐标原点，并且朝向z轴的负方向，距离image plane只有i unit away
- raster image由pixels组成
- 像素一般使用像素的中心点位置进行描述如像素坐标为 $(x,y)$，其中心为 $(x+0.5,y+0.5)$，即光栅化
- 几个space概念：
  - **Rasrter space**: the pixels coordinate plus an offset of 0.5
  - **NDC space**: the coordinates are remapped to the range $[0,1]$
  - **Screen space**: the NDC coordinates are remapped to the [-1,1]
  - **World space**：所有objects（scene、geometry、lights、camera等）所处的空间


这一步的本质是：

> convert the pixel coordinates expressed in **raster space** (the point coordinates are expressed in pixels with the coordinates (0,0) being the top-left corner of the frame) to **world space**

### Coordinates Convert
- Pixel position -> Raster space: 
  - + 0.5 offset
  - 这一步是光栅化，使用像素中心描述该像素位置
- Raster space -> NDC space:
  - 这一步是将坐标映射到NDC（normalized device coordinates）
  - 所以需要除以屏幕的实际长宽
  
$$\begin{align*}PixelNDC_x &= \frac{Pixel_x+0.5}{ImageWidth}\\PixelNDC_y &= \frac{Pixel_y+0.5}{ImageHeight}\end{align*}$$

- NDC space -> Screen space: 
  - 由于world space中相机是位于原点的，所以需要将NDC space平移到以原点为中心的位置
  - 这一步需要注意，**屏幕像素坐标以左上角为原点，水平向右为x正方向，垂直向下为y轴正方向，所以这里计算y值要取相反数**

  $$\begin{align}PixelScreen_x &= 2 * PixelNDC_x - 1 \\ PixelScreen_y &= - (2 * PixelNDC_y - 1)\end{align}$$

  - 再者，由于NDC space是将原本的图像进行压缩纵横比后的结果，其内部像素是被挤压变形的，还需要恢复原本的比例（只需要对其中一个坐标进行处理）
  - 故这里需要用到aspect ratio

$$\begin{align*}
    ImageAspectRatio &= \frac{ImageWidth}{ImageHeight} \\
    PixelCamera_x &= (2*PixelScreen_x -1)*ImageAspectRatio \\
    PixelCamera_y &= (1-2*PixelScreen_y)
\end{align*}$$

- Screen space -> World space:
  - 根据之前所述，相机位置默认放在原点且朝向z轴负方向，image plane一般放在距离camera position为1 unit的位置，即z=-1
  - 这一步的目的是将Screen space投影回原本的大小。可以这么想，此时image plane距离camera position的值固定为1，那么根据camera的fov，可以计算得到image plane的top点y值为多少。
  - 而本题目条件下，很容易计算得到half of the vertical angle为45°
  - 可以得到最后需要乘上的系数

$$\begin{align*}
    PixelCamera_x &= (2*PixelScreen_x-1)*ImageAspectRatio*\tan(\frac{\alpha}{2}) \\
    PixelCamera_y &= (1-2*PixelScreen_y)*\tan(\frac{\alpha}{2})
\end{align*}$$

- 因为camera默认放在原点，此时camera坐标系和world坐标系是aligned的，所以最后得到的camera space坐标为：$$P_{cameraSpace}=(PixelCamera_x, PixelCamera_y, -1)$$

# 代码实现

`rayTriangleIntersect()`：

```cpp
bool rayTriangleIntersect(const Vector3f& v0, const Vector3f& v1, const Vector3f& v2, const Vector3f& orig,
                          const Vector3f& dir, float& tnear, float& u, float& v)
{
    // TODO: Implement this function that tests whether the triangle
    // that's specified bt v0, v1 and v2 intersects with the ray (whose
    // origin is *orig* and direction is *dir*)
    // Also don't forget to update tnear, u and v.

    // 带入公式计算
    Vector3f E1, E2, S, S1, S2;
    E1 = v1 - v0;
    E2 = v2 - v0;
    S = orig - v0;
    S1 = crossProduct(dir, E2);
    S2 = crossProduct(S, E1);
    float t, b1, b2;
    t = dotProduct(S2, E2) / (dotProduct(S1, E1));
    b1 = dotProduct(S1, S) / (dotProduct(S1, E1));
    b2 = dotProduct(S2, dir) / (dotProduct(S1, E1));

    // 判断在不在三角形内以及确保计算得到的t是有意义的
    if (t > 0.0 && b1 >= 0.0 && b2 >= 0.0 && (1 - b1 - b2) >= 0.0) {
        tnear = t;
        u = b1;
        v = b2;
        return true;
    }
    return false;
}
```



`Render()`：

```cpp
void Renderer::Render(const Scene& scene)
{
    std::vector<Vector3f> framebuffer(scene.width * scene.height);

    float scale = std::tan(deg2rad(scene.fov * 0.5f));
    float imageAspectRatio = scene.width / (float)scene.height;

    // Use this variable as the eye position to start your rays.
    Vector3f eye_pos(0);
    int m = 0;
    for (int j = 0; j < scene.height; ++j)
    {
        for (int i = 0; i < scene.width; ++i)
        {
            // generate primary ray direction
            float x = (2 * (i + 0.5) / 1280 - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / 960) * scale;
            // TODO: Find the x and y positions of the current pixel to get the direction
            // vector that passes through it.
            // Also, don't forget to multiply both of them with the variable *scale*, and
            // x (horizontal) variable with the *imageAspectRatio*            

            Vector3f dir = normalize(Vector3f(x, y, -1)); // Don't forget to normalize this direction!
            framebuffer[m++] = castRay(eye_pos, dir, scene, 0);
        }
        UpdateProgress(j / (float)scene.height);
    }

    // save framebuffer to file
    FILE* fp = fopen("binary.ppm", "wb");
    (void)fprintf(fp, "P6\n%d %d\n255\n", scene.width, scene.height);
    for (auto i = 0; i < scene.height * scene.width; ++i) {
        static unsigned char color[3];
        color[0] = (char)(255 * clamp(0, 1, framebuffer[i].x));
        color[1] = (char)(255 * clamp(0, 1, framebuffer[i].y));
        color[2] = (char)(255 * clamp(0, 1, framebuffer[i].z));
        fwrite(color, 1, 3, fp);
    }
    fclose(fp);    
}
```


