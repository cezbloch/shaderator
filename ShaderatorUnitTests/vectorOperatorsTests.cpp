#include "stdafx.h"
#include "CppUnitTest.h"

#include <shader_types.h>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace glm {
  template<typename T, qualifier Q>
  GLM_FUNC_DECL std::wstring ToString(vec<2, T, Q> const& v)
  {
    return std::wstring();
  }

  template<typename T, qualifier Q>
  GLM_FUNC_DECL std::wstring ToString(vec<3, T, Q> const& v)
  {
    return std::wstring();
  }

  template<typename T, qualifier Q>
  GLM_FUNC_DECL std::wstring ToString(vec<4, T, Q> const& v)
  {
    return std::wstring();
  }

  template<typename T, qualifier Q>
  GLM_FUNC_DECL std::wstring ToString(mat<2, 3, T, Q> const& m)
  {
    return std::wstring();
  }
}

namespace ShaderatorUnitTests
{
  // HLSL language features I have experimented with however I have pulled them out 
  // because current shader examples do not need them. They required changes in glm library.
  TEST_CLASS(VectorOperatorsTests)
  {
  public:

    //TEST_METHOD(TestAssignmentUint4)
    //{
    //  uint4 expected(1, 1, 1, 1);
    //  
    //  uint4 actual = 1;

    //  Assert::AreEqual(actual, expected);
    //}

    //TEST_METHOD(TestAssignmentInt3)
    //{
    //  int3 expected(1, 1, 1);

    //  int3 actual = 1;

    //  Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestAssignmentFloat2)
    //{
    //  float2 expected(1.0, 1.0);

    //  float2 actual = 1.0;

    //  Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestBitShiftInt2)
    //{
    //  int2 expected = 8;
    //  int2 actual = 1;

    //  actual = actual << 3;

    //  Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestBitShiftUint3)
    //{
    //  uint3 expected = 4;
    //  uint3 actual = 1;

    //  actual = actual << 2;

    //  Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestBitShiftInt4)
    //{
    //  int4 expected = 32;
    //  int4 actual = 1;

    //  actual = actual << 5;

    //  Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestBitShiftLeftInt2x3)
    //{
    //  int2x3 actual;

    //  actual = actual << 5;

    //  //Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestBitShiftRightInt2x3)
    //{
    //  int2x3 actual;

    //  actual = actual >> 5;

    //  //Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestByScalarDivideUint4)
    //{
    //  uint3 expected = 2;
    //  uint3 actual = 4;

    //  actual = actual / 2;

    //  Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestByScalarDivideInt4)
    //{
    //  int4 expected = 32;
    //  int4 actual = 96;

    //  actual = actual / 3;

    //  Assert::AreEqual(expected, actual);
    //}

    //TEST_METHOD(TestEqualityOperatorUint3Uint3)
    //{
    //  uint3 expected = 2;
    //  uint3 actual = 2;

    //  Assert::IsTrue(expected == actual);
    //}

    //TEST_METHOD(TestGreaterOrEqualOperatorUint3Int)
    //{
    //  uint3 expected = 2;

    //  Assert::IsTrue(expected >= 1);
    //}

    //TEST_METHOD(TestEqualityOperatorUint3Int)
    //{
    //  uint3 expected = 2;

    //  Assert::IsTrue(expected == 2);
    //}

    //TEST_METHOD(TestEqualityOperatorInt2x3Int2x3)
    //{
    //  int2x3 expected;
    //  int2x3 actual;

    //  Assert::IsTrue(expected == actual);
    //}

    //TEST_METHOD(TestEqualityOperatorInt2x3Int)
    //{
    //  int2x3 expected;

    //  Assert::IsTrue(expected == 0);
    //}

    //TEST_METHOD(TestLeftBitShiftOperatorInt2x3Int)
    //{
    //  int2x3 actual = 1;
    //  int2x3 expected = 4;

    //  actual = actual << 2;

    //  Assert::AreEqual(expected, actual);
    //}
  };
}