#cg #games101

# What is Recursive Ray Tracing?

In [Ray Casting](Ray%20Casting.md), we know how to traced a ray until it hits an object. But this algorithm just stops here. No consideration of additional rays' generation because of reflection, refraction, and shadow.

[Recursive Ray Tracing](Recursive%20Ray%20Tracing.md) is going to *continue this process*.

# Why is Recursive Ray Tracing?

Recursive Ray Tracing = Whitted-Style Ray Tracing

After ray hits a surface, many additional rays casted:

- **Reflection ray**
	- Traced in mirror-reflection direction
- **Refraction ray**
	- Traveling through transparent material
	- Can entering or exiting a material
- **Shadow ray**
	- Traced toward each light to see if there are any objects blocked it's way.
	- If so, there must be a shadow of the block object on the ray's origin point.

- These recursive rays add *more realism* to ray traced images.

# How to do Recursive Ray Tracing?

Let's continue the process of [[Ray Casting]].

- Cast a ray per pixel, and Sending a ray to the light.

![RayCasting-Steps](Pasted%20image%2020231129160947.png)

- Then, we should take reflection, refraction and shadow into consideration.

![Recursive Ray Tracing](Pasted%20image%2020231129161120.png)

Ray casted from eye per pixel called, **primary ray**. And then the rays that sended to the light called, **shadow rays**, the rest rays called, **secondary rays**, because they are reflected or refracted from other objects.

Let's stop here, and think about *how to determine a ray has an intersection with a surface*, see in [[Ray-Surface Intersection]]




