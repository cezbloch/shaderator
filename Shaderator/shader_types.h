#pragma once

#define GLM_FORCE_SWIZZLE // this is to enable vector swizzling ie. some_vector.rgb
#include <glm/glm.hpp>
#include <glm/vec2.hpp> // glm::vec3
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <vector>

#define groupshared
#define RWStructuredBuffer std::vector
#define StructuredBuffer std::vector

typedef glm::bvec2 bool2;
typedef glm::bvec3 bool3;
typedef glm::bvec4 bool4;

typedef unsigned int uint;
typedef glm::uvec2 uint2;
typedef glm::uvec3 uint3;
typedef glm::uvec4 uint4;

typedef glm::ivec2 int2;
typedef glm::ivec3 int3;
typedef glm::ivec4 int4;

typedef glm::vec2 float2;
typedef glm::vec3 float3;
typedef glm::vec4 float4;

typedef glm::mat<2, 3, int, glm::highp>	int2x3;
typedef glm::mat<2, 3, uint, glm::highp>	uint2x3;