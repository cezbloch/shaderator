//--------------------------------------------------------------------------------------
// File: ComputeShaderSort11.hlsl
//
// This file contains the compute shaders to perform GPU sorting using DirectX 11.
// 
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

#include "shaderator.h"

#define BITONIC_BLOCK_SIZE 16//512

#define TRANSPOSE_BLOCK_SIZE 16

//--------------------------------------------------------------------------------------
// Constant Buffers
//--------------------------------------------------------------------------------------
SHADERETOR_CBUFFER(CB, 0)
SHADER_OPEN
    unsigned int g_iLevel;
    unsigned int g_iLevelMask;
    unsigned int g_iWidth;
    unsigned int g_iHeight;
SHADER_CLOSE

//--------------------------------------------------------------------------------------
// Structured Buffers
//--------------------------------------------------------------------------------------
StructuredBuffer<unsigned int> SHADERATOR_REGISTER_T(Input, 0);
RWStructuredBuffer<unsigned int> SHADERATOR_REGISTER_U(Data, 0);

//--------------------------------------------------------------------------------------
// Bitonic Sort Compute Shader
//--------------------------------------------------------------------------------------
SHADERATOR_GROUPSHARED_ARRAY(unsigned int, shared_data, BITONIC_BLOCK_SIZE);

SHADERATOR_NUM_THREADS(BITONIC_BLOCK_SIZE, 1, 1)
void BitonicSort(SHADERATOR_SV_DispatchThreadID(DTid), 
                 SHADERATOR_SV_GroupID(Gid),
                 SHADERATOR_SV_GroupThreadID(GTid),
                 SHADERATOR_SV_GroupIndex(GI))
{
    // Load shared data
    shared_data[GI] = Data[DTid.x];
    GroupMemoryBarrierWithGroupSync();
    
    // Sort the shared data
    for (unsigned int j = g_iLevel >> 1 ; j > 0 ; j >>= 1)
    {
        SHADERATOR_TYPE(unsigned int) result = ((shared_data[GI & ~j] <= shared_data[GI | j]) == (bool)(g_iLevelMask & DTid.x))? shared_data[GI ^ j] : shared_data[GI];
        GroupMemoryBarrierWithGroupSync();
        shared_data[GI] = result;
        GroupMemoryBarrierWithGroupSync();
    }
    
    // Store shared data
    Data[DTid.x] = shared_data[GI];
}

//--------------------------------------------------------------------------------------
// Matrix Transpose Compute Shader
//--------------------------------------------------------------------------------------
SHADERATOR_GROUPSHARED_ARRAY(unsigned int, transpose_shared_data, TRANSPOSE_BLOCK_SIZE * TRANSPOSE_BLOCK_SIZE);

SHADERATOR_NUM_THREADS(TRANSPOSE_BLOCK_SIZE, TRANSPOSE_BLOCK_SIZE, 1)
void MatrixTranspose( SHADERATOR_SV_DispatchThreadID(DTid), 
                      SHADERATOR_SV_GroupID(Gid),
                      SHADERATOR_SV_GroupThreadID(GTid),
                      SHADERATOR_SV_GroupIndex(GI))
{
    transpose_shared_data[GI] = Input[DTid.y * g_iWidth + DTid.x];
    GroupMemoryBarrierWithGroupSync();
    uint2 XY = DTid.yx - GTid.yx + GTid.xy;
    Data[XY.y * g_iHeight + XY.x] = transpose_shared_data[GTid.x * TRANSPOSE_BLOCK_SIZE + GTid.y];
}
