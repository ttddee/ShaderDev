# ShaderDev
**A desktop application for developing GLSL compute shaders for the purpose of image processing.**

![](/screenshots/ShaderDev01.jpg?raw=true "")

![](/screenshots/ShaderDev02.jpg?raw=true "")

# Dependencies

- [Qt](https://www.qt.io/download) >= 5.10
- [SpvShaderCompiler](https://github.com/ttddee/SpvShaderCompiler)
- [glslang](https://github.com/KhronosGroup/glslang)

# Build

The easiest way to compile is to open the project in QtCreator and compile for the desired platform.

QMake is set up for either Linux or Windows.

# Usage

Load the file **shaders/noop.comp** to see what a simple shader looks like. This one loads the image and renders it to the screen, without doing anything else.

```
#version 450

layout (local_size_x = 16, local_size_y = 16) in;
layout (binding = 0, rgba8) uniform readonly image2D inputImage;
layout (binding = 1, rgba8) uniform image2D resultImage;

void main()
{   
    ivec2 pixelCoords = ivec2(gl_GlobalInvocationID.xy);

    vec3 rgb = imageLoad(inputImage, pixelCoords).rgb;  
                                    
    vec4 pixel = vec4(rgb, 1.0);

    imageStore(resultImage, pixelCoords, pixel);
}
```

There are two bindings:

- **inputImage**: The image that was loaded from disk.
- **resultImage**: The final image that will be written to.

