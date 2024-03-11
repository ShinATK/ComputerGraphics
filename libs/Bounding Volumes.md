#cg #games101

# What is Bounding Volumes?

Wiki says,
> In computer graphics and computational geometry, a bounding volumes (or bounding region) for a set of objects is a closed region that completely contains the union of the objects in the set.

In my way, **Bounding Volume** is a *Area* that can barely hold the object.

In 3D, it's a **Cuboid**. In 2D, it's a **Rectangle**. In dynamical simulation, **Bounding Sphere** or **Cylinders** are preferred.

Most of all, it must be a simple shape.

![Bounding Regionm](../img/Pasted%20image%2020231129172602.png)

# Why need Bounding Volumes?

Before this, we talk about the [Ray-Surface Intersection](Ray-Surface%20Intersection.md), and it is really waste of time when exhaustively check every triangle. We want to avoid some obviously no-intersection triangle's computation.

Because, Bounding Volume can barely hold the object, so we can say, if ray has *no intersection with the Bounding Region*, there is *definitly no way to have a intersection between ray and object*.

# How to build a Bounding Volumes?

There are many various Bounding Volumes for different purposes or research fields.

But here I just talk about a 3D bounding area for now.

## Bounding Box

### Axis-Aligned Bounding Box

Box, is the intersection of 3 pairs of slabs.

![Bounding Box](../img/Pasted%20image%2020231129173420.png)

Specifically, **Axis-Aligned Bounding Box (AABB)** is often used.

> i.e. any side of the BB is along either x, y, or z axis

### Ray-AABB Intersection

Here are schematic diagrams, 2D examples, but 3D is the same.

![Ray-AxisAlignedBox Intersection, 2D](../img/Pasted%20image%2020231129173711.png)

- Left one, ray intersects with line $x=x_0$ and $x=x_1$, two intersections, $t_{x_{min}}$ and $t_{x_{max}}$.
- Mid one, with line $y=y_0$ and $y=y_1$, two intersections, $t_{y_{min}}$ and $t_{y_{max}}$.

Make a intersection, we can know the time of entering box $t_{enter}$ and the time of exiting box $t_{exit}$

- It is kind like, find the intersection between these two pairs.
- And note that: *$t_{min}$ can't be negative*

This is the 2D situation, but *what about 3D*?

Key ideas:
- The ray enters the box *only when* it enters all pairs of slabs
- The ray exits the box *as long as* it exits any pair of slabs

So for each pair, calcultate the $t_{min}$ and $t_{max}$, (*negative is fine, but later need care about this*). Then we will know the entering time and exiting time:

$$t_{enter} = \max(t_{min})$$

$$t_{exit} = \min(t_{max})$$

*Some discussions:*
$t_{enter}<t_{exit}$: ray *stays a while* in the box, must intersect
- check time if negative
$t_{exit}<0$: box is behind the ray, no intersection
$t_{exit}>0\ and\ t{enter}<0$: ray's region is inside the box, have intersection

In summary, ray and AABB intersect iff
$t_{enter}<=t_{exit}\ and \ t_{exit}>=0$

