
# 几何形体的表示方式

几何形体的表示有多种方式：

![多种表示几何形体的方式](../img/多种表示几何形体的方式.png)

## 几何形体的隐式表示

- 基于classifying points
- 例如f(x,y)所定义的几何图形![几何形体的表示有多种方式](../img/几何形体的表示有多种方式.png)
- 问题：sampling can be hard，不直观，只是知道xyz之间的关系
- 好处是：Inside/Outside Tests Easy，很容易判断一个点在内还是在外

## 几何形体的显式表示

- 每个点都 *直接给出* 或者通过 *参数映射* 给出，points are given directly or via parameter mapping
- 好处：sampling is Easy
	- 每个点都能够直观表示出来，能够直接看到xyz分别是什么![显式表示每个点都可以直接给出](../img/显式表示每个点都可以直接给出.png)
- 问题：inside/outside test hard，难以判断一个点是在内还是在外

# 隐式几何表示方法

## 布尔运算（隐式）

【CSG】**constructive solid geometry (implicit)**

![几何形体的布尔运算](../img/几何形体的布尔运算.png)

## 距离函数（隐式）

**distance functions(implicit)**

![利用距离函数产生的融合几何形体](../img/利用距离函数产生的融合几何形体.png)

- 描述一个点到物体的最近距离（signed）
- giving minimum distance from anywhere to object

*一个应用距离函数的例子*：![](../img/一个应用距离函数的例子.png)

A，左侧遮挡1/3；B，左侧遮挡2/3。如果想要将二者混合（blend），单纯的叠加会导致中间的1/3部分颜色较浅。

- *解决办法*：利用距离函数
	- A和B都可以得到一个关于遮挡边界的距离函数描述，从而将边界左右分为正负两侧
	- 随后将这个距离函数进行求和，从而得到一个blend后的结果

**Blending Distance Functions (Implicit)**

![任意两个距离函数的blend结果](../img/Pasted%20image%2020231124121928.png)

*那么*，如何再将距离函数恢复成几何形体的表面呢？

一个方法：**Level Set Methods(Implicit)**，这个概念可以类比地理上的等高线

![水平集方法](../img/Pasted%20image%2020231124122053.png)

## 分形表示（隐式）

Fractals (Implicit)，分形 -> 自相似 self-similarity，details at all scales

*Hard to control shape!*

![一些分形的例子](../img/Pasted%20image%2020231124122250.png)

## 隐式表示的Pros&Cons

**Pros：**
- compact description (e.g., a function)
	- 表述起来很容易
- certain queries easy (inside object, distance to surface)
	- 查询内外，距离函数等很容易
- good to ray-to-surface intersection
	- 容易做光线的求交
- for simple shapes, exact description / no sampling error
- easy to handle changes in topology (e.g., fluid)
**Cons：**
- diffcult to model complex shapes
	- 难以描述复杂的结合形体
- **所以需要用到显式的表示**

# 显式几何表示方法

![多种显式几何表示](../img/Pasted%20image%2020231124134416.png)

## 点云（显式）

Point Cloud

![点云](../img/Pasted%20image%2020231124134536.png)

## 多边形面（显式）

*应用最广泛的一种*

Polygon Mesh，三角形或多边形表示

![多边形表示](../img/Pasted%20image%2020231124134639.png)

*平时是如何在图形学表示用三角形面形成的物体的*

![](../img/Pasted%20image%2020231124134752.png)

- 这个obj与编译出来的不是同一个东西
- 图中描述的为一个立方体，上方的v表示的是8个顶点，vn表示法线，vt为纹理坐标（会有共用）
- f处表示第几个顶点，第几个纹理坐标，第几个法线
	- `f 5/1/1 1/2/1 4/3/1`
		- `5/1/1` 表示第5个顶点，第1个纹理坐标，第1个法线
		- 其他几个同理，表示用这三个顶点来组成一个三角形

# Curves

## 贝塞尔曲线 Bezier Curves

*用一系列的控制点，去描述某个曲线*

下图为贝塞尔曲线的一个示例

![贝塞尔曲线的一个示例](../img/Pasted%20image%2020231124135242.png)

*如何用任意多个点来画出一条贝塞尔曲线*

- **de Casteljau Algorithm**

三个点生成的贝塞尔曲线-quadratic Bezier，二次贝塞尔曲线

- 通过线性插值插入一个点
  - ![](../img/Pasted%20image%2020231124135628.png)
- 在另一边同样重复操作，并连接两点
  - ![](../img/Pasted%20image%2020231124135659.png)
- 从而找到的点 $b_0^2$ 为时间t时，贝塞尔曲线所在的位置
- 剩下的就是不断重复这个操作，从而就可以找到一条完整的贝塞尔曲线

**Cubic Bezier Curve-de Casteljau**

四个输入点，继续采用同样的线性插值，same recursive linear interpolations

![Cubic Bezier Curve-de Casteljau](../img/Pasted%20image%2020231124135840.png)

![一个动画演示](../img/Pasted%20image%2020231124135928.png)

## Evaluating Bezier Curves Algebraic Formula

本质上，通过几个操作点，经过某些操作，从而可以得到贝塞尔曲线上任意一个点的位置

![](../img/Pasted%20image%2020231124140031.png)

接下来尝试使用数学表达式来描述这个过程：

![](../img/Pasted%20image%2020231124140150.png)

**总结**：n个控制点所得到的n阶贝塞尔曲线上的点的公式![](../img/Pasted%20image%2020231124140321.png)

## 贝塞尔曲线的一些性质

![](../img/Pasted%20image%2020231124140806.png)
![](../img/Pasted%20image%2020231124140832.png)
- 起始点与结束点一定在给定的两个点上
- 曲线在起始点与结束点的切线
- 仿射变换下具有一个很好的性质，但是投影变换会导致变化
- **凸包**
	- ![凸包的定义](../img/Pasted%20image%2020231124140948.png)
	- *贝塞尔曲线上的点一定在控制点所形成的凸包之内*

## Piecewise Bezier Curves

piecewise 逐段

**贝塞尔曲线的问题**：控制点太多时，不容易用所有的控制点来进行控制，有些点甚至是用不到的。

*能否减少使用的控制点个数呢？*
- **利用分段贝塞尔曲线**

### 分段贝塞尔曲线

![Piecewise Bezier Curves](../img/Pasted%20image%2020231124141339.png)

如图，每四个点定义一个贝塞尔曲线（图中四个点一般不会画到一起，只会在起始和结束两个位置显示）![四个控制点如图](../img/Pasted%20image%2020231124141547.png)
如果某个点的两侧控制杆共线，则该点的导数是连续的

### 连续 Continuity

![](../img/Pasted%20image%2020231124142006.png)

- C0连续，贝塞尔曲线在该点在几何上是相接的
	- 第一段的结束点是第二段的起始点
	- ![](../img/Pasted%20image%2020231124141841.png)
	- ![](../img/Pasted%20image%2020231124142014.png)
- C1连续，切线连续
	- 两个控制点与贝塞尔曲线上点共线且距离相等
	- ![](../img/Pasted%20image%2020231124141904.png)
	- ![](../img/Pasted%20image%2020231124141934.png)

## 其他类型的样条线

splines 样条线

![splines](../img/Pasted%20image%2020231124142109.png)

### B-splines

- Short for basis splines
- Require more information than Bezier curves
- Satisfy all important properties that Bezier curves have (i.e. superset)

希望有一种*局部性质*，从而使得样条线在修改某些部分时，不至于影响到整个样条线的整体，例如分段的贝塞尔曲线。

B-splines则是不需要特地分段即可

- **B-splines 极其复杂，还有另一个叫做 NURBS**
- 高阶贝塞尔曲线
- 曲线上的操作

# Surfaces

将贝塞尔曲线引申到曲面：

![贝塞尔曲面](../img/Pasted%20image%2020231124142546.png)

*那么如何将贝塞尔曲线延伸到贝塞尔曲面呢*

## Bicubic Bezier Surface Patch

![](../img/Pasted%20image%2020231124142647.png)

16（4 x 4）个控制点

同样利用到了双线性插值

![](../img/Pasted%20image%2020231124143310.png)

*问题思考，不同的贝塞尔曲线如何无缝衔接*

## Evaluating Bezier Surfaces

贝塞尔曲面同样可以由参数表述，所以也是显示表示

- 使用参数（u，v）来表述曲面的位置![](../img/Pasted%20image%2020231124143359.png)
- ![](../img/Pasted%20image%2020231124143418.png)

# Mesh Operations: Geometry Processing

使用最多的还是三角形这样的网格描述![](../img/Pasted%20image%2020231124143020.png)

- Mesh Subdivision (upsampling)![](../img/Pasted%20image%2020231124144122.png)
- Mesh Simplification (down sampling)![](../img/Pasted%20image%2020231124144135.png)
- Mesh Regularization (same `#triangles`)![](../img/Pasted%20image%2020231124144201.png)

## Subdivision 曲面细分

和 triangle meshes 的细分类似![](../img/Pasted%20image%2020231124144326.png)
- 第一步，创建更多的三角形（顶点）
- 第二步，优化位置

### Loop Subdivision

这里的Loop不是循环，是提出者的family name

**先细分，再调整**

#### 步骤简述

- 第一步，**细分**，split each triangle into four，三角形数量增多
	- ![](../img/Pasted%20image%2020231124144353.png)
- 第二步，**调整**，new vertex positions according to weights
	- New / old vertices updated differently，区分出新顶点和旧顶点
	- ![](../img/Pasted%20image%2020231124144459.png)

#### Update 更新顶点位置

- 对于新顶点
![](../img/Pasted%20image%2020231124144611.png)

中间白点为新的顶点，更新其位置，即做加权平均

- 对于旧顶点

![](../img/Pasted%20image%2020231124144658.png)

保留一部分自身原本位置信息，以及一部分周围的信息，二者进行加权平均

*degree：度，一个顶点和它相连的边数就是degree*

#### Results

![](../img/Pasted%20image%2020231124144935.png)

### Catmull-Clark Subdivision (General Mesh)

Loop细分只能针对三角形的细分，*Catmull-Clark Subdivision则可以对网格进行细分*

![](../img/Pasted%20image%2020231124145146.png)

步骤：
- Add vertex in each face（面的中心）
- Add midpoint on each edge（边的中心）
- Connect all new vertices

![](../img/Pasted%20image%2020231124145422.png)

*思考经过一次细分后，*
- 还有多少个奇异点？
	- 4个
- 度为多少？
	- 5（old）
	- 3（new）
	- *总结得到，非四边形面中新增的点，就一定会出现奇异点*
- 有多少非四边形面？
	- 之前的非四边形面都消失了
- **catmull-clark细分，在第一次细分后增加了非四边形面数个奇异点，之后再细分也不会再增加了**

![](../img/Pasted%20image%2020231124145849.png)

Loop Subdivision和Catmull-Clark Subdivision：![](../img/Pasted%20image%2020231124145937.png)

## Simplification 曲面简化

目的是减少mesh元素但同时维持overall shape

![](../img/Pasted%20image%2020231124150317.png)

*但如果观察远处时，就会发现，适当减少mesh元素后效果还可以。有些时候没有必要用到过于复杂的模型*

那么接下来的问题是，*如何计算？*

其中一个方法：Edge Collapse，边坍缩

### Collapsing Edge

![](../img/Pasted%20image%2020231124150535.png)

*再思考一个问题，如何判断哪些边需要坍缩，哪些边不需要坍缩？*

### Quadric Error Metrics

二次误差度量

- *思考*，下图中，如何防止蓝色三角形顶点的位置从而使得蓝色三角形与原本的灰色区域形状基本一致呢？
	- 单纯求平均效果不理想
	- *利用二次误差度量，希望把这个点放到一个位置，使得这个点到和它相关联的面的位置距离平方和最小*

![](../img/Pasted%20image%2020231124150630.png)

![](../img/Pasted%20image%2020231124150849.png)

**如何去选要去坍缩的边？**



