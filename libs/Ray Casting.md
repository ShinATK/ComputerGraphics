#cg #games101
# What is Ray Casting?

A **methodological basis**, for solid modeling and image rendering.

The most basic of many geometric ray tracing algorithms.

---

# Why Ray Casting?

It is *simple* and *fast*.

no need to recursive computing additional rays

which means there will be many *details lost*.

---

# How to do Ray Casting?

- Generate an image by **casting one ray per pixel**

![Ray Casting - Generating Eye Rays](Ray%20Casting%20-%20Generating%20Eye%20Rays.png)


- Check for shadows by **sending a ray to the light**

![Ray Casting - Shading Pixels(Local Only)](Ray%20Casting%20-%20Shading%20Pixels(Local%20Only).png)

This algorithm traced rays until they hit an object. But in real world, when a ray hits a surface, additional rays may be cast because of reflection, refraction, and shadow.

So the [Recursive Ray Tracing](Recursive%20Ray%20Tracing.md) algorithm continues this process.

# Ref

- [Ray casting - Wikipedia](https://en.wikipedia.org/wiki/Ray_casting)
- [Image and object order rendering - Wikipedia](https://en.wikipedia.org/wiki/Image_and_object_order_rendering)

