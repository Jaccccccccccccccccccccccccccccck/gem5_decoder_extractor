/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:50
 */

#ifndef __PARAMS__KvmVM__
#define __PARAMS__KvmVM__

namespace gem5 {
class KvmVM;
} // namespace gem5
#include <vector>
#include "base/types.hh"
#include "base/addr_range.hh"

#include "params/SimObject.hh"

namespace gem5
{
struct KvmVMParams
    : public SimObjectParams
{
    gem5::KvmVM * create() const;
    std::vector< AddrRange > coalescedMMIO;
};

} // namespace gem5

#endif // __PARAMS__KvmVM__
