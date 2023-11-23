## C++基础

- [CMake](https://github.com/ttroy50/cmake-examples)
- [《C++ Primer 中文版（第 5 版）》](C++%20Primer%20中文版（第%205%20版）.pdf)
- 《Effective C++》
- 《STL源码剖析》
- 《深度探索C++》
- [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
- [现代C++教程：高速上手](https://changkun.de/modern-cpp/)
- [高性能并行编程与优化](https://github.com/parallel101/course)

## 图形学基础

- [# GAMES101: 现代计算机图形学入门 -UCSB 闫令琪](https://link.zhihu.com/?target=https%3A//sites.cs.ucsb.edu/~lingqi/teaching/games101.html)
	- 阅读材料：
		- [《Fundamentals of Computer Graphics, Fourth Edition》](Fundamentals%20of%20Computer%20Graphics,%20Fourth%20Edition.pdf)中的参考章节
		- [《3D数学基础：图形和游戏开发（第2版）》](3D数学基础：图形和游戏开发（第2版）.pdf)
- [# GAMES202: 高质量实时渲染](https://sites.cs.ucsb.edu/~lingqi/teaching/games202.html)

## 图形学进阶

- [《计算机图形学 第4版》](计算机图形学%20第4版.pdf)
	- 在学习**全局光照**那一章节的时候，建议对着下面的教程，写一个*基于Path Tracing的光线追踪渲染器*，只有99行代码
		- [# 全局光照实战](https://www.kevinbeason.com/smallpt/)
	- 建议再对着下面的教程过一遍**软渲染**。于是*摄像机设置*、*矩阵转换*、*剔除*、*光栅化*、*深度/模板测试*、*贴图*之类的概念都清楚了！
		- [# 3D C/C++ tutorials - Software rendering​](https://link.zhihu.com/?target=http%3A//www.3dcpptutorials.sk/index.php%3Fid%3D15)
		- [# Developing a Software Renderer Part 1​](https://link.zhihu.com/?target=https%3A//trenki2.github.io/blog/2017/06/06/developing-a-software-renderer-part1/)
		- 两个教程分别对应着两个不同的渲染流派
			- 基于光栅化的渲染
			- 基于光线追踪的渲染
		- 基本上所有的渲染相关的算法都是基于上面两个教程的扩展、近似、改进和优化，很多算法思路都是欺骗人眼睛的trick或者hack。

## 图形学API

- 到这里应该对图形API的意义有所了解了，可以跟着OpenGL的教程做一遍
	- [# Learn OpenGL CN](https://learnopengl-cn.github.io/)
 - [vulkan](https://vulkan-tutorial.com/)

## 图形学实战

- 实战：软光栅
- 实战：光线追踪
- 渲染进阶

参考：
- [计算机图形学应该从什么开始学习？ - 网易游戏雷火事业群的回答 - 知乎](https://www.zhihu.com/question/349302834/answer/931378785)
- [# 图形学渲染方向个人学习路线整理](https://zhuanlan.zhihu.com/p/445343440)
- [# 如何开始用 C++ 写一个光栅化渲染器？ - UncP的回答 - 知乎](https://www.zhihu.com/question/24786878/answer/127484388)
- [# 如何开始用 C++ 写一个光栅化渲染器？ - Zero的回答 - 知乎](https://www.zhihu.com/question/24786878/answer/401447840)

## 论文复现

- 尝试复现一些最新论文中的方法

---

- 参考：
[# 游戏程序员学习之路](https://miloyip.github.io/game-programmer/game-programmer-zh-cn.svg)
