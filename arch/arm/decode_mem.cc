#include "arch/arm/decoder.hh"

namespace gem5 {
namespace ArmISA {

MemInfo*
ArmISA::Decoder::_decode_mem(ExtMachInst machInst) {
    // Aarch64::aarch64(([], {}))
    if (bits(machInst, 27) == 0x0) {
        if (bits(machInst, 28) == 0x0) {
            if (bits(machInst, 31) != 0x0) {
                uint8_t b_30_29 = bits(machInst, 30, 29);
                switch (b_30_29) {
                    case 0x0: {
                        // load
                        return new MemInfo(1, 1, 0);
                    };
                    case 0x1:
                        // load
                        return new MemInfo(1, 1, 0);
                    case 0x2:
                        // load
                        return new MemInfo(1, 1, 0);
                    case 0x3:
                        // store
                        return new MemInfo(1, 0, 1);
                }
            }
        }
        return new MemInfo(0, 0, 0);
    } else if (bits(machInst, 25) == 0) {
        // bit 27,25=10
        switch (bits(machInst, 29, 28)) {
            case 0x0:
                if (bits(machInst, 26) == 0) {
                    uint8_t opc = (bits(machInst, 15) << 0) |
                                  (bits(machInst, 23, 21) << 1);
                    uint8_t size = bits(machInst, 31, 30);
                    switch (opc) {
                        case 0x0:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x1:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x2:
                            switch (size) {
                                case 0x0:
                                    // return new CASP32(machInst, rt, rnsp, rs);

                                    // https://developer.arm.com/documentation/ddi0602/2021-12/Base-Instructions/CASP--CASPA--CASPAL--CASPL--Compare-and-Swap-Pair-of-words-or-doublewords-in-memory-
                                    // 从内存中读取一对 32 位字或 64 位双字，并将它们与保存在第一对寄存器中的值进行比较。如果比较相等，则将第二对寄存器中的值写入内存。
                                    // both load and store
                                    return new MemInfo(1, 1, 1);
                                case 0x1:
                                    // return new CASP64(machInst, rt, rnsp, rs);
                                    // both load and store
                                    return new MemInfo(1, 1, 1);
                                case 0x2:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x3:
                                    // store
                                    return new MemInfo(1, 0, 1);
                            }

                        case 0x3:
                            switch (size) {
                                case 0x0:
                                    // return new CASPL32(machInst, rt, rnsp, rs);
                                    // both load and store
                                    return new MemInfo(1, 1, 1);
                                case 0x1:
                                    // return new CASPL64(machInst, rt, rnsp, rs);
                                    // both load and store
                                    return new MemInfo(1, 1, 1);
                                case 0x2:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x3:
                                    // store
                                    return new MemInfo(1, 0, 1);
                            }
                        case 0x4:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x5:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x6:
                            switch (size) {
                                case 0x0:
                                    // return new CASPA32(machInst, rt, rnsp, rs);
                                    // both load and store
                                    return new MemInfo(1, 1, 1);
                                case 0x1:
                                    // return new CASPA64(machInst, rt, rnsp, rs);
                                    // both load and store
                                    return new MemInfo(1, 1, 1);
                                case 0x2:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x3:
                                    // load
                                    return new MemInfo(1, 1, 0);
                            }
                        case 0x7:
                            switch (size) {
                                case 0x0:
                                    // return new CASPAL32(machInst, rt, rnsp, rs);
                                    // both load and store
                                    return new MemInfo(1, 1, 1);
                                case 0x1:
                                    // return new CASPAL64(machInst, rt, rnsp, rs);
                                    // both load and store
                                    return new MemInfo(1, 1, 1);
                                case 0x2:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x3:
                                    // load
                                    return new MemInfo(1, 1, 0);
                            }
                        case 0x9:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0xa:
                            // both load and store
                            return new MemInfo(1, 1, 1);
                        case 0xb:
                            // both load and store
                            return new MemInfo(1, 1, 1);
                        case 0xd:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0xe:
                            // both load and store
                            return new MemInfo(1, 1, 1);
                        case 0xf:
                            // both load and store
                            return new MemInfo(1, 1, 1);
                    }
                } else if (bits(machInst, 31)) {
                    // return new Unknown64(machInst);
                    // go error
                    return new MemInfo(0, 0, 0);
                } else {
                    bool load = bits(machInst, 22);
                    if (load) {
                        // load
                        return new MemInfo(1, 1, 0);
                    } else {
                        // store
                        return new MemInfo(1, 0, 1);
                    }
                }
            case 0x1: {
                // load
                return new MemInfo(1, 1, 0);
            }
            case 0x2: {
                bool load = bits(machInst, 22);
                if (load) {
                    // load
                    return new MemInfo(1, 1, 0);
                } else {
                    // store
                    return new MemInfo(1, 0, 1);
                }
            }
            // bit 29:27=111, 25=0
            case 0x3: {
                uint8_t switchVal = (bits(machInst, 23, 22) << 0) |
                                    (bits(machInst, 26) << 2) |
                                    (bits(machInst, 31, 30) << 3);
                if (bits(machInst, 24) == 1) {
                    uint64_t imm12 = bits(machInst, 21, 10);
                    IntRegIndex rt = (IntRegIndex)(uint32_t)bits(machInst, 4, 0);
                    IntRegIndex rn = (IntRegIndex)(uint32_t)bits(machInst, 9, 5);
                    IntRegIndex rnsp = makeSP(rn);
                    switch (switchVal) {
                        case 0x00:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x01:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x02:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x03:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x04:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x05:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x06:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x07:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x08:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x09:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x0a:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x0b:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x0c:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x0d:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x10:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x11:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x12:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x14:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x15:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x18:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x19:
                            // load
                            return new MemInfo(1, 1, 0);
                        case 0x1a:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x1c:
                            // store
                            return new MemInfo(1, 0, 1);
                        case 0x1d:
                            // load
                            return new MemInfo(1, 1, 0);
                    }
                } else if (bits(machInst, 21) == 1) {
                    uint8_t group = bits(machInst, 11, 10);
                    switch (group) {
                        case 0x0: {
                            if ((switchVal & 0x7) == 0x2 &&
                                bits(machInst, 20, 12) == 0x1fc) {
                                // load
                                return new MemInfo(1, 1, 0);
                            } else {
                                uint8_t opc = bits(machInst, 14, 12);
                                uint8_t o3 = bits(machInst, 15);
                                uint8_t size_ar = bits(machInst, 23, 22) << 0 | bits(machInst, 31, 30) << 2;
                                IntRegIndex rt = (IntRegIndex)(uint8_t)bits(machInst, 4, 0);
                                IntRegIndex rn = (IntRegIndex)(uint8_t)bits(machInst, 9, 5);
                                IntRegIndex rnsp = makeSP(rn);
                                IntRegIndex rs = (IntRegIndex)(uint8_t)bits(machInst, 20, 16);
                                uint8_t A_rt = bits(machInst, 4, 0) << 0 | bits(machInst, 23) << 5;

                                switch (opc) {
                                    case 0x0:
                                        switch (size_ar) {
                                            case 0x0:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x1:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x2:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x3:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x4:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x5:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x6:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x7:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x8:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x9:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xa:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xb:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xc:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);

                                                else if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xd:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xe:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xf:
                                                if (o3 == 1)
                                                    // both load and store
                                                    return new MemInfo(1, 1, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                        }
                                    case 0x1:
                                        switch (size_ar) {
                                            case 0x0:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x1:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x2:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x3:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x4:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x5:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x6:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x7:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x8:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x9:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xa:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xb:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xc:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xd:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xe:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xf:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                        }
                                    case 0x2:
                                        switch (size_ar) {
                                            case 0x0:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x1:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x2:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x3:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x4:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x5:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x6:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x7:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x8:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x9:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xa:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xb:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xc:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xd:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xe:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xf:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                        }
                                    case 0x3:
                                        switch (size_ar) {
                                            case 0x0:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x1:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x2:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x3:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x4:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x5:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x6:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x7:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x8:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x9:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xa:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xb:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xc:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xd:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xe:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xf:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                        }
                                    case 0x4:
                                        switch (size_ar) {
                                            case 0x0:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x1:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x2:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x3:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x4:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x5:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x6:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x7:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x8:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x9:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xa:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xb:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xc:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xd:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xe:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xf:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                        }
                                    case 0x5:
                                        switch (size_ar) {
                                            case 0x0:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x1:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x2:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x3:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x4:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x5:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x6:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x7:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x8:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x9:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xa:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xb:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xc:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xd:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xe:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xf:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                        }
                                    case 0x6:
                                        switch (size_ar) {
                                            case 0x0:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x1:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x2:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x3:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x4:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x5:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x6:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x7:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x8:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x9:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xa:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xb:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xc:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xd:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xe:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xf:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                        }
                                    case 0x7:
                                        switch (size_ar) {
                                            case 0x0:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x1:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x2:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x3:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x4:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x5:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x6:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x7:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0x8:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0x9:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xa:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xb:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xc:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xd:
                                                if (A_rt == 0x1f)
                                                    // store
                                                    return new MemInfo(1, 0, 1);
                                                else
                                                    // load
                                                    return new MemInfo(1, 1, 0);
                                            case 0xe:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                            case 0xf:
                                                // load
                                                return new MemInfo(1, 1, 0);
                                        }
                                    default:
                                        // return new Unknown64(machInst);
                                        // go error
                                        return new MemInfo(0, 0, 0);
                                }
                            }
                        }
                        case 0x1:
                        case 0x3: {
                            IntRegIndex rt = (IntRegIndex)(uint32_t)
                                bits(machInst, 4, 0);
                            IntRegIndex rn = (IntRegIndex)(uint32_t)
                                bits(machInst, 9, 5);
                            uint8_t s = bits(machInst, 22);
                            uint64_t imm9 = bits(machInst, 20, 12);
                            uint64_t imm10 = sext<10>(s << 9 | imm9) << 3;
                            uint8_t val = bits(machInst, 23) << 1 | bits(machInst, 11);
                            // load
                            return new MemInfo(1, 1, 0);
                        }
                        case 0x2: {
                            IntRegIndex rt = (IntRegIndex)(uint32_t)
                                bits(machInst, 4, 0);
                            IntRegIndex rn = (IntRegIndex)(uint32_t)
                                bits(machInst, 9, 5);
                            IntRegIndex rnsp = makeSP(rn);
                            IntRegIndex rm = (IntRegIndex)(uint32_t)
                                bits(machInst, 20, 16);
                            ArmExtendType type =
                                (ArmExtendType)(uint32_t)bits(machInst, 15, 13);
                            uint8_t s = bits(machInst, 12);
                            switch (switchVal) {
                                case 0x00:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x01:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x02:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x03:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x04:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x05:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x6:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x7:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x08:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x09:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0a:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0b:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0c:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x0d:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x10:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x11:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x12:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x14:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x15:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x18:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x19:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x1a:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x1c:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x1d:
                                    // load
                                    return new MemInfo(1, 1, 0);
                            }
                        }
                    }
                } else {
                    // bit 29:27=111, 25:24=00, 21=0
                    switch (bits(machInst, 11, 10)) {
                        case 0x0: {
                            IntRegIndex rt =
                                (IntRegIndex)(uint32_t)bits(machInst, 4, 0);
                            IntRegIndex rn =
                                (IntRegIndex)(uint32_t)bits(machInst, 9, 5);
                            IntRegIndex rnsp = makeSP(rn);
                            uint64_t imm = sext<9>(bits(machInst, 20, 12));
                            switch (switchVal) {
                                case 0x00:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x01:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x02:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x03:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x04:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x05:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x06:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x07:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x08:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x09:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0a:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0b:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0c:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x0d:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x10:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x11:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x12:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x14:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x15:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x18:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x19:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x1a:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x1c:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x1d:
                                    // load
                                    return new MemInfo(1, 1, 0);
                            }
                        }
                        // bit 29:27=111, 25:24=00, 21=0, 11:10=01
                        case 0x1: {
                            IntRegIndex rt =
                                (IntRegIndex)(uint32_t)bits(machInst, 4, 0);
                            IntRegIndex rn =
                                (IntRegIndex)(uint32_t)bits(machInst, 9, 5);
                            IntRegIndex rnsp = makeSP(rn);
                            uint64_t imm = sext<9>(bits(machInst, 20, 12));
                            switch (switchVal) {
                                case 0x00:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x01:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x02:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x03:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x04:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x05:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x06:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x07:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x08:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x09:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0a:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0b:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0c:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x0d:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x10:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x11:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x12:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x14:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x15:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x18:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x19:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x1c:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x1d:
                                    // load
                                    return new MemInfo(1, 1, 0);
                            }
                        }
                        case 0x2: {
                            IntRegIndex rt =
                                (IntRegIndex)(uint32_t)bits(machInst, 4, 0);
                            IntRegIndex rn =
                                (IntRegIndex)(uint32_t)bits(machInst, 9, 5);
                            IntRegIndex rnsp = makeSP(rn);
                            uint64_t imm = sext<9>(bits(machInst, 20, 12));
                            switch (switchVal) {
                                case 0x00:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x01:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x02:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x03:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x08:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x09:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0a:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0b:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x10:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x11:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x12:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x18:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x19:
                                    // load
                                    return new MemInfo(1, 1, 0);
                            }
                        }
                        case 0x3: {
                            IntRegIndex rt =
                                (IntRegIndex)(uint32_t)bits(machInst, 4, 0);
                            IntRegIndex rn =
                                (IntRegIndex)(uint32_t)bits(machInst, 9, 5);
                            IntRegIndex rnsp = makeSP(rn);
                            uint64_t imm = sext<9>(bits(machInst, 20, 12));
                            switch (switchVal) {
                                case 0x00:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x01:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x02:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x03:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x04:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x05:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x06:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x07:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x08:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x09:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0a:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0b:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x0c:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x0d:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x10:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x11:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x12:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x14:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x15:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x18:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x19:
                                    // load
                                    return new MemInfo(1, 1, 0);
                                case 0x1c:
                                    // store
                                    return new MemInfo(1, 0, 1);
                                case 0x1d:
                                    // load
                                    return new MemInfo(1, 1, 0);
                            }
                        }
                    }
                }
            }
        }

    } else {
        return new MemInfo(0, 0, 0);
    }
}

}  // namespace ArmISA
}  // namespace gem5
