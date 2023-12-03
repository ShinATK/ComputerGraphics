#cg 
# Diffuse term: Lambertian (Diffuse) Shading

认为*shading和view方向无关*

一个很简单的经验关系公式

$$L_d= k_d(I/r^2)\max(0,\vec{n}\cdot\vec{l})$$

- $L_d$: diffusely refelcted light
- $k_d$: diffuse coefficient (color)
- $I/r^2$: energy arrived at the shading point
- $\max(0,\vec{n}\cdot\vec{l})$: energy received by the shading point

![Lambertian (Diffuse) Shading](Pasted%20image%2020231201172811.png)

![Produces diffuse appearance](Pasted%20image%2020231201173041.png)

# Specular Term: Blinn-Phong


认为*光强依赖于view的方向*，并且高光应该有一个重要的性质：*view的方向越靠近镜面反射的方向，所看到shading point应该越亮*

![Specular: view direction close to mirror refelction direction](Pasted%20image%2020231201173436.png)

这里定义半程向量half vector，

$$\vec{h} = bisector(\vec{v}, \vec{l}) = \frac{\vec{v}+1}{||\vec{v}+1||}$$

![half vector](Pasted%20image%2020231201173631.png)

从而可以将衡量v和R方向之间接近程度转换成判断*半程向量h和法线n*之间的接近程度，即求二者点乘。

从而可以得到高光项的经验公式：

$$L_s = k_s(I/r^2)\max(0,\cos\alpha)^p = k_s(I/r^2)\max(0, \vec{n}\cdot\vec{h})^p$$

- $L_s$: specularly reflected light
- $k_s$: specular coefficient

那么此时就有一个问题，最后的p次方是为什么？

如果我们绘制不同幂次方下$cos\alpha$在0~90°范围内的曲线，

![cosine power plot](Pasted%20image%2020231201174241.png)

如果不设置幂次方，那么会导致高光项在各个观察角度都相差不多，而现实的高光应当是在*特定角度*亮度达到最大，所以对这里取幂次方。

至此，就得到了Blinn-Phong 模型

![](Pasted%20image%2020231201174404.png)

# Ambient Term

环境光项不依赖于任何东西

$$L_a = k_a I_a$$
- $L_a$: reflected ambient light
- $k_a$: ambient coefficient

![Ambient Term](Pasted%20image%2020231201174742.png)

# Blinn-Phong Reflection Model

![Blinn-Phong Reflection Model](Pasted%20image%2020231201174854.png)

最后将三项进行相加即可得到Blinn-Phong反射模型

$$\begin{align*}
L &= L_a+L_d+L_s\\
&= k_aI_a+k_d(I/r^2)\max(0,\vec{n}\cdot\vec{l})+k_s(I/r^2)\max(0,\vec{n}\cdot\vec{h})^p
\end{align*}$$


