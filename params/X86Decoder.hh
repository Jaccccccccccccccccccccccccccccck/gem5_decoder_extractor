/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:50
 */

#ifndef __PARAMS__X86Decoder__
#define __PARAMS__X86Decoder__

namespace gem5 {
namespace X86ISA {
class Decoder;
} // namespace X86ISA
} // namespace gem5

#include "params/InstDecoder.hh"

namespace gem5
{
struct X86DecoderParams
    : public InstDecoderParams
{
    gem5::X86ISA::Decoder * create() const;
};

} // namespace gem5

#endif // __PARAMS__X86Decoder__
