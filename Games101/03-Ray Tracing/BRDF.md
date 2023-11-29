#cg 
# BRDF: Bidirectional Reflectance Distribution Function

## Refelction at a Pint

Radiance from direction $\omega_i$ turns into the power $E$ that $\mathrm{d}A$ receives. Then power $E$ will become the radiance to *any other direction $\omega_o$*.

![Reflection at a Point](Reflection%20at%20a%20Point.png)

- Differential irradiance *incoming*: $$\mathrm{d}E(\omega_i)=L(\omega_i)\cos\theta_i\mathrm{d}\omega_i$$
- Differential radiance *exiting* (due to $\mathrm{d}E(\omega_i)$):$$\mathrm{d}L_r(\omega_r)$$

## BRDF

- Represents how much light is reflected into each outgoing $\omega_r$ from each incoming direction

$$f_r(\omega_i\to\omega_r)=\frac{\mathrm{d}L_r(\omega_r)}{\mathrm{d}E_i(\omega_i)}=\frac{\mathrm{d}L_r(\omega_r)}{L_i(\omega_i)\cos\theta_i\mathrm{d}\omega_i}$$

![BRDF](BRDF.png)

## The Reflection Equation

$$L_r(p,\omega_r)=\int_{H^2}f_r(p,\omega_i\to\omega_r)L_i(p,\omega_i)\cos\theta_i\mathrm{d}\omega_i$$

![The Reflection Equation](The%20Reflection%20Equation.png)

But it's a **Recursive** Equation!

$L_r(p,\omega_r)$ and $L_i(p,\omega_i)$

- Reflected radiance depends on incoming radiance
- Incoming radiance depends on reflected radiance (at another point in the scene)

## The Rendering Equation

Add and Emission term to make "The Reflection Equation" general!

$$L_o(p,\omega_o)=L_e(p,\omega_o)+\int_{\Omega+}L_i(p,\omega_i)f_r(p,\omega_i,\omega_o)(\vec{n}\cdot\vec{\omega_i})\mathrm{d}\omega_i$$
- Assuming that all directions are pointing **outwards!**

## Understanding the Rendering Equation

$$\begin{align}
\underset{Reflected\ Light\ (Output Image)}{L_r(x,\omega_r)} &= \underset{Emission}{L_e(x,\omega_r)} + \\& \underset{Incident\ Light\ (from\ light\ source)}{L_i(x,\omega_i)} \underset{BRDF}{f(x,\omega_i,\omega_r)}  \underset{Cosine\ of\ Incident\ Angle}{(\omega_i,n)}
\end{align}$$

- Replace $L_i(x,\omega_i)$ with $L_r(x',-\omega_i)$, and the direction is inversed.

![Understanding the Rendering Equation](Understanding%20of%20rendering%20equation.png)

- Some math operations, rewrite the Rendering Equation

![Linear Operator Equation](LinearOperatorEquation.png)

- Be discretized to a simple matrix equation (or system of simultaneous linear equations)
- L, E are vectors, K is the light transport matrix
$$L = E + KL$$
![RayTracing & Extensions](RayTracing&Extensions.png)

![RayTracing](RayTracing.png)
