#cg

# What is Ray Tracing?

> A technique for **modeling light transport** for use in a wide variety of rendering algorithms for generating digital images.

---

# Why Ray Tracing?

- Advantages:
	- *More realism* because of its basis in a realistic simulation of **light transport**, compared to other rendering methods, such as [[01-Rasterization]], which is focus on more realistic simulation of geometry.
		- **Reflections** and **shadows** can be difficult to other algorithms, but are natural result of the ray tracing algorithm.

But there are some disadvantages also:
- **Performance**: a serious one
- Traditional ray tracing is also not necessarily [photorealistic](https://en.wikipedia.org/wiki/Unbiased_rendering)

---

# How to do Ray Tracing?

## Some simple and basic Ray Tracing Algorithms

### Ray Casting

The basic thing for geometric ray tracing algorithm is [[Ray Casting]].

### Recursive Ray Tracing

But this algorithm determined the ray color without recursively tracing more rays. And [[Recursive Ray Tracing]] or Whitted-Style Ray Tracing continues the process.

### Ray-Surface Intersection

We have the ray tracing algorithm, then think about *how to determine a ray has an intersection with a surface*, in short [[Ray-Surface Intersection]]

Let's recall our ray-surface intersection,
- exhaustively check intersection with every triangle
- find the cloest hit (i.e. minimum t)

A serious problem, *check every triangle is really waste of time*.
- like, $\#pixels \times \#triangles \times \#light\_bounces$
- Is there any way to accelerate, or saying *avoid useless calculation*s?

## Accelerating Ray-Surface Intersection

Sure there is!

### Bounding Volumes

We can find a larger region, says [[Bounding Volumes]], that can barely hold the object, and determine if the ray has an intersection with this region. If not, there is definitly no way to have a intersection between ray and object.

### Spatial Partitions

#### Uniform SP - Grids



## Rendering Equation

Traditional ray tracing is also not necessarily [photorealistic](https://en.wikipedia.org/wiki/Unbiased_rendering). 

*True photorealism occurs when the [rendering equation](https://en.wikipedia.org/wiki/Rendering_equation "Rendering equation") is closely approximated or fully implemented.*

So, let's talk about [[Rendering Equation]]
- [[Radiometry]]
- [[BRDF]]


Ray tracing, if it is limited to Whitted's algorithm, is not necessarily the most realistic.

Methods that trace rays, but include additional techniques ([photon mapping](https://en.wikipedia.org/wiki/Photon_mapping "Photon mapping"), [path tracing](https://en.wikipedia.org/wiki/Path_tracing "Path tracing")), give a far more accurate simulation of real-world lighting.

---

