#cg #games101

# What is AA?

AA，anti-aliasing，抗锯齿，一种*消除*显示器输出画面中图物边缘出现*凹凸锯齿*的技术。

# Why need AA?

通过采样/sampling时，将较多的资料以较少的资料点代替，*部分的资料被忽略造成取样结果失真*。

而AA则是为了在一定程度上解决这种取样失真问题而发展出来的一种技术。

# How to impelment AA?

- 全屏反锯齿（Full Scene Anti-aliasing，简称FSAA）
- 超级采样抗锯齿（[Super-Sampling Anti-aliasing (SSAA)](Super-Sampling%20Anti-aliasing%20(SSAA).md)）
- 多重采样抗锯齿（[Multisampling Anti-Aliasing (MSAA)](Multisampling%20Anti-Aliasing%20(MSAA).md)）
- 覆盖采样抗锯齿（Coverage Sampling Anti-Aliasing，简称CSAA）
- 可编程过滤抗锯齿（Custom Filter Anti-Aliasing，简称CFAA）
- 快速近似抗锯齿（Fast Approximate Anti-Aliasing，简称FXAA）
- 时间混叠抗锯齿（Temporal Anti-Aliasing，简称TXAA）
- 深度学习抗锯齿（Deep Learning Anti-Aliasing，简称DLAA）
	- 深度学习超高采样（Deep Learning Super-Sampling，简称DLSS）：目的是提高4K或8K超高屏幕分辨率下的帧率