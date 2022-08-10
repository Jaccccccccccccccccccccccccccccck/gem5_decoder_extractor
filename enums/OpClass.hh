/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   /home/workspace/gem5/build/ARM/SConscript:791
 */

#ifndef __ENUM__enums__OpClass__
#define __ENUM__enums__OpClass__

namespace gem5
{
namespace enums {
    enum OpClass
    {
        No_OpClass = 0,
        IntAlu = 1,
        IntMult = 2,
        IntDiv = 3,
        FloatAdd = 4,
        FloatCmp = 5,
        FloatCvt = 6,
        FloatMult = 7,
        FloatMultAcc = 8,
        FloatDiv = 9,
        FloatMisc = 10,
        FloatSqrt = 11,
        SimdAdd = 12,
        SimdAddAcc = 13,
        SimdAlu = 14,
        SimdCmp = 15,
        SimdCvt = 16,
        SimdMisc = 17,
        SimdMult = 18,
        SimdMultAcc = 19,
        SimdShift = 20,
        SimdShiftAcc = 21,
        SimdDiv = 22,
        SimdSqrt = 23,
        SimdFloatAdd = 24,
        SimdFloatAlu = 25,
        SimdFloatCmp = 26,
        SimdFloatCvt = 27,
        SimdFloatDiv = 28,
        SimdFloatMisc = 29,
        SimdFloatMult = 30,
        SimdFloatMultAcc = 31,
        SimdFloatSqrt = 32,
        SimdReduceAdd = 33,
        SimdReduceAlu = 34,
        SimdReduceCmp = 35,
        SimdFloatReduceAdd = 36,
        SimdFloatReduceCmp = 37,
        SimdAes = 38,
        SimdAesMix = 39,
        SimdSha1Hash = 40,
        SimdSha1Hash2 = 41,
        SimdSha256Hash = 42,
        SimdSha256Hash2 = 43,
        SimdShaSigma2 = 44,
        SimdShaSigma3 = 45,
        SimdPredAlu = 46,
        MemRead = 47,
        MemWrite = 48,
        FloatMemRead = 49,
        FloatMemWrite = 50,
        IprAccess = 51,
        InstPrefetch = 52,
        Num_OpClass = 53
    };
    extern const char *OpClassStrings[Num_OpClass];
}; // enums

} // namespace gem5

#endif // __ENUM__enums__OpClass__
