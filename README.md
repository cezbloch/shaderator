# What is this?
Shaderator is a productivity library intended to speed up complex Compute Shader development. It also provides means to Unit Tests shader code offering protection against regressions.

# What problem does it solve?
Due to the nature of GPUs shaders are hard to debug. Back in the day developer wrote one, executed a batch and hoped for the best that the result is correct. Kernel function is usually executed hundreds of thousand times writing data to output buffer which can only be looked up when the Dispatch finished. This tool compiles .hlsl shader code to C++ and enables developer to leverage full Visual Studio debugging functionality to quickly find problems in the code.

# Will this work with any shader?
No, this is just a prototype - a proof of concept. If there is interest, support for more HLSL language features will be added.

# Getting started with debugging

1. Open ComputeShaderSort11\ComputeShaderSort11_2017_Win10.sln in VS 2017
2. Build solution (better Debug to see more variables under debugger)
3. In ComputeShaderSort11 project properties -> Debugging -> working directory -> set to "..\Shaderator"
4. Put breakpoint anywhere in ComputeShaderSort11.hlsl shader file
5. Press F5 to Debug

![](http://oi65.tinypic.com/358dwm1.jpg)

VS will start regular debugging session and you will be able to debug the .hlsl shader code as C++ code. You can see all variables, can add them to watch, pin or look-up values when hovering the mouse.
CPU shader is obviously very slow. The intention is to provide tools for faster Computer Shader development.

![](http://oi67.tinypic.com/1zp6rvc.jpg)

# Getting started with Unit Tests

1. Open ComputeShaderSort11\ComputeShaderSort11_2017_Win10.sln in VS 2017
2. Build solution
3. Set processor architecture for Unit Tests. In VS menu go to "Test -> Test Settings -> Default Processor Architecture" and select the platform for which you have built the solution (X86 or X640.
4. Open Test Explorer. In VS menu go to "Test -> Windows -> Test Explorer"
5. In Test Explorer right click on the Unit Test found and press "Run Selected Tests" or "Debug Selected Tests"

# Pre-requisites

* Windows 10
* Visual Studio 2017

# Problems or feedback

Please e-mail me at cez dot bloch at gmail dot com, you can also find email on my github profile.