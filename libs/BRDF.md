#cg #games101
# BRDF: Bidirectional Reflectance Distribution Function

## Refelction at a Pint

Radiance from direction $\omega_i$ turns into the power $E$ that $\mathrm{d}A$ receives. Then power $E$ will become the radiance to *any other direction $\omega_o$*.

![Reflection at a Point](Reflection%20at%20a%20Point.png)

- Differential irradiance *incoming*: $$\mathrm{d}E(\omega_i)=L(\omega_i)\cos\theta_i\mathrm{d}\omega_i$$
- Differential radiance *exiting* (due to $\mathrm{d}E(\omega_i)$):$$\mathrm{d}E(\omega_i) \to \mathrm{d}L_r(\omega_r)$$

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

Finally, *add an Emission term* to make "The Reflection Equation" general!

$$L_o(p,w_o)=L_e(p,w_o)+\int_{\Omega+}L_i(p,w_i)f_r(p,w_i,w_o)(\vec{n}\cdot\vec{w_i})\mathrm{d}w_i$$

We have the most important equation here, the **[Rendering Equation](Rendering%20Equation.md)**.

