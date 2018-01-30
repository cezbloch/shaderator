# What is this?
Shaderator is a productivity tool intended to speed up Compute Shader development.

# What problem does it solve?
Due to the nature of GPUs shaders cannot be debugged. Developer writes one, then executes and hopes for the best that the result is correct. Hundreds of thousand threads execute the same kernel function writing data to output buffer which can only be looked up when the Dispatch finished. This tool compiles .hlsl shader code to C++ and enables developer to leverage Visual Studio functionality to quickly find problems in the code.

# Will this work with any shader?
No, this is just a prototype - a proof of concept. If there is interest, support for other shaders will be added.

# Getting started

1. Open ComputeShaderSort11\ComputeShaderSort11_2017_Win10.sln in VS 2017
2. Build Debug or Release in x64 (better Debug to see more variables under debugger)
3. In ComputeShaderSort11 project properties -> Debugging -> working directory -> set to "..\Shaderator"
4. Put breakpoint anywhere in ComputeShaderSort11.hlsl shader file
5. Press F5 to Debug

![](http://oi65.tinypic.com/358dwm1.jpg)

VS will start regular debugging session and you will be able to debug the .hlsl shader code as C++ code. You can see all variables, can add them to watch, pin or look-up values when hovering the mouse.
CPU shader is obviously very slow. The intention is to provide tools for faster Computer Shader development.

![](http://oi67.tinypic.com/1zp6rvc.jpg)

# Pre-requisites

* Windows 10
* Visual Studio 2017
