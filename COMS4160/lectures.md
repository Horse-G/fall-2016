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



































