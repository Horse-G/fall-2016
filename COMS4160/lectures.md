# Computer Graphics, COMS4160
## Lecture 02, 2016-09-15
### Schedule
1. Rendering architecture over view
2. mathematical preliminaries
3. light & images
4. <break>
5. the OpenEXR image format
6. introduction to ray tracing
7. animation appreciation!

### Class minutiae
Wednesday 6:30pm - 8pm
Thursday 8am - 9:30am

#### TA OH
- He: T 3-5
- Justin: W 4-6
- Ray: T/R 1-2

#### Programming tools
- totalview
- valgrind
- vtune
- gdp
- perf
- xcode

### Render architectures for 3D graphics, an overview
Given objects, and a plane to project on, you need to somehow convert the 3D objects down to the 2D plane.

We need a camera model. the image plane, and the geometric models.

We need the geometric transformations to convert from one to the other to the other.

We need a lighting model, and material descriptions.

We need acceleration structures.

Two common methods to do this:

#### Raytracing
The basic idea is to thnk of rays of light following simple geometric principles (but in reverse).
Generate rays from the focal point, through an image pixel, and to the first image it hits. Pixel is colored depending on the amount of light hitting that object.

Operations:
- ray-object intersections
- shading

#### Pipeline rendering
Objects are primitives that are projected to the image frame, closest objects placed on the image.

Operations:
- dicing ( tesselation)
- shading
- geometric transformations
- perspective projections
- optimized sorting for handling occlusion

#### Raytracing vs pipelines
Raytracing is better for theory (high quality images)

Pipelines are fast

Interactive rendering use pipelines, but things with physics as the basis use raytracing

### Mathematical preliminaries
#### Points
Denote locations in any n-dimension.
A **point** is an n-tuple for a given n-dimension.

#### Vectors
**Vectors** describe both orientation and magnitude. An n-tuple for a given n-dimension.

2 equivalent if same orientation & magnitude.

Unit vector is length 1.

Dot product is a projection.

Cross product is a vector result.

**vector base** any nD vector can be written as a combination of two non-zero, non parallel nD vectors

#### Coordinate systems
Comes from bases

#### Equation forms
#### Linear interpolation
This is important
ratio 0:t:1 == x0:xt:x1

#### Barycentric combinations
where coefficients sum to 1

### Light & vision
#### Dual nature of light
wave-particle duality - light acts as both

#### Spectral power distribution

#### Tristimulus theory of color vision

#### Metamers

#### We default to RGB
Can ecnode this color as a 3-tuple
3 values scaled from 0 to 1.

Unless you know something specific,
- a pixel is a point sample
- an image is an array of point samples


### Pixel data types
- 1 bit, b&w - like e-ink
- 8 bit rgb - web & email images
- 12-16 bit rgb - highend digital cameras
- 16 bit greyscale - medical imaging
- 16 bit float rgb - HDR images & rendering
- 32 bit float rgb - even better HDR

#### Whats the dif between 16 bit FLOAT vs FIXED POINT
**dynamic range** specifies the maximum contrast possible, and is a major factor in image quality

floating point starts skipping values at higher end of the range

### OpenEXR Image Format
- developed by ILM
- support 16-bit and 32 bit formats
- multiple lossless compression algorithms
- scan-line & tile-based methods
- portable & extensible
- compatible with graphics hardware

#### interface
- using simple interface
- half pixels
- rw rbga files
- addressing scanline-bsed images

#### coordinates
- 0,0 is the upper left
- difference between display and data, bc you only may want to process a smaller section
- we will be assuming the same

#### half-pixel
struct of 4 halfs

## Lecture 03, 2016-09-21
### Recap
We will always talk about light in terms of geometric optics (light as a particle).

Due to metamerism, we can use RGB to represent colors.

The raytracing algorithm is very intuitive. It extends to mant secondary phenomena, like shadows, refraction, multiple lights.
- produces very realistic images
- weak becuse not good for things like diffuse inter-reflection
- weak because it is slow

### Ray tracing
#### Recap
for each pixel:
- computer ray through current pixel
- intersect with scene
- compute shading at intersection point
- put shading value in pixel

#### Shadows
Make a second ray from the intersection point to light source, compute distance to find the right amount of shadow.

#### Reflections
Find complement ray and compute the energy coming from another point.

### Refraction
Find other complement ray to find energy coming from another point.

### Multiple lights
Need to compute multiple rays at the points, to each of the light sources.

### New psuedocode
for each pixel:
- compute the ray through the current pixel (primary ray)
- intersect eay with the scene
- trace shadow rays to all lights
- compute illumination/shading at the intersection point
- if the surface is reflective, trace a reflection ray
- if the surface is transparent, trace a transmission ray
- combine shading, reflectance, transmission contributions into pixel value
- (if ray missed all objects, set color to background value)

Basically generating a tree of rays

### Benefits
provides an easily-understood solution to visibility determination from any **point in the scene**

automatically generates images

### Intro to materials
Light is partially absorbed by materials before the bounce off to another direction

In reflection
Reflection is outscattered, transmission is inscattered

In opaque objects, some light is reflected, bu the rest is absorbed. Reflected light is the specular contribution, but absorbed light is the diffuse contribution.

#### How do we characterize reflectance geometrically?
- the angle of the ray to the surface
- the angle of the light to the surface
- the normal direction at the specific position on the surface

How these affect the exiting energy is described by the **shading model**

#### Simple material description
specular reflection is an RGB triple (in [0,1])

diffuse reflection is an RGB triple (in [0,1])

The shading combines these with an RGB triple that describes the incidient light energy (could be > 1) to produce an RGB triple describing the emitted energy along a ray (could be > 1)

#### Modeling the systems
- way to represent rays
- camera model
- geometric models
- way to represent lights
- shading model
- support classes: image

### Signal processing
### Hw 1.1 overview
### Animation Appreciation

"The Adventures of Andre and Wally B."

## Lecture 04, 2016-09-29
what we'll need

- a away to represent and work with rays
- a camera model
- geometric models - for the objects in our scene
- a way to represent lights
- a shading model, simple material descriptions
- support classes: image, point/vector/intersection

### rays
defined as linear interpolation of a point and a vector

_r(t) = P\_0 + td_

```c++
class ray
{
public:
	point origin;
	vector dir;
};
```

### pinhole camera model
camera coordinate frame

- the eye point
- vector w (opposite the viewing direction)
- vector u ( the camera's right)
- vector v ( the camera's up)

the three vectors are orthonormal

```c++
class camera
{
	point eye;
	float d;
	vector u;
	vector v;
	vector w;
	...
};
```

### Basic geometries
#### Planes
planes ca nbe used to represent limitless ground. They can be useful as a bounding surface in acceleration structures

implicit equation for a place with normal N and distance to origin d:

_p dot N + d = 0_

```
class plane: public surface
{
	vector normal;
	float d; // distance to origin
}
```

##### ray-plane intersection
System of equations with the plane equation and the ray formula, and solve for t.

The dot product of orthogonal vectors is 0 (and then there won't be an interesection)

##### create a plane
from 3 points - cross products to compute normal

#### Spheres
- useful as test objects
- useful for bounding objects (complex ones)
- useful for representing sky
- are not flat, so easy to test shading

```
class sphere: public surface
{
	point center;
	float radius;
}
```

- descriminant negative: line and sphere do not interest
- descriminant zero: 1 interesction (graze). hard to compute with floats - have a magnitude check for < than error
- otherwise: the two intersect

### Ray-surface intersections
- yes/no intersection
- 't' the parameterization of the intersection point
- **intersection point** for shading
- **geometric normal** for shading
- surface id - so we can look up materials
- all this suggests an intersection class

### Images and signal processing

### Assignment 1.0
Write, test, and evaluate a raytracing renderer named **raytra**

eventually, it will include:

- multiple light sources
- multiple geometry types
- diffuse, specular, & mirror reflection models
- refraction on transparent materials
- spatial acceleration structures

#### Basics
- scene file read
- camera & image setup
- primary ray generation
- ray/sphere interersection
- no shading, lights
- need basic materials

for each pixel:
- compute the ray through current pixel (primary ray)
- intersect ray with scene
- if ray missed all objects, set color to background value

## Lecture 05, 2016-10-06
Homework will include shading, and ray plane intersections.

### Scattering & absorption
Reflection vs transmission

Specular reflection comes straight off

diffuse reflection bounces in object and then leaves, independent of viewer position.

### difuse component
diffusely reflected ligh = diffuse coefficeint * illuination from source * max(0, n_hat dot l)

### specular component
strongest when object is basically acting like a mirror with the light

specularly reflected light = specular coefficeint * illumination from source * max(0, n dot h)^(phong exponent)

where h = bisector(v,l) = (v + l)/(v + l).norm()

### ambient contribution
reflected ambient light = ambient coefficient * illumination from sourc

### Blinn-Phong shading
L = l_ambient + l_diffuse + l_specular

= k_a*I_a + k_d*I*max(0,n dot l) + k_s*I*max(0,n dot h)^p

### types of lights
- point
- directional
- area
- spotlight (w flaps)
- volumetric
- ambient

```class point
 point position
 rgb triple
 float intensity
 ```
### homework 1.1
 shading calcuatioin
 - surface normal at interesection point
 - normlized vector from interesection point to light
 - normalized vector opposite camera ray direction
 - diffuse & speculat coeeficients of hte material, and its phong exponents

### code overview
DELETE ALLOCATED MEMORY YOURSELF

MAKE VECTOR INVERT A FUNCTION

MAKE VECTOR NORMALIZE

MAKE VECTOR A 3 SCALAR ARRAY

friend istream &operator>> FOR INSIDE A CLASS

NORMALIZE HAS TO ASSERT THAT IT IS NOT ALL ZERO

PUT VIRTUAL IN ALL THE SUBCLASS VIRTUAL FUNCTIONS


## Lecture 06, 2016-10-13
- raytracing triangles
- raytracing "true" shadows
- raytracing multiple light sources
- code review on 1.1 additions
- animation appreciation "knick knack"

### Raytracing triangles
- can be used to represent any shape, to a desired error
- they fit well into ray tracing and pipeline paradigms
- they are easy to subdivide into smaller triangles
- most freeform geometry tyles have well-defined methods of tesselation by triangles
- they are fast to compue intersections with
- DISADVANTAGES: only approximates smooth surfaces, without extra work norals are not smooth, all the other problems associated w/ sampling

#### ray-triangle intersection
- (b-a)x(p-a) . n > 0
- (c-b)x(p-b) . n > 0
- (a-c)x(p-c) . n > 0
- logical, not efficient

instead:
- use barycentric coordinates
- P(B,G) = a + B(b - a) + G(c - a), in triangle if B+G <= 1
- given ray equation: r(t) = P0 + td
- P0 + td = a + B(b-a) + G(c-a)
- td - B(b-a) - G(c-a) = a - P0
- td + B(a-b) + G(a-c) = a - P0
- [ d (a-b) (a-c)].[t B G]^T = a - P0
- 3x3 * 3x1 = 3x1 => use Cramer's rule
- have intersection routine throw away if already found an object in front

### Other objects: triangle mesh
- share vertices
- share normals

### Other other objects
- parallelpipeds
- cones, cylinders, disks, paraboloids
- convex polygons
- concave polygons

### Shadows
- compute ray to light, if object between light surface, black it out
- push object up from the normal first, then compute the shadow ray (bc you might accidentally intersect object again bc of rounding) 1e-6 works for test scenes
- instead you could check normal dot ray to light is positive

## Lecture 07, 2016-10-20
### profiling code
Graphics is a very "optimization-centric" culture

the faster algorithm, and the faster implementation, make better
- images
- products
- papers

in rendering, so many operations are repeated, sloppiness will become evident

because of this, profiling is very common - use it to identify where time is being taken up

via:
- external tools
- or permanently intrument your code

simplest is
- UNIX `time`
- gprof statistical profiler (-pg option on g++)
- getrusage (instrument your code yourself)

#### gprof
- compile with -pg
- run executable
- process output

### Mirror reflection
- perfectly shiny surface doesn't have a highlight
- instead there's the reflection of other objects
- can render using recursive ray tracing
	- to find out mirror reflection radiance, ask what color is seen from surface point in reflection direction
	- shiny material has mirror reflection and diffuse


- must generate a new ray that return an spd ("color") from its scene intersection & lighting
	- call it radiance
- must limit recursion because otherwise you could get trapped

#### let's compute
r = v + 2*((n.v)n - v) = 2*(n.v)n - v

#### recursive ray tracing
l = [diffuse + specular + ambient] + k_reflective*ray_code(reflected ray)
if k_reflective = 0, then don't recurse!

#### to compute ray r

### Refractions
- every material has an index of refraction
- refracted ray `t`, along angle phi
- n sin theta = nt * sin phi
- b = orthogonal vector to n

- t = sin phi * b - cos phi * n
- d = sin theta * b - cos theta * n

#### light's color
color changes through refraction according to de beer's law

I = I0 * e^(ln(a)*s)

### recursive ray tracing architecture
- the loop is now checking each pixel, each object, each light, and then each object again for shadow-ray
- it's getting complicated

```
rgb L ( ray, min_t, max_t, recursion_limit, ray_type, light, ... )
```

### Acceleration structures
- divide up space to not need to check every object

#### bounding volumes
- spatially bound geometric objects with something much simpler than object it bounds
- reduce number of ray-intersection or containment tests with the complex geometry
- based on a quick rejection - "hit" on bounds may still miss object, but a "miss" definitely misses the object
- bounds are not rendered (but you could for debugging)

#### axis aligned bounding boxes
- surround each object with a bounding box




















