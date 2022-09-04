/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:50
 */

#ifndef __PARAMS__I82094AA__
#define __PARAMS__I82094AA__

namespace gem5 {
namespace X86ISA {
class I82094AA;
} // namespace X86ISA
} // namespace gem5
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "params/I8259.hh"
#include <cstddef>
#include "base/types.hh"

#include "params/BasicPioDevice.hh"

namespace gem5
{
struct I82094AAParams
    : public BasicPioDeviceParams
{
    gem5::X86ISA::I82094AA * create() const;
    int apic_id;
    gem5::X86ISA::I8259 * external_int_pic;
    Tick int_latency;
    unsigned int port_int_requestor_connection_count;
    unsigned int port_inputs_connection_count;
};

} // namespace gem5

#endif // __PARAMS__I82094AA__
