/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:127
 */

#ifndef __DEBUG_LLSC_HH__
#define __DEBUG_LLSC_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union LLSC
{
    ~LLSC() {}
    SimpleFlag LLSC = {
        "LLSC", "", false
    };
} LLSC;
} // namespace unions

inline constexpr const auto& LLSC = 
    ::gem5::debug::unions::LLSC.LLSC;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_LLSC_HH__
