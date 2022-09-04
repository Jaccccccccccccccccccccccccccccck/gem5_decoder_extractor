/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:50
 */

#ifndef __PARAMS__X86TLB__
#define __PARAMS__X86TLB__

namespace gem5 {
namespace X86ISA {
class TLB;
} // namespace X86ISA
} // namespace gem5
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "params/System.hh"
#include <cstddef>
#include "params/X86PagetableWalker.hh"

#include "params/BaseTLB.hh"

namespace gem5
{
struct X86TLBParams
    : public BaseTLBParams
{
    gem5::X86ISA::TLB * create() const;
    unsigned size;
    gem5::System * system;
    gem5::X86ISA::Walker * walker;
};

} // namespace gem5

#endif // __PARAMS__X86TLB__
