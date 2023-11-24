# Shadow Mapping

![](../img/Pasted%20image%2020231124151842.png)

**最重要的思想**
- 如果点不在阴影里，那么一定可以同时被*光源*和*相机*看到

**Shadow Mapping只能处理点光源**，硬阴影

# Why Ray Tracing?

- Rasterization couldn't handle **global** effects well
  - (Soft) shadows
  - especially when the light bounces **more than once**
- ![why光线追踪](../img/why光线追踪.png)

