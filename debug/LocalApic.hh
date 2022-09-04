/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:127
 */

#ifndef __DEBUG_LocalApic_HH__
#define __DEBUG_LocalApic_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union LocalApic
{
    ~LocalApic() {}
    SimpleFlag LocalApic = {
        "LocalApic", "Local APIC debugging", false
    };
} LocalApic;
} // namespace unions

inline constexpr const auto& LocalApic = 
    ::gem5::debug::unions::LocalApic.LocalApic;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_LocalApic_HH__
