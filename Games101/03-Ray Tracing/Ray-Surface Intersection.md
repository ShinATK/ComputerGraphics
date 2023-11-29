#cg 

# Why to do this?

Because we need a method or mathematical way to determine a ray whether goes through an object or not.

# What is this?

A line intersects a surface.

In mathematic, just solving two equations simultaneously

# How to do this?

## Ray Equation

Ray is defined by its **origin** and a **direction** vector.

$$\vec{r}(t) = \vec{o}+t\cdot\vec{d}, \ 0\le t < \infty$$
- $\vec{r}$: point along ray
- $t$: time
- $\vec{o}$: origin
- $\vec{d}$: normalized direction

## Surface

### Implicit Surface

- General implicit surface: $\vec{p}:\ f(\vec{p})=0$
- With ray equation:$f(\vec{o}+t\cdot\vec{d})=0$
- And solve for *real*, *positive* roots

#### Sphere
##### Sphere Equation

Sphere is defined by its **center** and its **radius**.

$$(\vec{p}-\vec{c})^2-R^2=0$$
- $\vec{p}$: a given point of the sphere
- $\vec{c}$: center of the sphere
- $R$: radius of the sphere

##### Ray-Sphere Intersection

$$(\vec{o}+t\cdot\vec{d}-\vec{c})^2 - R^2=0$$

Remeber choose the meaningful solutions

### Explicit Surface

#### Triangle Mesh

*Ignoring multiple intersections, just consider 0 or 1 intersection*

Consider triangle is in a plane, so:
- *Ray-plane intersection*
- *Test if hit point is inside triangle*

Though there are many ways to optimize

##### Plance Equation

Plane is defined by normal vector and a point on plane.

$$\vec{p}: (\vec{p}-\vec{p'})\cdot\vec{N}=0$$
- $\vec{p}$: all points on plane
- $\vec{p'}$: one point on plane
- $\vec{N}$: normal vector

##### Ray-Plane Intersection

Solve for intersection, set $\vec{p}=\vec{r}(t)$

$$\begin{align}
(\vec{p}-\vec{p'})\cdot\vec{N} &= (\vec{o}+t\cdot\vec{d}-\vec{p'})\cdot\vec{N}=0 \\
t &= \frac{(\vec{p'}-\vec{o})\cdot\vec{N}}{\vec{d}\cdot\vec{N}}
\end{align}$$
- *Check*: $0\le t < \infty$

And here is a special situation, when the plane is parallel to an axis-plane. The normal vector can be outclouded, just $$t = \frac{(\vec{p'}-\vec{o})}{\vec{d}}$$

##### Moller Trumbore Algorithm

This is a faster approach, giving [Barycentric](Barycentric.md) coordinate directly.

$$\vec{O}+t\cdot\vec{D}=(1-b_1-b_2)\vec{P_0}+b_1\vec{P_1}+b_2\vec{P_2}$$

By barycentric coordinate,

$$\begin{align}

\begin{bmatrix*}
	t \\ b_1 \\ b_2
\end{bmatrix*} = \frac{1}{\vec{S_1}\cdot\vec{E_1}}

\begin{bmatrix*}
	\vec{S_2}\cdot\vec{E_2} \\ \vec{S_1}\cdot\vec{S} \\ \vec{S_2}\cdot\vec{D}
\end{bmatrix*}

\end{align}$$
where,
$$
\begin{align}
&\vec{E_1} = \vec{P_1}-\vec{P_0}\\
&\vec{E_2} = \vec{P_2}-\vec{P_0}\\
&\vec{S} = \vec{O}-\vec{P_0}\\
&\vec{S_1} = \vec{D}\times\vec{E_2}\\
&\vec{S_2} = \vec{S}\times\vec{E_1}
\end{align}$$

Use barycentric coordinates to determine if the intersection is inside the triangle:

$$b_1>0\ \&\&\ b_2>0\ \&\&\ (1-b_1-b_2)>0$$



