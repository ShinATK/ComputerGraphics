#cg

# What is Ray Tracing?

> A technique for **modeling light transport** for use in a wide variety of rendering algorithms for generating digital images.

---

# Why Ray Tracing?

- Advantages:
	- *More realism* because of its basis in a realistic simulation of **light transport**, compared to other rendering methods, such as [[01-Rasterization]], which is focus on more realistic simulation of geometry.
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

The basic thing for geometric ray tracing algorithm is [[Ray Casting]]. Follow the light path, we will find the light source.

But in Ray Casting, it just about the direct illumination of the light source. What about reflection from other objects and so on?

### Recursive Ray Tracing

We know the [Ray Casting](Ray%20Casting.md) algorithm determined the ray color without recursively tracing more rays. And [[Recursive Ray Tracing]] or Whitted-Style Ray Tracing continues the process.

And this algorithm seems not bad. So it is time to think about how to describe a ray hits an object.

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

We can find a larger region, says [[Bounding Volumes]], that can barely hold the object, and determine if the ray has an intersection with this region. 

If not, there is definitly no way to have a intersection between ray and object.

### Spatial Partitions

- Grids

- Oct-Tree
- [[KD-Tree]]
- BSP-Tree

### Object Partitions

#### Bounding Volume Hierarchy (BVH)

An object belongs to multiple regions in KD-Tree. To fix this, we have [[Bounding Volume Hierarchy]]

### Compare: Spatial vs Object Partitions

Spatial parition (e.g. [[KD-Tree]])
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

But, before we talk about [[Rendering Equation]], we should know some bacis [[Radiometry]].

## Bidirectionan Reflectance Distribution Function

After that, we can study the reflection of a point, see in [[BRDF]], Bidirectional Reflectance Distribution Function.

## Rendering Equation

Then, we add an Emission term into the reflection equation, and [Rendering Equation](Rendering%20Equation.md) shows up!

Methods that trace rays, but include additional techniques ([photon mapping](https://en.wikipedia.org/wiki/Photon_mapping "Photon mapping"), [path tracing](https://en.wikipedia.org/wiki/Path_tracing "Path tracing")), give a far more accurate simulation of real-world lighting.

## Solve the Rendering Equation

### Monte Carlo Integration

- [[Monte Carlo Integration]]


---

