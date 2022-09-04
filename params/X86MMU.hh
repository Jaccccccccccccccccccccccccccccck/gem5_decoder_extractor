/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:50
 */

#ifndef __PARAMS__X86MMU__
#define __PARAMS__X86MMU__

namespace gem5 {
namespace X86ISA {
class MMU;
} // namespace X86ISA
} // namespace gem5

#include "params/BaseMMU.hh"

namespace gem5
{
struct X86MMUParams
    : public BaseMMUParams
{
    gem5::X86ISA::MMU * create() const;
};

} // namespace gem5

#endif // __PARAMS__X86MMU__
