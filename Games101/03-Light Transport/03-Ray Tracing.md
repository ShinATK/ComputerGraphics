#cg

# What is Ray Tracing?

> A technique for **modeling light transport** for use in a wide variety of rendering algorithms for generating digital images.

---

# Why Ray Tracing?

- Advantages:
	- *More realism* because of its basis in a realistic simulation of **light transport**, compared to other rendering methods, such as [01-Rasterization](01-Rasterization.md), which is focus on more realistic simulation of geometry.
		- **Reflections** and **shadows** can be difficult to other algorithms, but are *natural result* of the ray tracing algorithm.

But there are some disadvantages also:
- **Performance**: a serious one
- Traditional ray tracing is also not necessarily [photorealistic](https://en.wikipedia.org/wiki/Unbiased_rendering)

---

# How to do Ray Tracing?

We know that Ray Tracing is about *modeling light transport*.

The idea thought I think is that this is a *result-oriented*, and it will be better if the approach to desired result seems great.

We need to show the picture of the scene on the screen, so we need to know what is going to be shown?

We see things because of light coming into our eyes and our physical body can handle it. But focusing on every object and light source of the scene, is too hard and no need to, obviously. *We just need to show the things that we can see.*

So the things shown on the screen are all we needed to care about. One more thing, *Light path is reversible*. Follow the light path, we will find what "light source" light this object. Then, things need to care about become a little bit simpler, **the seen object and any kind of light sources that give it an illumination**.

I think this is the most obvious and basic thing that should always keep in mind.

## Some simple and basic Ray Tracing Algorithms

### Ray Casting

The basic thing for geometric ray tracing algorithm is [Ray Casting](Ray%20Casting.md). Follow the light path, we will find the light source.

But in Ray Casting, it just about the direct illumination of the light source. What about reflection from other objects and so on?

### Recursive Ray Tracing

We know the [Ray Casting](Ray%20Casting.md) algorithm determined the ray color without recursively tracing more rays. And [Recursive Ray Tracing](Recursive%20Ray%20Tracing.md) or Whitted-Style Ray Tracing continues the process.

And this algorithm seems not bad. So it is time to think about how to describe a ray hits an object.

### Ray-Surface Intersection

We have the ray tracing algorithm, then think about *how to determine a ray has an intersection with a surface*, in short [Ray-Surface Intersection](Ray-Surface%20Intersection.md)

Let's recall our ray-surface intersection,
- exhaustively check intersection with every triangle
- find the cloest hit (i.e. minimum t)

A serious problem, *check every triangle is really waste of time*.
- like, \#pixels X \#triangles X \#light\_bounces
- Is there any way to accelerate, or saying *avoid useless calculation*s?

## Accelerating Ray-Surface Intersection

Sure there is!

### Bounding Volumes

We can find a larger region, says [Bounding Volumes](Bounding%20Volumes.md), that can barely hold the object, and determine if the ray has an intersection with this region. 

If not, there is definitly no way to have a intersection between ray and object.

### Spatial Partitions

- Grids

- Oct-Tree
- [KD-Tree](KD-Tree.md)
- BSP-Tree

### Object Partitions

#### Bounding Volume Hierarchy (BVH)

An object belongs to multiple regions in KD-Tree. To fix this, we have [Bounding Volume Hierarchy](Bounding%20Volume%20Hierarchy.md)

### Compare: Spatial vs Object Partitions

Spatial parition (e.g. [KD-Tree](KD-Tree.md))
- Parition space into non-overlapping regions
- An object can be contained in multiple regions
Object parition (e.g. [Bounding Volume Hierarchy](Bounding%20Volume%20Hierarchy.md))
- Parition set of objects into disjoint subsets
- Bounding boxes for each set many overlap in sapce

---

Ray tracing, if it is limited to Whitted's algorithm, is not necessarily the most realistic.

Traditional ray tracing is also not necessarily [photorealistic](https://en.wikipedia.org/wiki/Unbiased_rendering). 

*True photorealism occurs when the [rendering equation](https://en.wikipedia.org/wiki/Rendering_equation "Rendering equation") is closely approximated or fully implemented.*

## Radiometry

But, before we talk about [Rendering Equation](Rendering%20Equation.md), we should know some bacis [Radiometry](Radiometry.md).

## Bidirectionan Reflectance Distribution Function

After that, we can study the reflection of a point, see in [BRDF](BRDF.md), Bidirectional Reflectance Distribution Function.

## Rendering Equation

Then, we add an Emission term into the reflection equation, and [Rendering Equation](Rendering%20Equation.md) shows up!

Methods that trace rays, but include additional techniques ([photon mapping](https://en.wikipedia.org/wiki/Photon_mapping "Photon mapping"), [path tracing](https://en.wikipedia.org/wiki/Path_tracing "Path tracing")), give a far more accurate simulation of real-world lighting.

## Solve the Rendering Equation

### Monte Carlo Integration

Because we want to solve the rendering equation just numerically, and it's to difficult to solve analytically.

So we can use [Monte Carlo Integration](Monte%20Carlo%20Integration.md), a particular [Monte Carlo method](https://en.wikipedia.org/wiki/Monte_Carlo_method) that *numerically computes a definite integral*, to meet our purpose.

### Try to solve the equation

The rendering equation: $$L_o(p,\omega_o)=L_e(p,\omega_o)+\int_{\Omega+}L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(\vec{n}\cdot\vec{\omega_i})\mathrm{d}\omega_i$$

The Emission term is easily known while we set the object's material feature or something else. So let's just focus on the **Direct Illumination** and **Indirect Illumination**, and render one pixel (point).

Then the equation can be rewrite:

$$L_o(p,\omega_o)=\int_{\Omega+}L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(\vec{n}\cdot\vec{\omega_i})\mathrm{d}\omega_i$$

assume all directions are *pointing outwards*(means $w_i,\ w_o$ are start from the point)

Here, we can use our **Uniform Monte Carlo Estimator** to solve the Direct Illumination first.

#### Direct Illumination

-  Monte Carlo integration: $\int^b_af(x)\mathrm{d}x \approx \frac{1}{N}\sum\limits^N_{k=1}\frac{f(X_k)}{p(X_k)}, \ X_k \to p(x)$
- $f(x)$: $L_i(p, w_i)f_r(p,w_i,w_o)(\vec{n} \cdot \vec{w_i})$
- pdf: $p(w_i) = \frac{1}{2\pi}$
	- assume uniformly sampling the hemisphere

So, in general,

$$\begin{align*}
L_o(p,w_o) &= \int_{\Omega+}L_i(p,w_i)f_r(p,w_i,w_o)(\vec{n}\cdot\vec{w_i})\mathrm{d}w_i\\
&\approx \frac{1}{N}\sum\limits^N_{i=1}\frac{L_i(p,w_i)f_r(p,w_i,w_o)(\vec{n}\cdot\vec{w_i})}{p(w_i)}
\end{align*}$$

We got *a correct shading algorithm for direct illumination*!

#### Indirect Illumination

According to our analysis, there are still *Indirect Illumination* term (like mirrors, refraction) and others that rays may bounce much more times, but we just have the equation about Direct Illumination.

Rethinking about the equation that we finally had of the Direct Illumination.

In face, it's not just representing for the Direct Illumination, but and really for *the proportional of $L_i$ and $L_o$ of the hit point*.

![Global Illumination](./img/Pasted%20image%2020231130205956.png)

- Q also reflects light to P! How much?
- *The dir.illum. at Q!*

We just need to *call this function recursively*!

#### Some Constraints

##### Problem 1: Explosion of \#rays as #bounces go up

**[Path Tracing](Path%20Tracing.md)**

![Problem-01: Explosion of ray number](./img/Pasted%20image%2020231130210245.png)

- Set $N=1$, **Path Tracing!** Only 1 ray is traced at each shading point.
- $N != 1$, Distributed Ray Tracing

##### Problem 2: Small ray number results in Noisy

**Ray Generation**, see in [Ray Casting](Ray%20Casting.md)

Trace *more paths* through each pixel and average radiance.

![Noisy-trace more paths](./img/Pasted%20image%2020231130210512.png)

##### Problem 3: Stop the Recursive Algorithm

Because the Conservation of energy, we can't just cut off some part of \#bounces.

*But we can stop bouncing with probability $p$*.

And we say, 
- With probability $P$, shoot a ray and return the *shading result divided by $P$*: $L_o/P$
- With probability $1-P$, don't shoot a ray and return 0

We can still expect to get $L_o$:

$$E=P\cdot(\frac{L_o}{P})+(1-P)\cdot 0$$

Here is one thing need to remember, radiance coming from two parts:
- *light source(direct, no need to have RR)*
- other reflectors (indirect RR), this is the global illumination term

##### Problem 4: Inefficient

![Low&High SPP](./img/Pasted%20image%2020231130211339.png)

Reason: ![Inefficient Reason](./img/Pasted%20image%2020231130211415.png)

If the light source is too small, there are going to waste a lot of rays when we uniformly sample the hemisphere at the shading point.

The core is, **we need to make sure the rays generated return some useful information**.

Fix: we can just **sample the light**!

Assume *uniformly sampling on the light*, pdf=$\frac{1}{A}$($\int pdf\mathrm{d}A=1$), A is the area of the light

But the rendering equation integrates on the solid angle: $L_o=\int L_i f_r cos \mathrm{d}\omega$, and we need to integrate on the light, need the relationship between them!

Pure math work.

Recall the alternative def. of solid angle: *Projected area on the unit sphere*

So, we can have the unit light area that projected on the sphere, and we can easily get the relationship equation(*care about the angle $\theta'$*):

$$\mathrm{d}\omega = \frac{\mathrm{d}A \cos\theta'}{||x'-x||^2}$$

![Sampling the light](./img/Pasted%20image%2020231130211718.png)

And one more thing: *care about the ray if is blocked in the middle before it hits the target point*.

---



