/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:50
 */

#ifndef __PARAMS__RiscvMMU__
#define __PARAMS__RiscvMMU__

namespace gem5 {
namespace RiscvISA {
class MMU;
} // namespace RiscvISA
} // namespace gem5
#include <cstddef>
#include "params/PMAChecker.hh"
#include <cstddef>
#include "params/PMP.hh"

#include "params/BaseMMU.hh"

namespace gem5
{
struct RiscvMMUParams
    : public BaseMMUParams
{
    gem5::RiscvISA::MMU * create() const;
    gem5::PMAChecker * pma_checker;
    gem5::PMP * pmp;
};

} // namespace gem5

#endif // __PARAMS__RiscvMMU__
