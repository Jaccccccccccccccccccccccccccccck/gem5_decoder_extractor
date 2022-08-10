/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:50
 */

#ifndef __PARAMS__BaseCPU__
#define __PARAMS__BaseCPU__

namespace gem5 {
class BaseCPU;
} // namespace gem5
#include <cstddef>
#include "params/BaseCPU.hh"
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "params/InstDecoder.hh"
#include <cstddef>
#include <cstddef>
#include <cstddef>
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "params/BaseInterrupts.hh"
#include <vector>
#include "params/BaseISA.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "params/BaseMMU.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "params/System.hh"
#include <cstddef>
#include "params/InstTracer.hh"
#include <vector>
#include "params/Process.hh"

#include "params/ClockedObject.hh"

namespace gem5
{
struct BaseCPUParams
    : public ClockedObjectParams
{
    gem5::BaseCPU * checker;
    int cpu_id;
    std::vector< gem5::InstDecoder * > decoder;
    bool do_checkpoint_insts;
    bool do_statistics_insts;
    bool function_trace;
    Tick function_trace_start;
    std::vector< gem5::BaseInterrupts * > interrupts;
    std::vector< gem5::BaseISA * > isa;
    Counter max_insts_all_threads;
    Counter max_insts_any_thread;
    gem5::BaseMMU * mmu;
    unsigned numThreads;
    bool power_gating_on_idle;
    Tick progress_interval;
    Cycles pwr_gating_latency;
    std::vector< Counter > simpoint_start_insts;
    unsigned socket_id;
    bool switched_out;
    Cycles syscallRetryLatency;
    gem5::System * system;
    gem5::Trace::InstTracer * tracer;
    std::vector< gem5::Process * > workload;
    unsigned int port_icache_port_connection_count;
    unsigned int port_dcache_port_connection_count;
};

} // namespace gem5

#endif // __PARAMS__BaseCPU__
