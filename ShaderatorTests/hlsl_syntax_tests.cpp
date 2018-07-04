#define _SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING 

#include "gtest/gtest.h"

#include "shaderator.h"
#include <vector>


TEST(HlslSyntaxTests, less_than_operator_compiless)
{
  int4 srcLeft{ 1, 1, 1, 1 }, srcRight{ 2, 2, 2, 2 }, mask{ 0, 0, 0, 0 };

  mask = srcLeft < srcRight;
}

// Below are some tests used for partial work on BC6HBC7EncoderCS project from directx samples

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