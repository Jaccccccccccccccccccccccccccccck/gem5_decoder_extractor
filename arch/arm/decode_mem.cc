#include "arch/arm/decoder.hh"

namespace gem5
{
namespace ArmISA
{

MemInfo*
ArmISA::Decoder::_decode_mem(ExtMachInst mach_inst)
{
    return new MemInfo(false, false);
}

}
}
