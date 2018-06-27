import unittest
from converters.hlsl import HlslToShaderator


class TestShaderate(unittest.TestCase):
    def setUp(self):
        self.converter = HlslToShaderator()

    def test_converts_structured_buffer(self):
        shader = "StructuredBuffer<float> Input : register(t0);"

        shaderated = self.converter.shaderate(shader)

        expected = "StructuredBuffer<float> SHADERATOR_REGISTER_T(Input, 0);"
        self.assertEqual(expected, shaderated)

    def test_converts_rwstructured_buffer(self):
        shader = "RWStructuredBuffer<unsigned int> Data : register(u0);"

        shaderated = self.converter.shaderate(shader)

        expected = "RWStructuredBuffer<unsigned int> SHADERATOR_REGISTER_U(Data, 0);"
        self.assertEqual(expected, shaderated)

    def test_adds_shaderator_header(self):
        shader = "float a;"

        shaderated = self.converter.shaderate(shader)

        expected = "#include \"shaderator.h\"\nfloat a;"
        self.assertEqual(expected, shaderated)


if __name__ == '__main__':
    unittest.main()
