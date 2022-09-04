/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:50
 */

#ifndef __PARAMS__BaseTLB__
#define __PARAMS__BaseTLB__

namespace gem5 {
class BaseTLB;
} // namespace gem5
#include <cstddef>
#include "enums/TypeTLB.hh"
#include <cstddef>
#include "params/BaseTLB.hh"

#include "params/SimObject.hh"

#include "enums/TypeTLB.hh"

namespace gem5
{
struct BaseTLBParams
    : public SimObjectParams
{
    TypeTLB entry_type;
    gem5::BaseTLB * next_level;
    unsigned int port_cpu_side_ports_connection_count;
    unsigned int port_mem_side_port_connection_count;
};

} // namespace gem5

#endif // __PARAMS__BaseTLB__
