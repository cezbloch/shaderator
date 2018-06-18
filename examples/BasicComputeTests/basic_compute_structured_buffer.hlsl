#include "shaderator.h"
#include "shared_types.h"

StructuredBuffer<BufType> SHADERATOR_REGISTER_T(Buffer0, 0);
StructuredBuffer<BufType> SHADERATOR_REGISTER_T(Buffer1, 1);
RWStructuredBuffer<BufType> SHADERATOR_REGISTER_U(BufferOut, 0);

SHADERATOR_NUM_THREADS(1, 1, 1)
void CSMain(SHADERATOR_SV_DispatchThreadID(DTid), 
            SHADERATOR_SV_GroupID(Gid),
            SHADERATOR_SV_GroupThreadID(GTid),
            SHADERATOR_SV_GroupIndex(GI))
{
    BufferOut[DTid.x].i = Buffer0[DTid.x].i + Buffer1[DTid.x].i;
    BufferOut[DTid.x].f = Buffer0[DTid.x].f + Buffer1[DTid.x].f;
}

