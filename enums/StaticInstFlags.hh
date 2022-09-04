/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /home/workspace/gem5/build/X86/SConscript:791
 */

#ifndef __ENUM__StaticInstFlags__Flags__
#define __ENUM__StaticInstFlags__Flags__

namespace gem5
{
struct StaticInstFlags {
    enum Flags
    {
        IsNop = 0,
        IsInteger = 1,
        IsFloating = 2,
        IsVector = 3,
        IsVectorElem = 4,
        IsLoad = 5,
        IsStore = 6,
        IsAtomic = 7,
        IsStoreConditional = 8,
        IsInstPrefetch = 9,
        IsDataPrefetch = 10,
        IsControl = 11,
        IsDirectControl = 12,
        IsIndirectControl = 13,
        IsCondControl = 14,
        IsUncondControl = 15,
        IsCall = 16,
        IsReturn = 17,
        IsSerializing = 18,
        IsSerializeBefore = 19,
        IsSerializeAfter = 20,
        IsWriteBarrier = 21,
        IsReadBarrier = 22,
        IsNonSpeculative = 23,
        IsQuiesce = 24,
        IsUnverifiable = 25,
        IsSyscall = 26,
        IsMacroop = 27,
        IsMicroop = 28,
        IsDelayedCommit = 29,
        IsLastMicroop = 30,
        IsFirstMicroop = 31,
        IsSquashAfter = 32,
        IsHtmStart = 33,
        IsHtmStop = 34,
        IsHtmCancel = 35,
        Num_Flags = 36
    };
    static const char *FlagsStrings[Num_Flags];
}; // StaticInstFlags

} // namespace gem5

#endif // __ENUM__StaticInstFlags__Flags__
