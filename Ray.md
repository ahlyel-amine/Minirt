# Ray takeover


1. **red note**:

* ray traced image are created by generating one ray for each pixel in the frame.
* `<primary ray>` or `camera ray` stand for the rays we cast to the scene.
+ We know that the start from the camera's origin.
+ We will also orient the camera along the negative z-axis.

*Our task consists of creating a primary ray for each pixel of the frame.*

This can easily be done by tracing a line starting at the camera's origin and passing through the middle of each pixel. 
We can express this line in the form of a ray whose origin is the camera's origin and whose direction is the vector from the camera's origin to the pixel center.
* To compute the position of a point at the center of a pixel, we need to convert the pixel coordinates which are originally expressed in *raster space* (the point coordinates are expressed in pixels with the coordinates (0,0) being the top-left corner of the frame) to world space.

## Day02

Our task today consist of creating a primary ray for each pixel of the frame. This can easily be done by tracing a line starting at the camera's origin and passing through the middle of each pixel.
but in order to compute the position of a point at the center of a pixel, we need first to convert the pixel coordinates which are originally expressed in <raster space> to *world space*.
<Raster_world_space> >> for more daitles check resource bellow.
- Converssion >> Converting the coordinates of a point in the middle of a pixel requires a banch of steps, The coordinates of this point which expressed in *raster space* plus *0.5* then convert it to *NDC space* here the coordinates are remapped to the range [0, 1].

```
ndcX = ((Pixel_x + 0.5) / ImageWidth)
ndcY = ((Pixel_y + 0.5) / imageHeight)

```
	
Then converted again to *screen space* like last converssion now we remapp it to the range [-1,1].
~~~~
	PixelScreen_x = 2 * ndcX - 1
	PixelScreen_y = 1 - 2 * ndcY
	PixelCamera_x = (2 * PixelScreen_x) * ImageAspectRatio * FOV
	PixelCamera_x = (1 - 2 * PixelScreen_y) * FOV
~~~~
	
Now we reach the final stage which consist of applying the final camera to world transformation 4x4 matrix transformas the coordinates in screen space to world space.
*secondary ray* are shadows ray.

[Ray-Tracing: Generating Camera Rays](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-generating-camera-rays/generating-camera-rays.html#:~:text=This%20can%20easily%20be%20done,origin%20to%20the%20pixel%20center).



https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/parametric-and-implicit-surfaces.html

https://gamedev.stackexchange.com/questions/172352/finding-texture-coordinates-for-plane