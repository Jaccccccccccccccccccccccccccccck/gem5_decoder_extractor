/*
 * Copyright (c) 2011 Google
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

#include "arch/x86/decoder.hh"

#include "arch/x86/regs/misc.hh"
#include "base/logging.hh"
#include "base/trace.hh"
#include "base/types.hh"
#include "debug/Decode.hh"
#include "debug/Decoder.hh"

namespace gem5
{

namespace X86ISA
{

X86ISAInst::MicrocodeRom Decoder::microcodeRom;

Decoder::State
Decoder::doResetState()
{
    origPC = basePC + offset;
    printf("Setting origPC to %#x\n", origPC);
    instBytes = &decodePages->lookup(origPC);
    chunkIdx = 0;

    emi.rex = 0;
    emi.legacy = 0;
    emi.vex = 0;

    emi.opcode.type = BadOpcode;
    emi.opcode.op = 0;

    immediateCollected = 0;
    emi.immediate = 0;
    emi.displacement = 0;
    emi.dispSize = 0;

    emi.modRM = 0;
    emi.sib = 0;

    if (instBytes->si) {
        return FromCacheState;
    } else {
        instBytes->chunks.clear();
        return PrefixState;
    }
}

Decoder::State
Decoder::doResetStateStatic(ExtMachInst &emi)
{
    emi.rex = 0;
    emi.legacy = 0;
    emi.vex = 0;

    emi.opcode.type = BadOpcode;
    emi.opcode.op = 0;

    emi.immediate = 0;
    emi.displacement = 0;
    emi.dispSize = 0;

    emi.modRM = 0;
    emi.sib = 0;
    return PrefixState;
}

ExtMachInst
Decoder::getExtInst(unsigned char bytes[], int byte_size)
{
  // The size of the displacement value.
  int displacementSize;
  // The size of the immediate value.
  int immediateSize;
  // This is how much of any immediate value we've gotten. This is used
  // for both the actual immediate and the displacement.
  int immediateCollected = 0;
  uint8_t altOp = 1;
  uint8_t defOp = 2;
  uint8_t altAddr = 2;
  uint8_t defAddr = 3;
  uint8_t stack = 3;
  ExtMachInst emi;
  emi.mode = (X86Mode)(uint64_t)LongMode;
  emi.mode.submode = (X86SubMode)(uint64_t)SixtyFourBitMode;
  State state = ResetState;
  state = doResetStateStatic(emi);
  bool instDone = false;
  u_int64_t index = 0;
  // While there's still something to do...
  while (!instDone) {
      uint8_t nextByte = bytes[index];
      switch (state) {
        case PrefixState:
          // state = doPrefixState(nextByte);
          state = doPrefixStateStatic(nextByte, emi, index);
          break;
        case Vex2Of2State:
          // state = doVex2Of2State(nextByte);
          state = doVex2Of2StateStatic(nextByte, emi, index);
          break;
        case Vex2Of3State:
          // state = doVex2Of3State(nextByte);
          state = doVex2Of3StateStatic(nextByte, emi, index, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
          break;
        case Vex3Of3State:
          // state = doVex3Of3State(nextByte);
          state = doVex3Of3StateStatic(nextByte, emi, index, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
          break;
        case VexOpcodeState:
          // state = doVexOpcodeState(nextByte);
          state = doVexOpcodeStateStatic(nextByte, emi, index, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
          break;
        case OneByteOpcodeState:
          // state = doOneByteOpcodeState(nextByte);
          state = doOneByteOpcodeStateStatic(nextByte, emi, index, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
          break;
        case TwoByteOpcodeState:
          // state = doTwoByteOpcodeState(nextByte, emi, index);
          state = doTwoByteOpcodeStateStatic(nextByte, emi, index, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
          break;
        case ThreeByte0F38OpcodeState:
          // state = doThreeByte0F38OpcodeState(nextByte);
          state = doThreeByte0F38OpcodeStateStatic(nextByte, emi, index, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
          break;
        case ThreeByte0F3AOpcodeState:
          // state = doThreeByte0F3AOpcodeState(nextByte);
          state = doThreeByte0F3AOpcodeStateStatic(nextByte, emi, index, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
          break;
        case ModRMState:
          // state = doModRMState(nextByte);
          state = doModRMStateStatic(nextByte, emi, index, displacementSize, immediateSize, defOp, instDone);
          break;
        case SIBState:
          // state = doSIBState(nextByte);
          state = doSIBStateStatic(nextByte, emi, index, displacementSize, immediateSize, instDone);
          break;
        case DisplacementState:
          // state = doDisplacementState();
          state = doDisplacementStateStatic(bytes, byte_size, emi, index, displacementSize, immediateSize, immediateCollected, instDone);
          break;
        case ImmediateState:
          state = doImmediateStateStatic(bytes, byte_size, emi, index, immediateSize, immediateCollected, instDone);
          break;
        case ErrorState:
          panic("Went to the error state in the decoder.\n");
        default:
          panic("Unrecognized state! %d\n", state);
      }
  }
  return emi;
}

void
Decoder::process()
{
    // This function drives the decoder state machine.

    // Some sanity checks. You shouldn't try to process more bytes if
    // there aren't any, and you shouldn't overwrite an already decoded
    // ExtMachInst.
    assert(!outOfBytes);
    assert(!instDone);

    if (state == ResetState)
        state = doResetState();
    if (state == FromCacheState) {
        state = doFromCacheState();
    } else {
        instBytes->chunks.push_back(fetchChunk);
    }

    // While there's still something to do...
    while (!instDone && !outOfBytes) {
        uint8_t nextByte = getNextByte();
        switch (state) {
          case PrefixState:
            state = doPrefixState(nextByte);
            break;
          case Vex2Of2State:
            state = doVex2Of2State(nextByte);
            break;
          case Vex2Of3State:
            state = doVex2Of3State(nextByte);
            break;
          case Vex3Of3State:
            state = doVex3Of3State(nextByte);
            break;
          case VexOpcodeState:
            state = doVexOpcodeState(nextByte);
            break;
          case OneByteOpcodeState:
            state = doOneByteOpcodeState(nextByte);
            break;
          case TwoByteOpcodeState:
            state = doTwoByteOpcodeState(nextByte);
            break;
          case ThreeByte0F38OpcodeState:
            state = doThreeByte0F38OpcodeState(nextByte);
            break;
          case ThreeByte0F3AOpcodeState:
            state = doThreeByte0F3AOpcodeState(nextByte);
            break;
          case ModRMState:
            state = doModRMState(nextByte);
            break;
          case SIBState:
            state = doSIBState(nextByte);
            break;
          case DisplacementState:
            state = doDisplacementState();
            break;
          case ImmediateState:
            state = doImmediateState();
            break;
          case ErrorState:
            panic("Went to the error state in the decoder.\n");
          default:
            panic("Unrecognized state! %d\n", state);
        }
    }
}



Decoder::State
Decoder::doFromCacheState()
{
    printf("Looking at cache state.\n");
    if ((fetchChunk & instBytes->masks[chunkIdx]) !=
            instBytes->chunks[chunkIdx]) {
        printf("Decode cache miss.\n");
        // The chached chunks didn't match what was fetched. Fall back to the
        // predecoder.
        instBytes->chunks[chunkIdx] = fetchChunk;
        instBytes->chunks.resize(chunkIdx + 1);
        instBytes->si = NULL;
        chunkIdx = 0;
        fetchChunk = instBytes->chunks[0];
        offset = origPC % sizeof(MachInst);
        basePC = origPC - offset;
        return PrefixState;
    } else if (chunkIdx == instBytes->chunks.size() - 1) {
        // We matched the cache, so use its value.
        instDone = true;
        offset = instBytes->lastOffset;
        if (offset == sizeof(MachInst))
            outOfBytes = true;
        return ResetState;
    } else {
        // We matched so far, but need to check more chunks.
        chunkIdx++;
        outOfBytes = true;
        return FromCacheState;
    }
}

// Either get a prefix and record it in the ExtMachInst, or send the
// state machine on to get the opcode(s).
Decoder::State
Decoder::doPrefixState(uint8_t nextByte)
{
    uint8_t prefix = Prefixes[nextByte];
    State nextState = PrefixState;
    // REX prefixes are only recognized in 64 bit mode.
    if (prefix == RexPrefix && emi.mode.submode != SixtyFourBitMode)
        prefix = 0;
    if (prefix)
        consumeByte();
    switch(prefix) {
        // Operand size override prefixes
      case OperandSizeOverride:
        printf("Found operand size override prefix.\n");
        emi.legacy.op = true;
        break;
      case AddressSizeOverride:
        printf("Found address size override prefix.\n");
        emi.legacy.addr = true;
        break;
        // Segment override prefixes
      case CSOverride:
      case DSOverride:
      case ESOverride:
      case FSOverride:
      case GSOverride:
      case SSOverride:
        printf("Found segment override.\n");
        emi.legacy.seg = prefix;
        break;
      case Lock:
        printf("Found lock prefix.\n");
        emi.legacy.lock = true;
        break;
      case Rep:
        printf("Found rep prefix.\n");
        emi.legacy.rep = true;
        break;
      case Repne:
        printf("Found repne prefix.\n");
        emi.legacy.repne = true;
        break;
      case RexPrefix:
        printf("Found Rex prefix %#x.\n", nextByte);
        emi.rex = nextByte;
        break;
      case Vex2Prefix:
        printf("Found VEX two-byte prefix %#x.\n", nextByte);
        emi.vex.present = 1;
        nextState = Vex2Of2State;
        break;
      case Vex3Prefix:
        printf("Found VEX three-byte prefix %#x.\n", nextByte);
        emi.vex.present = 1;
        nextState = Vex2Of3State;
        break;
      case 0:
        nextState = OneByteOpcodeState;
        break;

      default:
        panic("Unrecognized prefix %#x\n", nextByte);
    }
    return nextState;
}

Decoder::State
Decoder::doPrefixStateStatic(uint8_t nextByte, ExtMachInst &emi, u_int64_t &index)
{
    uint8_t prefix = Prefixes[nextByte];
    State nextState = PrefixState;
    // REX prefixes are only recognized in 64 bit mode.
    if (prefix == RexPrefix && emi.mode.submode != SixtyFourBitMode)
        prefix = 0;
    if (prefix)
        index++;
    switch(prefix) {
        // Operand size override prefixes
      case OperandSizeOverride:
        // printf("Found operand size override prefix.\n");
        printf("Found operand size override prefix.\n");
        emi.legacy.op = true;
        break;
      case AddressSizeOverride:
        printf("Found address size override prefix.\n");
        emi.legacy.addr = true;
        break;
        // Segment override prefixes
      case CSOverride:
      case DSOverride:
      case ESOverride:
      case FSOverride:
      case GSOverride:
      case SSOverride:
        printf("Found segment override.\n");
        emi.legacy.seg = prefix;
        break;
      case Lock:
        printf("Found lock prefix.\n");
        emi.legacy.lock = true;
        break;
      case Rep:
        printf("Found rep prefix.\n");
        emi.legacy.rep = true;
        break;
      case Repne:
        printf("Found repne prefix.\n");
        emi.legacy.repne = true;
        break;
      case RexPrefix:
        printf("Found Rex prefix %#x.\n", nextByte);
        emi.rex = nextByte;
        break;
      case Vex2Prefix:
        printf("Found VEX two-byte prefix %#x.\n", nextByte);
        emi.vex.present = 1;
        nextState = Vex2Of2State;
        break;
      case Vex3Prefix:
        printf("Found VEX three-byte prefix %#x.\n", nextByte);
        emi.vex.present = 1;
        nextState = Vex2Of3State;
        break;
      case 0:
        nextState = OneByteOpcodeState;
        break;

      default:
        panic("Unrecognized prefix %#x\n", nextByte);
    }
    return nextState;
}

Decoder::State
Decoder::doVex2Of2State(uint8_t nextByte)
{
    consumeByte();
    Vex2Of2 vex = nextByte;

    emi.rex.r = !vex.r;

    emi.vex.l = vex.l;
    emi.vex.v = ~vex.v;

    switch (vex.p) {
      case 0:
        break;
      case 1:
        emi.legacy.op = 1;
        break;
      case 2:
        emi.legacy.rep = 1;
        break;
      case 3:
        emi.legacy.repne = 1;
        break;
    }

    emi.opcode.type = TwoByteOpcode;

    return VexOpcodeState;
}

Decoder::State
Decoder::doVex2Of2StateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index)
{
    index++;
    Vex2Of2 vex = nextByte;

    emi.rex.r = !vex.r;

    emi.vex.l = vex.l;
    emi.vex.v = ~vex.v;

    switch (vex.p) {
      case 0:
        break;
      case 1:
        emi.legacy.op = 1;
        break;
      case 2:
        emi.legacy.rep = 1;
        break;
      case 3:
        emi.legacy.repne = 1;
        break;
    }

    emi.opcode.type = TwoByteOpcode;

    return VexOpcodeState;
}

Decoder::State
Decoder::doVex2Of3State(uint8_t nextByte)
{
    if (emi.mode.submode != SixtyFourBitMode && bits(nextByte, 7, 6) == 0x3) {
        // This was actually an LDS instruction. Reroute to that path.
        emi.vex.present = 0;
        emi.opcode.type = OneByteOpcode;
        emi.opcode.op = 0xC4;
        return processOpcode(ImmediateTypeOneByte, UsesModRMOneByte,
                             nextByte >= 0xA0 && nextByte <= 0xA3);
    }

    consumeByte();
    Vex2Of3 vex = nextByte;

    emi.rex.r = !vex.r;
    emi.rex.x = !vex.x;
    emi.rex.b = !vex.b;

    switch (vex.m) {
      case 1:
        emi.opcode.type = TwoByteOpcode;
        break;
      case 2:
        emi.opcode.type = ThreeByte0F38Opcode;
        break;
      case 3:
        emi.opcode.type = ThreeByte0F3AOpcode;
        break;
      default:
        // These encodings are reserved. Pretend this was an undefined
        // instruction so the main decoder will behave correctly, and stop
        // trying to interpret bytes.
        emi.opcode.type = TwoByteOpcode;
        emi.opcode.op = 0x0B;
        instDone = true;
        return ResetState;
    }
    return Vex3Of3State;
}

Decoder::State
Decoder::doVex2Of3StateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, uint8_t &altOp, uint8_t &defOp, uint8_t &altAddr, uint8_t &defAddr, uint8_t &stack, int &immediateSize, bool &instDone)
{
    if (emi.mode.submode != SixtyFourBitMode && bits(nextByte, 7, 6) == 0x3) {
        // This was actually an LDS instruction. Reroute to that path.
        emi.vex.present = 0;
        emi.opcode.type = OneByteOpcode;
        emi.opcode.op = 0xC4;
        return processOpcodeStatic(ImmediateTypeOneByte, UsesModRMOneByte,
                            emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone, nextByte >= 0xA0 && nextByte <= 0xA3);
    }

    index++;
    Vex2Of3 vex = nextByte;

    emi.rex.r = !vex.r;
    emi.rex.x = !vex.x;
    emi.rex.b = !vex.b;

    switch (vex.m) {
      case 1:
        emi.opcode.type = TwoByteOpcode;
        break;
      case 2:
        emi.opcode.type = ThreeByte0F38Opcode;
        break;
      case 3:
        emi.opcode.type = ThreeByte0F3AOpcode;
        break;
      default:
        // These encodings are reserved. Pretend this was an undefined
        // instruction so the main decoder will behave correctly, and stop
        // trying to interpret bytes.
        emi.opcode.type = TwoByteOpcode;
        emi.opcode.op = 0x0B;
        instDone = true;
        return ResetState;
    }
    return Vex3Of3State;
}

Decoder::State
Decoder::doVex3Of3State(uint8_t nextByte)
{
    if (emi.mode.submode != SixtyFourBitMode && bits(nextByte, 7, 6) == 0x3) {
        // This was actually an LES instruction. Reroute to that path.
        emi.vex.present = 0;
        emi.opcode.type = OneByteOpcode;
        emi.opcode.op = 0xC5;
        return processOpcode(ImmediateTypeOneByte, UsesModRMOneByte,
                             nextByte >= 0xA0 && nextByte <= 0xA3);
    }

    consumeByte();
    Vex3Of3 vex = nextByte;

    emi.rex.w = vex.w;

    emi.vex.l = vex.l;
    emi.vex.v = ~vex.v;

    switch (vex.p) {
      case 0:
        break;
      case 1:
        emi.legacy.op = 1;
        break;
      case 2:
        emi.legacy.rep = 1;
        break;
      case 3:
        emi.legacy.repne = 1;
        break;
    }

    return VexOpcodeState;
}

Decoder::State
Decoder::doVex3Of3StateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, uint8_t &altOp, uint8_t &defOp, uint8_t &altAddr, uint8_t &defAddr, uint8_t &stack, int &immediateSize, bool &instDone)
{
    if (emi.mode.submode != SixtyFourBitMode && bits(nextByte, 7, 6) == 0x3) {
        // This was actually an LES instruction. Reroute to that path.
        emi.vex.present = 0;
        emi.opcode.type = OneByteOpcode;
        emi.opcode.op = 0xC5;
        return processOpcodeStatic(ImmediateTypeOneByte, UsesModRMOneByte,
                            emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone, nextByte >= 0xA0 && nextByte <= 0xA3);
    }

    index++;
    Vex3Of3 vex = nextByte;

    emi.rex.w = vex.w;

    emi.vex.l = vex.l;
    emi.vex.v = ~vex.v;

    switch (vex.p) {
      case 0:
        break;
      case 1:
        emi.legacy.op = 1;
        break;
      case 2:
        emi.legacy.rep = 1;
        break;
      case 3:
        emi.legacy.repne = 1;
        break;
    }

    return VexOpcodeState;
}

Decoder::State
Decoder::doVexOpcodeState(uint8_t nextByte)
{
    printf("Found VEX opcode %#x.\n", nextByte);

    emi.opcode.op = nextByte;
    consumeByte();

    switch (emi.opcode.type) {
      case TwoByteOpcode:
        return processOpcode(ImmediateTypeTwoByte, UsesModRMTwoByte);
      case ThreeByte0F38Opcode:
        return processOpcode(ImmediateTypeThreeByte0F38,
                             UsesModRMThreeByte0F38);
      case ThreeByte0F3AOpcode:
        return processOpcode(ImmediateTypeThreeByte0F3A,
                             UsesModRMThreeByte0F3A);
      default:
        panic("Unrecognized opcode type %d.\n", emi.opcode.type);
    }
}

Decoder::State
Decoder::doVexOpcodeStateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, uint8_t &altOp, uint8_t &defOp, uint8_t &altAddr, uint8_t &defAddr, uint8_t &stack, int &immediateSize, bool &instDone)
{
    printf("Found VEX opcode %#x.\n", nextByte);

    emi.opcode.op = nextByte;
    index++;

    switch (emi.opcode.type) {
      case TwoByteOpcode:
        return processOpcodeStatic(ImmediateTypeTwoByte, UsesModRMTwoByte, emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
      case ThreeByte0F38Opcode:
        return processOpcodeStatic(ImmediateTypeThreeByte0F38,
                             UsesModRMThreeByte0F38, emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
      case ThreeByte0F3AOpcode:
        return processOpcodeStatic(ImmediateTypeThreeByte0F3A,
                             UsesModRMThreeByte0F3A, emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
      default:
        panic("Unrecognized opcode type %d.\n", emi.opcode.type);
    }
}

// Load the first opcode byte. Determine if there are more opcode bytes, and
// if not, what immediate and/or ModRM is needed.
Decoder::State
Decoder::doOneByteOpcodeState(uint8_t nextByte)
{
    State nextState = ErrorState;
    consumeByte();

    if (nextByte == 0x0f) {
        printf("Found opcode escape byte %#x.\n", nextByte);
        nextState = TwoByteOpcodeState;
    } else {
        printf("Found one byte opcode %#x.\n", nextByte);
        emi.opcode.type = OneByteOpcode;
        emi.opcode.op = nextByte;

        nextState = processOpcode(ImmediateTypeOneByte, UsesModRMOneByte,
                                  nextByte >= 0xA0 && nextByte <= 0xA3);
    }
    return nextState;
}

Decoder::State
Decoder::doOneByteOpcodeStateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, uint8_t &altOp, uint8_t &defOp, uint8_t &altAddr, uint8_t &defAddr, uint8_t &stack, int &immediateSize, bool &instDone)
{
    State nextState = ErrorState;
    index++;

    if (nextByte == 0x0f) {
        printf("Found opcode escape byte %#x.\n", nextByte);
        nextState = TwoByteOpcodeState;
    } else {
        printf("Found one byte opcode %#x.\n", nextByte);
        emi.opcode.type = OneByteOpcode;
        emi.opcode.op = nextByte;

        nextState = processOpcodeStatic(ImmediateTypeOneByte, UsesModRMOneByte,
                                  emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone, nextByte >= 0xA0 && nextByte <= 0xA3);
    }
    return nextState;
}

// Load the second opcode byte. Determine if there are more opcode bytes, and
// if not, what immediate and/or ModRM is needed.
Decoder::State
Decoder::doTwoByteOpcodeState(uint8_t nextByte)
{
    State nextState = ErrorState;
    consumeByte();
    if (nextByte == 0x38) {
        nextState = ThreeByte0F38OpcodeState;
        printf("Found opcode escape byte %#x.\n", nextByte);
    } else if (nextByte == 0x3a) {
        nextState = ThreeByte0F3AOpcodeState;
        printf("Found opcode escape byte %#x.\n", nextByte);
    } else {
        printf("Found two byte opcode %#x.\n", nextByte);
        emi.opcode.type = TwoByteOpcode;
        emi.opcode.op = nextByte;

        nextState = processOpcode(ImmediateTypeTwoByte, UsesModRMTwoByte);
    }
    return nextState;
}

Decoder::State
Decoder::doTwoByteOpcodeStateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, uint8_t &altOp, uint8_t &defOp, uint8_t &altAddr, uint8_t &defAddr, uint8_t &stack, int &immediateSize, bool &instDone)
{
    State nextState = ErrorState;
    index++;
    if (nextByte == 0x38) {
        nextState = ThreeByte0F38OpcodeState;
        printf("Found opcode escape byte %#x.\n", nextByte);
    } else if (nextByte == 0x3a) {
        nextState = ThreeByte0F3AOpcodeState;
        printf("Found opcode escape byte %#x.\n", nextByte);
    } else {
        printf("Found two byte opcode %#x.\n", nextByte);
        emi.opcode.type = TwoByteOpcode;
        emi.opcode.op = nextByte;

        nextState = processOpcodeStatic(ImmediateTypeTwoByte, UsesModRMTwoByte, emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
    }
    return nextState;
}

// Load the third opcode byte and determine what immediate and/or ModRM is
// needed.
Decoder::State
Decoder::doThreeByte0F38OpcodeState(uint8_t nextByte)
{
    consumeByte();

    printf("Found three byte 0F38 opcode %#x.\n", nextByte);
    emi.opcode.type = ThreeByte0F38Opcode;
    emi.opcode.op = nextByte;

    return processOpcode(ImmediateTypeThreeByte0F38, UsesModRMThreeByte0F38);
}

Decoder::State
Decoder::doThreeByte0F38OpcodeStateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, uint8_t &altOp, uint8_t &defOp, uint8_t &altAddr, uint8_t &defAddr, uint8_t &stack, int &immediateSize, bool &instDone)
{
    index++;

    printf("Found three byte 0F38 opcode %#x.\n", nextByte);
    emi.opcode.type = ThreeByte0F38Opcode;
    emi.opcode.op = nextByte;

    return processOpcodeStatic(ImmediateTypeThreeByte0F38, UsesModRMThreeByte0F38, emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
}

// Load the third opcode byte and determine what immediate and/or ModRM is
// needed.
Decoder::State
Decoder::doThreeByte0F3AOpcodeState(uint8_t nextByte)
{
    consumeByte();

    printf("Found three byte 0F3A opcode %#x.\n", nextByte);
    emi.opcode.type = ThreeByte0F3AOpcode;
    emi.opcode.op = nextByte;

    return processOpcode(ImmediateTypeThreeByte0F3A, UsesModRMThreeByte0F3A);
}

Decoder::State
Decoder::doThreeByte0F3AOpcodeStateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, uint8_t &altOp, uint8_t &defOp, uint8_t &altAddr, uint8_t &defAddr, uint8_t &stack, int &immediateSize, bool &instDone)
{
    index++;

    printf("Found three byte 0F3A opcode %#x.\n", nextByte);
    emi.opcode.type = ThreeByte0F3AOpcode;
    emi.opcode.op = nextByte;

    return processOpcodeStatic(ImmediateTypeThreeByte0F3A, UsesModRMThreeByte0F3A, emi, altOp, defOp, altAddr, defAddr, stack, immediateSize, instDone);
}

// Generic opcode processing which determines the immediate size, and whether
// or not there's a modrm byte.
Decoder::State
Decoder::processOpcode(ByteTable &immTable, ByteTable &modrmTable,
                       bool addrSizedImm)
{
    State nextState = ErrorState;
    const uint8_t opcode = emi.opcode.op;

    // Figure out the effective operand size. This can be overriden to
    // a fixed value at the decoder level.
    int logOpSize;
    if (emi.rex.w)
        logOpSize = 3; // 64 bit operand size
    else if (emi.legacy.op)
        logOpSize = altOp;
    else
        logOpSize = defOp;

    // Set the actual op size.
    emi.opSize = 1 << logOpSize;

    // Figure out the effective address size. This can be overriden to
    // a fixed value at the decoder level.
    int logAddrSize;
    if (emi.legacy.addr)
        logAddrSize = altAddr;
    else
        logAddrSize = defAddr;

    // Set the actual address size.
    emi.addrSize = 1 << logAddrSize;

    // Figure out the effective stack width. This can be overriden to
    // a fixed value at the decoder level.
    emi.stackSize = 1 << stack;

    // Figure out how big of an immediate we'll retreive based
    // on the opcode.
    int immType = immTable[opcode];
    if (addrSizedImm)
        immediateSize = SizeTypeToSize[logAddrSize - 1][immType];
    else
        immediateSize = SizeTypeToSize[logOpSize - 1][immType];

    // Determine what to expect next.
    if (modrmTable[opcode]) {
        nextState = ModRMState;
    } else {
        if (immediateSize) {
            nextState = ImmediateState;
        } else {
            instDone = true;
            nextState = ResetState;
        }
    }
    return nextState;
}

Decoder::State
Decoder::processOpcodeStatic(ByteTable &immTable, ByteTable &modrmTable,
                      ExtMachInst &emi,
                      uint8_t &altOp, uint8_t &defOp, uint8_t &altAddr, uint8_t &defAddr, uint8_t &stack, int &immediateSize, bool &instDone,
                      bool addrSizedImm)
{
    State nextState = ErrorState;
    const uint8_t opcode = emi.opcode.op;

    // Figure out the effective operand size. This can be overriden to
    // a fixed value at the decoder level.
    int logOpSize;
    if (emi.rex.w)
        logOpSize = 3; // 64 bit operand size
    else if (emi.legacy.op)
        logOpSize = altOp;
    else
        logOpSize = defOp;

    // Set the actual op size.
    emi.opSize = 1 << logOpSize;

    // Figure out the effective address size. This can be overriden to
    // a fixed value at the decoder level.
    int logAddrSize;
    if (emi.legacy.addr)
        logAddrSize = altAddr;
    else
        logAddrSize = defAddr;

    // Set the actual address size.
    emi.addrSize = 1 << logAddrSize;

    // Figure out the effective stack width. This can be overriden to
    // a fixed value at the decoder level.
    emi.stackSize = 1 << stack;

    // Figure out how big of an immediate we'll retreive based
    // on the opcode.
    int immType = immTable[opcode];
    if (addrSizedImm)
        immediateSize = SizeTypeToSize[logAddrSize - 1][immType];
    else
        immediateSize = SizeTypeToSize[logOpSize - 1][immType];

    // Determine what to expect next.
    if (modrmTable[opcode]) {
        nextState = ModRMState;
    } else {
        if (immediateSize) {
            nextState = ImmediateState;
        } else {
            instDone = true;
            nextState = ResetState;
        }
    }
    return nextState;
}

// Get the ModRM byte and determine what displacement, if any, there is.
// Also determine whether or not to get the SIB byte, displacement, or
// immediate next.
Decoder::State
Decoder::doModRMState(uint8_t nextByte)
{
    State nextState = ErrorState;
    ModRM modRM = nextByte;
    printf("Found modrm byte %#x.\n", nextByte);
    if (defOp == 1) {
        // Figure out 16 bit displacement size.
        if ((modRM.mod == 0 && modRM.rm == 6) || modRM.mod == 2)
            displacementSize = 2;
        else if (modRM.mod == 1)
            displacementSize = 1;
        else
            displacementSize = 0;
    } else {
        // Figure out 32/64 bit displacement size.
        if ((modRM.mod == 0 && modRM.rm == 5) || modRM.mod == 2)
            displacementSize = 4;
        else if (modRM.mod == 1)
            displacementSize = 1;
        else
            displacementSize = 0;
    }

    // The "test" instruction in group 3 needs an immediate, even though
    // the other instructions with the same actual opcode don't.
    if (emi.opcode.type == OneByteOpcode && (modRM.reg & 0x6) == 0) {
       if (emi.opcode.op == 0xF6)
           immediateSize = 1;
       else if (emi.opcode.op == 0xF7)
           immediateSize = (emi.opSize == 8) ? 4 : emi.opSize;
    }

    // If there's an SIB, get that next.
    // There is no SIB in 16 bit mode.
    if (modRM.rm == 4 && modRM.mod != 3) {
            // && in 32/64 bit mode)
        nextState = SIBState;
    } else if (displacementSize) {
        nextState = DisplacementState;
    } else if (immediateSize) {
        nextState = ImmediateState;
    } else {
        instDone = true;
        nextState = ResetState;
    }
    // The ModRM byte is consumed no matter what.
    consumeByte();
    emi.modRM = modRM;
    return nextState;
}

Decoder::State
Decoder::doModRMStateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, int &displacementSize, int &immediateSize, uint8_t &defOp, bool &instDone)
{
    State nextState = ErrorState;
    ModRM modRM = nextByte;
    printf("Found modrm byte %#x.\n", nextByte);
    if (defOp == 1) {
        // Figure out 16 bit displacement size.
        if ((modRM.mod == 0 && modRM.rm == 6) || modRM.mod == 2)
            displacementSize = 2;
        else if (modRM.mod == 1)
            displacementSize = 1;
        else
            displacementSize = 0;
    } else {
        // Figure out 32/64 bit displacement size.
        if ((modRM.mod == 0 && modRM.rm == 5) || modRM.mod == 2)
            displacementSize = 4;
        else if (modRM.mod == 1)
            displacementSize = 1;
        else
            displacementSize = 0;
    }

    // The "test" instruction in group 3 needs an immediate, even though
    // the other instructions with the same actual opcode don't.
    if (emi.opcode.type == OneByteOpcode && (modRM.reg & 0x6) == 0) {
       if (emi.opcode.op == 0xF6)
           immediateSize = 1;
       else if (emi.opcode.op == 0xF7)
           immediateSize = (emi.opSize == 8) ? 4 : emi.opSize;
    }

    // If there's an SIB, get that next.
    // There is no SIB in 16 bit mode.
    if (modRM.rm == 4 && modRM.mod != 3) {
            // && in 32/64 bit mode)
        nextState = SIBState;
    } else if (displacementSize) {
        nextState = DisplacementState;
    } else if (immediateSize) {
        nextState = ImmediateState;
    } else {
        instDone = true;
        nextState = ResetState;
    }
    // The ModRM byte is consumed no matter what.
    index++;
    emi.modRM = modRM;
    return nextState;
}

// Get the SIB byte. We don't do anything with it at this point, other
// than storing it in the ExtMachInst. Determine if we need to get a
// displacement or immediate next.
Decoder::State
Decoder::doSIBState(uint8_t nextByte)
{
    State nextState = ErrorState;
    emi.sib = nextByte;
    printf("Found SIB byte %#x.\n", nextByte);
    consumeByte();
    if (emi.modRM.mod == 0 && emi.sib.base == 5)
        displacementSize = 4;
    if (displacementSize) {
        nextState = DisplacementState;
    } else if (immediateSize) {
        nextState = ImmediateState;
    } else {
        instDone = true;
        nextState = ResetState;
    }
    return nextState;
}

Decoder::State
Decoder::doSIBStateStatic(uint8_t nextByte, ExtMachInst &emi, uint64_t &index, int &displacementSize, int &immediateSize, bool &instDone)
{
    State nextState = ErrorState;
    emi.sib = nextByte;
    printf("Found SIB byte %#x.\n", nextByte);
    index++;
    if (emi.modRM.mod == 0 && emi.sib.base == 5)
        displacementSize = 4;
    if (displacementSize) {
        nextState = DisplacementState;
    } else if (immediateSize) {
        nextState = ImmediateState;
    } else {
        instDone = true;
        nextState = ResetState;
    }
    return nextState;
}

// Gather up the displacement, or at least as much of it as we can get.
Decoder::State
Decoder::doDisplacementState()
{
    State nextState = ErrorState;

    getImmediate(immediateCollected,
            emi.displacement,
            displacementSize);

    printf("Collecting %d byte displacement, got %d bytes.\n",
            displacementSize, immediateCollected);

    if (displacementSize == immediateCollected) {
        // Reset this for other immediates.
        immediateCollected = 0;
        // Sign extend the displacement.
        switch(displacementSize)
        {
          case 1:
            emi.displacement = sext<8>(emi.displacement);
            break;
          case 2:
            emi.displacement = sext<16>(emi.displacement);
            break;
          case 4:
            emi.displacement = sext<32>(emi.displacement);
            break;
          default:
            panic("Undefined displacement size!\n");
        }
        printf("Collected displacement %#x.\n",
                emi.displacement);
        if (immediateSize) {
            nextState = ImmediateState;
        } else {
            instDone = true;
            nextState = ResetState;
        }

        emi.dispSize = displacementSize;
    }
    else
        nextState = DisplacementState;
    return nextState;
}

Decoder::State
Decoder::doDisplacementStateStatic(unsigned char* bytes, int byte_size, ExtMachInst &emi, uint64_t &index, int &displacementSize, int &immediateSize, int &immediateCollected, bool &instDone)
{
    State nextState = ErrorState;

    getImmediateStatic(bytes, byte_size, immediateCollected, emi.displacement, displacementSize, index);

    printf("Collecting %d byte displacement, got %d bytes.\n",
            displacementSize, immediateCollected);

    if (displacementSize == immediateCollected) {
        // Reset this for other immediates.
        immediateCollected = 0;
        // Sign extend the displacement.
        switch(displacementSize)
        {
          case 1:
            emi.displacement = sext<8>(emi.displacement);
            break;
          case 2:
            emi.displacement = sext<16>(emi.displacement);
            break;
          case 4:
            emi.displacement = sext<32>(emi.displacement);
            break;
          default:
            panic("Undefined displacement size!\n");
        }
        printf("Collected displacement %#x.\n",
                emi.displacement);
        if (immediateSize) {
            nextState = ImmediateState;
        } else {
            instDone = true;
            nextState = ResetState;
        }

        emi.dispSize = displacementSize;
    }
    else
        nextState = DisplacementState;
    return nextState;
}

// Gather up the immediate, or at least as much of it as we can get.
Decoder::State
Decoder::doImmediateState()
{
    State nextState = ErrorState;

    getImmediate(immediateCollected, emi.immediate, immediateSize);

    printf("Collecting %d byte immediate, got %d bytes.\n",
            immediateSize, immediateCollected);

    if (immediateSize == immediateCollected) {
        // Reset this for other immediates.
        immediateCollected = 0;

        //XXX Warning! The following is an observed pattern and might
        // not always be true!

        // Instructions which use 64 bit operands but 32 bit immediates
        // need to have the immediate sign extended to 64 bits.
        // Instructions which use true 64 bit immediates won't be
        // affected, and instructions that use true 32 bit immediates
        // won't notice.
        switch(immediateSize) {
          case 4:
            emi.immediate = sext<32>(emi.immediate);
            break;
          case 1:
            emi.immediate = sext<8>(emi.immediate);
        }

        printf("Collected immediate %#x.\n",
                emi.immediate);
        instDone = true;
        nextState = ResetState;
    } else {
        nextState = ImmediateState;
    }
    return nextState;
}

Decoder::State
Decoder::doImmediateStateStatic(unsigned char* bytes, int byte_size, ExtMachInst emi, uint64_t &index, int &immediateSize, int &immediateCollected, bool &instDone)
{
    State nextState = ErrorState;

    getImmediateStatic(bytes, byte_size, immediateCollected, emi.immediate, immediateSize, index);
    printf("Collecting %d byte immediate, got %d bytes.\n",
            immediateSize, immediateCollected);

    if (immediateSize == immediateCollected) {
        // Reset this for other immediates.
        immediateCollected = 0;

        //XXX Warning! The following is an observed pattern and might
        // not always be true!

        // Instructions which use 64 bit operands but 32 bit immediates
        // need to have the immediate sign extended to 64 bits.
        // Instructions which use true 64 bit immediates won't be
        // affected, and instructions that use true 32 bit immediates
        // won't notice.
        switch(immediateSize) {
          case 4:
            emi.immediate = sext<32>(emi.immediate);
            break;
          case 1:
            emi.immediate = sext<8>(emi.immediate);
        }

        printf("Collected immediate %#x.\n",
                emi.immediate);
        instDone = true;
        nextState = ResetState;
    } else {
        nextState = ImmediateState;
    }
    return nextState;
}

Decoder::InstBytes Decoder::dummy;
Decoder::InstCacheMap Decoder::instCacheMap;

StaticInstPtr
Decoder::decode(ExtMachInst mach_inst, Addr addr)
{
    StaticInstPtr si;

    auto iter = instMap->find(mach_inst);
    if (iter != instMap->end()) {
        si = iter->second;
    } else {
        si = decodeInst(mach_inst);
        (*instMap)[mach_inst] = si;
    }

    DPRINTF(Decode, "Decode: Decoded %s instruction: %#x\n",
            si->getName(), mach_inst);
    return si;
}

StaticInstPtr
Decoder::decode(PCStateBase &next_pc)
{
    if (!instDone)
        return NULL;
    instDone = false;
    updateNPC(next_pc.as<PCState>());

    StaticInstPtr &si = instBytes->si;
    if (si)
        return si;

    // We didn't match in the AddrMap, but we still populated an entry. Fix
    // up its byte masks.
    const int chunkSize = sizeof(MachInst);

    instBytes->lastOffset = offset;

    Addr firstBasePC = basePC - (instBytes->chunks.size() - 1) * chunkSize;
    Addr firstOffset = origPC - firstBasePC;
    Addr totalSize = instBytes->lastOffset - firstOffset +
        (instBytes->chunks.size() - 1) * chunkSize;
    int start = firstOffset;
    instBytes->masks.clear();

    while (totalSize) {
        int end = start + totalSize;
        end = (chunkSize < end) ? chunkSize : end;
        int size = end - start;
        int idx = instBytes->masks.size();

        MachInst maskVal = mask(size * 8) << (start * 8);
        assert(maskVal);

        instBytes->masks.push_back(maskVal);
        instBytes->chunks[idx] &= instBytes->masks[idx];
        totalSize -= size;
        start = 0;
    }

    si = decode(emi, origPC);
    return si;
}

StaticInstPtr
Decoder::fetchRomMicroop(MicroPC micropc, StaticInstPtr curMacroop)
{
    return microcodeRom.fetchMicroop(micropc, curMacroop);
}

} // namespace X86ISA
} // namespace gem5
