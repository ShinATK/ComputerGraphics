#cg 

# What is Rasterization?

[Raterization](https://zh.wikipedia.org/wiki/%E6%A0%85%E6%A0%BC%E5%8C%96)

**栅格化/光栅化**：将[向量图形](https://zh.wikipedia.org/wiki/%E7%9F%A2%E9%87%8F%E5%9B%BE%E5%BD%A2)转换成[位图](https://zh.wikipedia.org/wiki/%E4%BD%8D%E5%9B%BE)的过程。

- 向量图形：计算机图形学中用点、直线或多边形等基于数学方程的几何图元表示的图像
- 位图：使用像素数组（Pixel-array/Dot-matrix 点阵）来表示的图像

Sampling

# Why need Rasterization?

所有的现代计算机显示器都要讲矢量图形转换成栅格图像的格式，包含屏幕上每个像素数值的栅格图像保存在内存中。

# How to do Rasterization?

这里暂时只考虑三角形的图元

## 基本实现方法

首先思考一个简单的问题，如何将一个三角形在栅格化显示器上显示出来呢？

![Drawing to Raster Displays](./img/Pasted%20image%2020231201150322.png)

### Sampling

可以遍历屏幕上每个像素 pixel，然后检测该 pixel 是否在三角形内部，如果在则设置为 1，不在则设置为 0，用伪代码表示如下：

```python
for each_pixel in screen:
	if each_pixel.inside(triangle):
		each_pixel.set_values(1)
	else:
		each_pixel.set_values(0)
```

约定：*用 pixel 的中心点坐标来表示对应的 pixel*

即：

![Sample location for pixel (x,y) = (x+0.5, y+0.5)](./img/Pasted%20image%2020231201151105.png)

经过遍历后，应当能够得到的结果：

![Sample if each pixel center is inside triangle](./img/Pasted%20image%2020231201151357.png)

此时就有一个问题，*该如何检测一个像素是否在三角形内部呢？*

### Cross Product with Triangle

下图有三角形$P_0P_1P_2$（注意是逆时针标记的顶点），我们想要检测像素 Q 的中心点是否在三角形内，那么只需要计算$\vec{P_0Q}$和三角形的三条边的叉积（按照顶点标记的顺序为三条边各自的方向）即可。

![Corss Product with Triangle](./img/Pasted%20image%2020231201151524.png)

如果像素 Q 在三角形内部，那么当满足条件：

$$(\vec{P_0Q}\times\vec{P_0P_1})\cdot(\vec{P_1Q}\times\vec{P_1P_2})\cdot(\vec{P_2Q}\times\vec{P_2P_0}) > 0$$

此时，Q 点在三角形内部。

伪代码如下：

```python
bool Pixel::inside(triangle){
	a = Pixel.crossProduct(Q, P_0, P_1);
	b = Pixel.crossProduct(Q, P_1, P_2);
	c = Pixel.crossProduct(Q, P_2, P_0);
	return dot(a, b, c) > 0
}
```

对于边界上的点，可以自行定义是否归属于三角形内部

### 加快栅格化速度

*思考*：如果我们想要显示的图形，并不会填满整个屏幕，那就说明没有必要对*全部的像素*进行检测。

我们可以用其他容易遍历的图形将三角形圈起来，例如下图中的矩形（[Bounding Volumes](Bounding%20Volumes.md)）Bounding Box。则此时处于 Box 内部的像素才是我们真正需要遍历的像素。这样一来，就避免了对一些无用的检测。

![Bounding Box](./img/Pasted%20image%2020231201153006.png)

那么这个 Bounding Box 该如何确定呢？

可以发现，这个 box 的四个顶点的像素坐标，分别对应了三角形三个顶点的坐标的最大和最小值的组合。*显示器的像素坐标原点一般在左上角，水平向右为 x 正向，垂直向下为 y 正向*。所以用两个对角点就能够表示这个 Bounding Box，即：$P_{min} = (x_{min}, y_{min}),\ P_{max} = (x_{max}, y_{max})$

伪代码实现：

```python
# Bounding Box
x_min = min(triangle.vertex.x());
y_min = min(triangle.vertex.y());
x_max = max(triangle.vertex.x());
y_max = max(triangle.vertex.y());

BBox Box(x_min, y_min, x_max, y_max);

# 遍历 Box 内部像素
for each_pixel in Box:
	...
```

到此，就可以将一个三角形成功显示在位图中。*但是*，此时又会出现一个问题，见下图：

![Pixel Display](./img/Pasted%20image%2020231201153953.png)

三角形的边缘很明显不是我们所期望的那样，这种现象被称为[Aliasing](https://en.wikipedia.org/wiki/Aliasing)

### Sampling Artifacts

> In nature science and signal processing, an artifact or artefact is any *error* in the *perception or representation of any information* introduced by the involved equipment or technique(s).

即，被设备或技术引入的在对信息的感知或表示时出现的*错误*

- Jaggies (Staircase Pattern): sampling in sapce
- Moire Patterns in Imaging: undersampling images
- Wagon Wheel Illusion (False Motion): sampling in time
- ...

这些本质上都是因为：
- Signals are changing *too fast*(high frequency)
- But *sampled too slowly*

### Antialiasing Idea: Blurring (Pre-Filtering) before Sampling

观察下图：

![](./img/Pasted%20image%2020231201155241.png)

可以发现，在栅格化的三角形中锯齿/jaggies 出现在纯白/纯红色的边缘位置。

那么，是否可以经过提前处理，将原本的三角形的边缘进行“模糊”：

![](./img/Pasted%20image%2020231201155351.png)

此时，可以看到原本出现 Jaggies 的边缘位置，这些 pixel 的 value 变为了红色和白色的中间值

此时，recall 我们之前对像素是否在三角形内的判断依据：根据像素中点是否在三角形内来判断设置 pixel_values 为 1 还是 0。将这一条件更改为：*根据 pixel 有多少比例的 area 处于三角形内部来对应设置 pixel_values*

![Computing Average Pixel Value](./img/Pasted%20image%2020231201155913.png)

### Anti-Aliasing (AA)

为了解决这种图物边缘出现凹凸锯齿，还可以通过使用[Anti-Aliasing (AA)](Anti-Aliasing%20(AA).md)，即**抗锯齿**或反走样技术。

这里暂时只整理[Multisampling Anti-Aliasing (MSAA)](Multisampling%20Anti-Aliasing%20(MSAA).md)和[Super-Sampling Anti-aliasing (SSAA)](Super-Sampling%20Anti-aliasing%20(SSAA).md)。

MSAA：
- 对每个 pixel 进行 N x N 次采样

![2x2 supersampling](./img/Pasted%20image%2020231201164806.png)
- 对每个 pixel 内部的 samples 求平均

最后可以得到每个 pixel 对于三角形栅格化显示时的贡献比例

![](./img/Pasted%20image%2020231201164950.png)


### Visibility/Occlusion: Z-buffering

之前我们只是对一个三角形进行了栅格化绘制，但如果需要同时显示多个三角形，那么如何判断哪个三角形在上即可见，哪个三角形在下即被遮挡呢？即，**可见性问题**。

一种方法：可以按照从远到近的方式进行栅格化，远处的物体先进行栅格化，近处的物体在栅格化时将先前绘制好的部分重新覆盖掉即可，即**画家算法/优先填充**

但这种方法效率较低，这里尝试使用另一种方法：深度缓冲[Z-buffering](Z-buffering.md)。

![](./img/Pasted%20image%2020231201170014.png)

## Shading

Shading: The process of *applying a material* to an object.

在通过上述步骤后，我们已经可以将物体呈现在栅格化的屏幕上了，但此时物体还无法通过不同亮度来表现出深度。

*一切的目的都为了看起来更真实*

### 相对于光源的角度

除了环境光，其他光都是具有放相信的。根据物体表面和光线的夹角不同，shading 算法会改变三维模型中的表面颜色和明暗程度。

![Lambert's cosine law](./img/Pasted%20image%2020231201172128.png)

### 距离衰减

距离衰减的计算的算法：
- 无：光强跟点与光源之间的距离无关
- 线性：光强正比于距离的倒数
- 二次：光强正比于距离倒数的平方（*无雾或其他东西吸收或这散射的情况下的光强真实衰减模型*）
- n 阶：光强正比于距离倒数的 n 次方
- 其他

![light fall off](./img/Pasted%20image%2020231201172312.png)

### 光照模型

通过对现实世界的物体进行观察，可以发现物体和光线相互作用之后，物体的表面呈现出的不同亮度位置，可以大概分为三种：
- 高光 Specular hightlights
- 漫反射 Diffuse reflection
- 环境光 Ambient lighting

![Perceptual Observation](./img/Pasted%20image%2020231201170938.png)
可以通过[Blinn-Phong Reflectance Model](Blinn-Phong%20Reflectance%20Model.md)来对这三项进行建模

### 插值技术

渲染的过程需要计算表面的亮度，而上边的光照模型需要知道任意点的法线，但实际上存储了法线信息的只是多边形的顶点。解决这一问题可以使用不同的插值技术。

#### Flat Shading 平直着色法



基于“组成模型的多边形都是平的”的假设，认为在同一多边形上任意点的法线都相同。

使用这种着色法时，先在每个多边形上挑选一个点计算颜色（通常是多边形的第一个顶点，如果是三角形网格则也可以选择[几何中心](https://zh.wikipedia.org/wiki/%E5%87%A0%E4%BD%95%E4%B8%AD%E5%BF%83 "几何中心")），则该多边形上其余点都直接使用该点的颜色。所以，使用平直着色法的每个多边形上都是统一的颜色，和[最近邻插值](https://zh.wikipedia.org/wiki/%E6%9C%80%E8%BF%91%E9%82%BB%E6%8F%92%E5%80%BC "最近邻插值")的效果类似。

当其他高级的着色技术由于计算量太大不便于使用时，这种方法常用于*高速渲染*。但难以做出高光效果。

#### Smooth Shading 平滑着色法

使用平直着色法时，颜色在多边形的边缘跳变。而使用平滑着色法（英语：smooth shading）时，每个像素的颜色都可以不同，相邻多边形之间的颜色转变看上去就比较平滑。通常先计算多边形顶点的颜色，再通过[双线性插值](https://zh.wikipedia.org/wiki/%E5%8F%8C%E7%BA%BF%E6%80%A7%E6%8F%92%E5%80%BC "双线性插值")来确定多边形上其它点的像素值。

常见的平滑着色法有：
- [Gouraud 着色法 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/Gouraud%E7%9D%80%E8%89%B2%E6%B3%95)
	- 计算多边形的顶点法向量
	- 用光照模型去计算每个顶点的光强
	- 用双线性插值计算多边形表面上每个像素的明暗
- [Phong 着色法 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/Phong%E8%91%97%E8%89%B2%E6%B3%95)：与 Gouraud 着色法类似，区别在于进行双线性插值的不是光照强度本身，而是顶点的法线
	- 计算多边形顶点的法向量
	- 双线性插值计算每个像素点的法向量
	- 通过每个像素的法向量计算光强
	- 根据光强绘制像素

此外，还有通过[泰勒级数](https://zh.wikipedia.org/wiki/%E6%B3%B0%E5%8B%92%E7%BA%A7%E6%95%B0 "泰勒级数")展开[1](https://zh.wikipedia.org/wiki/%E7%9D%80%E8%89%B2#cite_note-1)、[球面线性插值](https://zh.wikipedia.org/wiki/%E7%90%83%E9%9D%A2%E7%B7%9A%E6%80%A7%E6%8F%92%E5%80%BC "球面线性插值")[2](https://zh.wikipedia.org/wiki/%E7%9D%80%E8%89%B2#cite_note-2)等方法实现的平滑着色法。

## Graphics Pipeline

- [Graphics (Real-time Rendering Pipeline)](Graphics%20(Real-time%20Rendering%20Pipeline).md)


## Texture Mapping

此时我们已经能够知道如何把物体栅格化到屏幕上，也能够通过光照模型给物体表面产生不同的光照效果，但这还远远不足以达到追求真实的效果。

还需要通过**材质贴图/纹理贴图**给物体提供丰富的细节。

那么就涉及到一个问题，*如何将纹理贴图和物体表面建立起一一对应的关系*。

**纹理坐标系**

u、v 限制在 0~1 之间

![纹理坐标系](./img/Pasted%20image%2020231201181100.png)

## Barycentric Coordinates

因为物体的信息都存储在定点上，而我们希望能够得到三角形面内的连续变化的值。

例如，纹理坐标、颜色、法线等等

利用**重心坐标**对三角形进行插值
- [Barycentric](Barycentric.md)

## Texture Magnification

在 applying textures 时，往往会遇到纹理过大或过小的问题。

### 纹理太小

当纹理太小时，可能会出现某个像素点找不到对应纹理坐标的情况。

三种映射办法：
#### Nearest

映射到最近位置

#### Bilinear

计算公式：

$$\begin{align*}
u_0 &= lerp(s,u_{00},u_{10})\\
u_1 &= lerp(s,u_{01},u_{11})\\
f(x,y)&= lerp(t,u_0,u_1)
\end{align*}$$

![](./img/Pasted%20image%2020231201182101.png)


#### Bicubic

### 纹理太大

![](./img/Pasted%20image%2020231201182331.png)

如果纹理太大，那就会导致无法全部使用纹理坐标上的信息

可以发现，随着距离的拉远，单个像素在纹理坐标上覆盖范围会变得越来越大

![](./img/Pasted%20image%2020231201182434.png)

虽然可以使用超采样来解决这个问题，但为了得到高质量会非常消耗资源。

Point Query vs. (Avg.) Range Query

#### Mipmap

能够*快速*进行*方形*范围内的*近似*查询

![](./img/Pasted%20image%2020231201182648.png)

将这些图进行逐层级放置，从而方便查询

![](./img/Pasted%20image%2020231201182731.png)

只需要知道在纹理坐标下相较于正常情况下被改变了多少程度，计算方式如下：

![](./img/Pasted%20image%2020231201182803.png)

但此时由于是直接在不同层级上寻找对应的纹理坐标，而不同层级之间又存在较大的差别时，

![](./img/Pasted%20image%2020231201182955.png)

这里可以继续应用插值方法，对层级之间进行插值，从而可以获得类似“2.5”层的数据

即，**三线性插值**

![](./img/Pasted%20image%2020231201183040.png)

实现了层级之间的连续查询

![](./img/Pasted%20image%2020231201183047.png)

Mipmap 只能够进行方形区域的查询，然而实际上像素从 screen space 上映射到对应的 texture space 上后，其对应的区域不一定还是方形，如下

![](./img/Pasted%20image%2020231201183201.png)

所以这里就有另一种方式：[各向异性过滤 - 维基百科，自由的百科全书](https://zh.wikipedia.org/wiki/%E5%90%84%E5%90%91%E5%BC%82%E6%80%A7%E8%BF%87%E6%BB%A4)

#### 各向异性过滤 Anisotropic Filtering

Ripmap：可以查询平行于轴向的矩形区域，相较于 mipmap 多了一些不均匀性的压缩信息

![](./img/Pasted%20image%2020231201183252.png)

但此时还没有完全解决，因为映射到 texture space 上后还会有很多不规则的矩形区域，各向异性过滤仍然是用矩形去近似这种不规则的区域


#### EWA 过滤

- 有任意不规则形状，可以拆成很多圆形来覆盖区域，多次查询覆盖圆形
- 代价较高

![](./img/Pasted%20image%2020231201183533.png)

## Texture 应用

### 环境光映射

记录来自各个方向的光；若屋子较小，不能直接运用方向记录信息。

简单的方法：在场景中设置金属球，则金属球反射的信息即为环境光；可以记录在球面上然后展开

问题和解决：

- 问题：展开后会产生扭曲，不是均匀的展开
- 解决：将信息记录在立方体上，则有 6 张图

该方法称为天空盒 Cube Map

### 法线贴图（Bump texture）

- 纹理可以记录相对高度和法线信息
- Bump/normal mapping
- 伪造细节几何

得到凹凸贴图（高度）和法线贴图（法线）：记录任何点高度相对的移动，通过高度的变化改变法线：

![Bump Texture](./img/Pasted%20image%2020231201183735.png)


以上假设法线为 (0,0,1)，可以认为*在局部坐标系的法线就是指向局部坐标系的 z 轴*，然后再转换回原坐标系。（*这里可以联系到 hw7 中的 toWorld() 函数*）

### 位移贴图（Displacement mapping）

比 bump mapping 更高级，可以真的在模型上进行移动顶点。

Bump Texture：
- 可以看到 bump texture 会在边缘处看出问题。
- 并且无法处理自身内部阴影问题

Displacement Mapping：
- 真实移动了顶点位置
- 和法线贴图的纹理相同

但位移贴图要求：
- 模型的三角形足够细，采样率非常高

解决办法：先定义较低细分程序的面，再根据需要结合位移贴图检测是否需要进行细分，**动态曲面细分**


![](./img/Pasted%20image%2020231201183905.png)

### 3D Procedural Noise + Solid Modeling

定义在三维空间中噪声的函数，该噪声函数可以来算出性质，常见的方法为柏林噪声 – Perlin Noise

![](./img/Pasted%20image%2020231201184207.png)


### 提供预计算着色（Provide Precomputed Shading）

想要实时计算模型内部复杂阴影，可以使用环境光遮蔽，但是成本代价较高。可以计算好后写入贴图。

### 3D 纹理和体渲染

物体的信息记录在空间中，但是作为纹理


# Games101 作业

- 作业 2：Triangles and Z-buffering
	- [README](Graphics/Games101/src/hw2/README.md)
- 作业 3：Pipeline and Shading
	- [README](Graphics/Games101/src/hw3/README.md)

