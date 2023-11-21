#readme
# 目录

## 课程学习

|   |   |   |   |   |   |
|---|---|---|---|---|---|
|课程网站|课程时长|编程语言|课程视频|课程教材|课程作业|
|[CS 148: Introduction to Computer Graphics and Imaging](https://web.stanford.edu/class/cs148/lectures.html)|40小时|Python|[CS148](https://web.stanford.edu/class/cs148/summer23/lectures.html)|Fundamentals of Computer Graphics|[CS 148: Introduction to Computer Graphics and Imaging](https://web.stanford.edu/class/cs148/assignments.html)|
|[GAMES101: 现代计算机图形学入门](https://sites.cs.ucsb.edu/~lingqi/teaching/games101.html)|80小时|C++|[GAMES101](https://www.bilibili.com/video/BV1X7411F744/?p=1&vd_source=ec161869fed250aa616ee2fdd48e6494)|Fundamentals of Computer Graphics|[往期作业汇总帖](https://games-cn.org/forums/topic/allhw/)|
|GAMES102：几何建模与处理||||||
|[GAMES103：基于物理的计算机动画入门](https://games-cn.org/games103/)|50小时|C#|[GAMES103](https://www.bilibili.com/video/BV12Q4y1S73g/?vd_source=ec161869fed250aa616ee2fdd48e6494)||[其他人整理的库](https://github.com/indevn/GAMES103/tree/main/HW)|
|GAMES201：高级物理引擎实战指南||||||
|[GAMES202: 高质量实时渲染](https://sites.cs.ucsb.edu/~lingqi/teaching/games202.html)|60小时|C++|[GAMES202](https://www.bilibili.com/video/BV1YK4y1T7yY/?vd_source=ec161869fed250aa616ee2fdd48e6494)|Real-Time Rendering, 4th edition.|[GAMES202作业汇总– 计算机图形学与混合现实在线平台](https://games-cn.org/forums/topic/games202zuoyehuizong/)|

## 图形学API

- [# TinyRenderer](https://github.com/ssloy/tinyrenderer)

- 引擎部分
- 渲染框架OpenGL、DirectX、Vulkan等
	- OpenGL
		- [ ] [Learn OpenGL CN](https://learnopengl-cn.github.io/)
		- [ ] BGFX：[# Overview - bgfx 1.0 documentation](https://bkaradzic.github.io/bgfx/overview.html)
	- [ ] [Vulkan Tutorial](https://link.zhihu.com/?target=https%3A//vulkan-tutorial.com/)
	- Web：WebGL、three.js
	- [# Three.js - JavaScript 3D Library](https://link.zhihu.com/?target=https%3A//threejs.org/)
- 3D引擎、游戏：Unity、UE4
	- Unity、UE官方网站以及各类视频
- **引擎熟练使用+读代码**，具体来说
	- 读过UE5多少模块代码，远比看过什么书，做对什么题重要得多
- [# A brief computer graphics / rendering course](https://github.com/ssloy/tinyrenderer)

## 项目实战

- 实践：软光栅
	- 软件光栅化 renderer
		- 向量矩阵四元数
		- 整条pipeline
		- 实现到vs/ps加shadowmap
- 实践：光线追踪
	- ray tracing/path tracing，为以后pbr（physically based rendering）打基础
- 实践：渲染进阶
	- - [Physically Based Rendering in Filament](https://google.github.io/filament/Filament.html)

- 参考：
	- [# 图形学渲染方向个人学习路线整理](https://zhuanlan.zhihu.com/p/445343440)
	- [# 如何开始用 C++ 写一个光栅化渲染器？ - UncP的回答 - 知乎](https://www.zhihu.com/question/24786878/answer/127484388)
	- [# 如何开始用 C++ 写一个光栅化渲染器？ - Zero的回答 - 知乎](https://www.zhihu.com/question/24786878/answer/401447840)

## 游戏开发相关

- [ ] [游戏程序员的学习之路 -叶劲峰](https://link.zhihu.com/?target=https%3A//github.com/miloyip/game-programmer/)
- [ ] [技术美术百人计划](https://link.zhihu.com/?target=https%3A//space.bilibili.com/7398208/video)
- [ ] [GAMES104: 现代游戏引擎 -不鸣科技 王希](https://link.zhihu.com/?target=https%3A//games104.boomingtech.com/)
- [ ] [C# and Shader Tutorials for the Unity Engine](https://link.zhihu.com/?target=https%3A//catlikecoding.com/unity/tutorials/)

## 深入提升
 
 这部分内容比较有难度，通过这些差不多就可以了解到整个工业和科研界所处理的问题了。
 
- 《# [Real-Time Rendering 4rd](https://www.zhihu.com/search?q=Real-Time%20Rendering%204rd&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra=%7B%22sourceType%22%3A%22answer%22%2C%22sourceId%22%3A1500559999%7D)》[# QianMo/Game-Programmer-Study-Notes](https://link.zhihu.com/?target=https%3A//github.com/QianMo/Game-Programmer-Study-Notes/blob/master/Content/%25E3%2580%258AReal-Time%2520Rendering%25203rd%25E3%2580%258B%25E8%25AF%25BB%25E4%25B9%25A6%25E7%25AC%2594%25E8%25AE%25B0/README.md)
- 《# [GPU 编程与CG 语言之阳春白雪下里巴人](https://www.zhihu.com/search?q=GPU%20%E7%BC%96%E7%A8%8B%E4%B8%8ECG%20%E8%AF%AD%E8%A8%80%E4%B9%8B%E9%98%B3%E6%98%A5%E7%99%BD%E9%9B%AA%E4%B8%8B%E9%87%8C%E5%B7%B4%E4%BA%BA&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra=%7B%22sourceType%22%3A%22answer%22%2C%22sourceId%22%3A1500559999%7D)》# [QianMo/Game-Programmer-Study-Notes](https://link.zhihu.com/?target=https%3A//github.com/QianMo/Game-Programmer-Study-Notes/blob/master/Content/%25E3%2580%258AGPU%2520%25E7%25BC%2596%25E7%25A8%258B%25E4%25B8%258ECG%2520%25E8%25AF%25AD%25E8%25A8%2580%25E4%25B9%258B%25E9%2598%25B3%25E6%2598%25A5%25E7%2599%25BD%25E9%259B%25AA%25E4%25B8%258B%25E9%2587%258C%25E5%25B7%25B4%25E4%25BA%25BA%25E3%2580%258B%25E8%25AF%25BB%25E4%25B9%25A6%25E7%25AC%2594%25E8%25AE%25B0/README.md)
- 《PBRT》[# 如何阅读PBRT3？](https://www.zhihu.com/question/309420057/answer/578681653)
- 《GPU PRO》1~7
- 《[# GPU Gems](https://www.zhihu.com/search?q=GPU%20Gems&search_source=Entity&hybrid_search_source=Entity&hybrid_search_extra=%7B%22sourceType%22%3A%22answer%22%2C%22sourceId%22%3A1500559999%7D)》1~3