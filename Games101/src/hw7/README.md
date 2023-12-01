#cg #hw

# 作业 7：路径追踪

## 问题

在 hw6 中，实现了 Whitted-Style Ray Tracing 算法，并且用 BVH 等加速结构对于求交过程进行了加速。
本次则要求在 hw6 基础上实现完整的 PathTracing 算法。


## 迁移内容

- `Triangle::getIntersection(...)` in Triangle.hpp
  - 光线 - 三角形相交函数
- `IntersectP(...)` in Bounds3.hpp
  - 判断包围盒 BoundingBox 与光线是否相交
  - *注意检查 t_enter=t_exit 的时候的判断是否正确*


## 本次任务

`Vector3f Scene::castRay(const Ray ray, int depth)` in Scene.cpp，在其中实现 PathTracing 算法

一些可能用到的函数和变量：

- `intersect(const Ray ray)` in Scene.cpp：利用 BVH 加速结构求一条光线与场景的交点
- `sampleLight(Intersection pos, float pdf)` in Scene.cpp：在场景所有光源上按面积 uniform 地 sample 一个点，并计算该 sample 的概率密度
- `sample(const Vector3f wi, const Vector3f N)` in Material.hpp：按照材质的性质，给定入射方向和法向量，用某种分布采样一个出射方向
  - 这里的 wi 没有在函数体内使用
  - 计算 z 取值时，是通过对 -1~1 随机数取绝对值
- `Vector3f toWorld(const Vector3f &a, const Vector3f &N)` in Material.hpp：将`sample()`函数中的半球相对坐标转换为世界坐标
- `pdf(const Vector3f wi, const Vector3f wo, const Vector3f N)` in Material.hpp：给定一对入射、出射方向与法向量，计算 sample 方向得到该出射方向的概率密度
- `eval(const Vector3f wi, const Vector3f wo, const Vector3f N)` in Material.hpp：对给定一对入射、出射方向与法向量，计算这种情况下的 f_r 值
- `RussianRoulette` in Scene.cpp：P_RR，Russian Roulette 的概率


## PathTracing 原理简述

使用蒙特卡洛积分求解 Rendering Equation 的反射项，为了防止光线反弹后产生 N 条光线导致的光线数量爆炸，将光线每次反弹后的数量 N 设置为 1。

但这种情况下会导致严重的噪点 noisy。

为了减少噪点，可以通过*增加每个 pixel 所 trace 的 ray paths 数量*，[Path Tracing](Path%20Tracing.md)。


## 代码分析

### main() 函数

- 设置 scene 分辨率
- 加载 object 并设置相应的 material，建立 BVH
- *将 scene 传给 Render() 进行渲染*
- 记录运行时间
- ...

### void Renderer::Render() 函数

#### 目的

- 获得每一个 pixel 对应的深度信息并存入 framebuffer 的相应 index 位置

#### 过程

- 对 screen 上每一个像素进行迭代，计算每个 pixel 投射的 ray
- 再对每个 pixel 投射的 ray 进行多次 path 采样，利用 castRay 计算颜色结果，取平均值存入 framebuffer 对应 index
- 最后将 framebuffer 的数据保存为`binary.ppm`即可得到最终的渲染效果图

### Vector3f Scene::castRay() 函数

本次作业要实现的`scene.castRay(Ray, depth)`函数

#### 目的

- 利用[Monte Carlo Integration](Monte%20Carlo%20Integration.md)来计算[Rendering Equation](Rendering%20Equation.md)
- Final_Result = emission_term + (dirct_illumination + indirect_illumination)

#### 过程

切记[Ray Casting](Ray%20Casting.md)的过程，是*逆着光线的传播方向进行溯源*
- 要注意入射到 point 的 wi 和从 point 射出的 wo 分别对应哪个过程
- *使用方向向量时，一定要搞清楚方向的正负关系*

从 pixel 出发，向空间中 cast ray，根据 hit point 位置采取不同的公式计算反射

- 与场景没有 hit_point
  - `return {none}`

- 与场景有 hit_point，判断 point 所在 object 是否为 light_source
	- 是 light_source
    	- `return light_source.emission_term`
	- 不是 light source，说明打到了 object，此时分别计算 `dir_term` 和 `indir_term`
		- `dir_term`：从 light_source（*sampling light source*）cast 一条 ray 到 hit_point
			- 判断这条 ray 在到达 hit_point 之前是否被 blocked（对比 hit_point 和 blocked_point 到 light_source 的距离之差是否在误差范围内）
				- 是，`dir_term = 0`
				- 否，计算 `dir_term`
		- `indir_term`：根据 pixel_cast_ray 的方向角 wo 对 hit_point 的方向角 wi 进行 uniform sample
			- 确保对方向 wi 上进行 ray casting 后打到了 object，判断该 object 不是光源
				- 是光源，`indir_term = 0` (*已经在 dir_term 中计算过*，此处不再重复计算)
				- 不是光源，计算 `indir_term`
		- `return dir_term + indir_term`


## 个人疑问

### 问题 1：

`sampleLight(Intersection pos, float pdf)` in Scene.cpp：在场景所有光源上按面积 uniform 地 sample 一个点，并计算该 sample 的概率密度

该函数调用了了 objects 类的成员函数 Sample(pos, pdf)

**问题**：

这里计算采样点相对球心的方向时，

` Vector3f dir(std::cos(phi), std::sin(phi)*std::cos(theta), std::sin(phi)*std::sin(theta));`

z 轴方向为什么在第一个位置？

### 问题 2：

`sample(const Vector3f wi, const Vector3f N)` in Material.hpp

这里在随机取半球的 z 坐标时，`float z = std::fabs(1.0f - 2.0f * x_1);`，x_1 为 0~1 的随机数

为什么不直接对 z 取 0~1 随机数呢？

**个人思考**：

我认为这里这么取值是考虑到了具体的物理过程和条件取舍。

在对一个点的方位角进行随机取样时，原则上取样范围为以该点为球心的一个球面，此时应该为：`float z = 1.0f - 2.0f * x_1;`，z 取值在 -1~1。

而此时我们不考虑光线入射到 object 内部的情况，只需要考虑一半即半球面上的均匀取样，即对球面均匀取样取绝对值，于是就有了`float z = std::fabs(1.0f - 2.0f * x_1);`

如果只是单纯的将 z = random(0,1)，那么从物理意义上就变成了 z 只在半球面上取样了，*少了一层从球面上进行取舍的含义，也即对 -1~1 这个范围进行取绝对值的过程*。


胡说八道 ing... :>


## 代码

- [Scene](Graphics/Games101/src/hw7/Assignment7/Scene.cpp)
- [Material](Graphics/Games101/src/hw7/Assignment7/Material.hpp)
- [Renderer](Graphics/Games101/src/hw7/Assignment7/Renderer.cpp)



## 提高项

### 多线程

将多线程应用在 Ray Generation 上，注意实现时可能涉及的冲突

### Microfacet

正确实现 Microfacet 材质，提交可体现 Microfacet 性质的渲染结果

