import re


class HlslToShaderator(object):
    pass

    def shaderate(self, shader):
        line = re.sub("StructuredBuffer\<(.*)\> (.*) : register\(t(.*)\)",
                      r'StructuredBuffer<\1> SHADERATOR_REGISTER_T(\2, \3)',
                      shader)

        line = re.sub("RWStructuredBuffer\<(.*)\> (.*) : register\(u(.*)\)",
                      r'RWStructuredBuffer<\1> SHADERATOR_REGISTER_U(\2, \3)',
                      line)

        return line


if __name__ == '__main__':
    pass
