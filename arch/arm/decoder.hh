/*
 * Copyright (c) 2013-2014 ARM Limited
 * All rights reserved
 *
 * The license below extends only to copyright in the software and shall
 * not be construed as granting a license to any other intellectual
 * property including but not limited to intellectual property relating
 * to a hardware implementation of the functionality of the software
 * licensed hereunder.  You may use the software subject to the license
 * terms below provided that you ensure that this notice is replicated
 * unmodified and in its entirety in all distributions of the software,
 * modified or unmodified, in source code or in binary form.
 *
 * Copyright (c) 2012 Google
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __ARCH_ARM_DECODER_HH__
#define __ARCH_ARM_DECODER_HH__

#include <cassert>

#include "arch/arm/regs/misc.hh"
#include "arch/arm/types.hh"
#include "arch/generic/decode_cache.hh"
#include "arch/generic/decoder.hh"
#include "base/types.hh"
#include "cpu/static_inst.hh"
#include "debug/Decode.hh"
#include "enums/DecoderFlavor.hh"
#include "params/ArmDecoder.hh"

namespace gem5
{

namespace ArmISA
{

class ISA;
class Decoder : public InstDecoder
{
  protected:
    //The extended machine instruction being generated
    ExtMachInst emi;
    uint32_t data;
    bool bigThumb;
    int offset;
    bool foundIt;
    ITSTATE itBits;

    int fpscrLen;
    int fpscrStride;

    /**
     * SVE vector length, encoded in the same format as the ZCR_EL<x>.LEN
     * bitfields.
     */
    int sveLen;

    enums::DecoderFlavor decoderFlavor;

    /// A cache of decoded instruction objects.
    static GenericISA::BasicDecodeCache<Decoder, ExtMachInst> defaultCache;
    friend class GenericISA::BasicDecodeCache<Decoder, ExtMachInst>;

    /**
     * Pre-decode an instruction from the current state of the
     * decoder.
     */
    void process();

    /**
     * Consume bytes by moving the offset into the data word and
     * sanity check the results.
     */
    void consumeBytes(int numBytes);

    /**
     * Decode a machine instruction without calling the cache.
     *
     * @note The implementation of this method is generated by the ISA
     * parser script.
     *
     * @warn This method takes a pre-decoded instruction as its
     * argument. It should typically not be called directly.
     *
     * @param mach_inst The binary instruction to decode.
     * @retval A pointer to the corresponding StaticInst object.
     */
    

    /**
     * Decode a pre-decoded machine instruction.
     *
     * @warn This method takes a pre-decoded instruction as its
     * argument. It should typically not be called directly.
     *
     * @param mach_inst A pre-decoded instruction
     * @retval A pointer to the corresponding StaticInst object.
     */
    StaticInstPtr
    decode(ExtMachInst mach_inst, Addr addr)
    {
        StaticInstPtr si = defaultCache.decode(this, mach_inst, addr);
        DPRINTF(Decode, "Decode: Decoded %s instruction: %#x\n",
                si->getName(), mach_inst);
        return si;
    }

  public: // Decoder API
    Decoder(const ArmDecoderParams &params);

    static StaticInstPtr decodeInst(ExtMachInst mach_inst);

    /** Reset the decoders internal state. */
    void reset() override;

    void moreBytes(const PCStateBase &pc, Addr fetchPC) override;

    StaticInstPtr decode(PCStateBase &pc) override;

  public: // ARM-specific decoder state manipulation
    void
    setContext(FPSCR fpscr)
    {
        fpscrLen = fpscr.len;
        fpscrStride = fpscr.stride;
    }

    void
    setSveLen(uint8_t len)
    {
        sveLen = len;
    }
};

} // namespace ArmISA
} // namespace gem5

#endif // __ARCH_ARM_DECODER_HH__