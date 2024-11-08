# What is this?
Shaderator is a productivity library intended to speed up complex Compute Shader development. It also provides means to Unit Tests shader code offering protection against regressions. Click on the image below to see the Lighting Talk from ACCU 2018 Conference.

[![Shaderator on ACCU 2018 Link](http://img.youtube.com/vi/WUDPdin83A0/0.jpg)](http://www.youtube.com/watch?v=WUDPdin83A0)

# What problem does it solve?
Due to the nature of GPUs shaders are hard to debug. Back in the day developer wrote one, executed a batch and hoped for the best that the result is correct. Kernel function is usually executed hundreds of thousand times writing data to output buffer which can only be looked up when the Dispatch finished. This tool compiles .hlsl shader code to C++ and enables developer to leverage full Visual Studio debugging functionality to quickly find problems in the code.

# Setup

If you use VS Code install recommended extensions from 

```configs/recommended_extensions.json```

## Linux

Install compiler and build tools

```sudo apt-get install cmake build-essential gdb```

# Building

Shaderators uses CMake to setup and run the build process.

## Linux

Run the following commands to build:

```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON ..
make
```

CMake will download the neccessary dependencies like GoogleTests.

# Unit testing

To execute unit tests run from command line run

```ctests --verbose```

When using VS Code and all the recommended extensions were installed, then tests should be visible in the 'Test Explorer UI'.


# (old instructions) Windows - Getting started with debugging 

1. Open Shaderator.sln in VS 2017
2. Build solution (better choose Debug configuration to see more variables under debugger)
3. Set ComputeShaderSort11 in examples folder as startup project (right click on the project in Visual Studio and select "Set as StartUp Project")
4. Put breakpoint anywhere in ComputeShaderSort11.hlsl shader file 
5. Press F5 to Debug

VS will start regular debugging session and you will be able to debug the .hlsl shader code as C++ code. You can see all variables, can add them to watch, pin or look-up values when hovering the mouse.
CPU shader is obviously very slow. The intention is to provide tools for faster Computer Shader development.

If you have Visual Assist X installed debugging experience may be reduced.

# Getting started with Unit Tests

1. Open Shaderator.sln in VS 2017
2. Build solution 
3. Set processor architecture for Unit Tests. In VS menu go to "Test -> Test Settings -> Default Processor Architecture" and select the platform for which you have built the solution (X86 or X64).
4. Open Test Explorer. In VS menu go to "Test -> Windows -> Test Explorer"
5. In Test Explorer right click on the Unit Test found and press "Run Selected Tests" or "Debug Selected Tests"

# Pre-requisites

* Windows 10
* Visual Studio 2017

# Will this work with any shader?
Not yet, the project is in it's early phase, however it should work with many shaders. If there is interest, support for more HLSL language features will be added.
At the moment matrices are not supported yet.

# Problems or feedback

Submit any issues on github. Feel free to contact the author directly with information available on github.
