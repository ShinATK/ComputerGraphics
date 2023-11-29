#cg
# Basic concept

## Radiant Energy

$Q$ barely used in CG

## Radiant Flux (Power) 

- Energy per unit time:
$$\phi \equiv \frac{dQ}{dt}$$

## Radiant Internsity 

- Power per unit solid angle

$$I(\omega)\equiv\frac{d\Phi}{d\omega}$$

## Solid Angle

### Definition

- Ratio of subtened area on sphere to radius squared

$$\Omega = \frac{A}{r^2}$$

### Differential Solid Angle

$$\begin{align}
	\mathrm{d}A &= (r \mathrm{d}\theta)(r \sin\theta\mathrm{d}\phi) \\ &=r^2 \sin\theta \mathrm{d}\theta \mathrm{d}\phi \\
	\mathrm{d}\omega &= \frac{\mathrm{d}A}{r^2} \\ &=\sin\theta \mathrm{d}\theta \mathrm{d}\phi
\end{align}$$

# Irradiance

## Definition

- The power per unit area incident on a surface point

$$E(x) \equiv \frac{\mathrm{d}\Phi(x)}{\mathrm{d}A}$$

![Irradiance](Irradiance.png)

## Lambert's Cosine Law

- **Irradiance** at surface is proportional to cosine of angle between light direction and surface normal.

![Lambert's Cosine Law](Lambert's%20Cosine%20Law.png)

## Correction: Irradiance Falloff

![Irradiance Falloff](Irradiance%20Falloff.png)
# Radiance

- The fundamental field quantity that describes the distribution of light in an environment
	- Radiance is the quantity associated with a ray
	- **Rendering is all about computing radiance**

## Definition

- *Power* (emitted, reflected, transmitted or received by a surface), *per unit solid angle*, *per projected unit area*

$$L(p,\omega) \equiv \frac{\mathrm{d}^2\Phi(p, \omega)}{\mathrm{d}\omega \mathrm{d}A \cos\theta}$$

![Radiance](Radiance.png)

- Recall
	- Irradiance: power per projected unit area
	- Intensity: power per solid angle
- So
	- Radiance: Irradiance *per solid angle*
		- **Incident Radiance**
	- Radiance: Intensity *per projected unit area*
		- **Exiting Radiance**

## Incident Radiance

- Irradiance per unit solid angle *arriving at the surface*

![Incident Radiance](Incident%20Radiance.png)

$$L(p, \omega) = \frac{\mathrm{d}E(p)}{\mathrm{d}\omega \cos\theta}$$

## Exiting Radiance

- Intensity per unit projected area **leaving the surface**

![Exiting Radiance](Exiting%20Radiance.png)

$$L(p,\omega)=\frac{\mathrm{d}I(o,\omega)}{\mathrm{d}A\cos\theta}$$

# Compare: Irradiance & Radiance

- Irradiance: total power received by area $\mathrm{d}A$
- Radiance: power received by area $\mathrm{d}A$ from "direction" $\mathrm{d}\omega$


