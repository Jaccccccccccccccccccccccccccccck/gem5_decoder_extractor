#include <iostream>

#include "arch/arm/decoder.hh"
#include "arch/arm/insts/static_inst.hh"
#include "cpu/static_inst_fwd.hh"

using namespace std;

void test_decode_elf_arm(const char* file_path) {
    std::vector<gem5::StaticInst *> insts;
    gem5::ArmISA::Decoder::decode_elf_arm(file_path, insts);
    cout << "elf .text insts count: " << insts.size() << endl;
    cout << "first 10 insts opcode ..." << endl;
    std::cout << std::hex << &insts << std::endl;
    // for (int i = 0; i < 10 && i < insts.size(); i++) {
    //     cout << hex << insts[i] << " : "<< insts[i]->getName() << endl;
    // }
}

int main(int argc, char* argv[]) {
    test_decode_elf_arm("../test/hello.arm64");
    if (argc != 2) {
        cout << "need a hex inst arg! eg. d50342df" << endl;
        exit(1);
    }
    int64_t inst = strtoul(argv[1], nullptr, 16);
    inst |= 1L << 34; // set bit 34 of inst = 1, bit 34 of inst is a extra flag for aarch64 of ExtMachInst; 
    gem5::StaticInst *a = gem5::ArmISA::Decoder::decodeInst(inst).get();
    
    // cout << "disassembly: " << a->disassemble(0x00000001, nullptr) << endl;
    cout << "op class: " << a->getName() << endl;
    bool isMicroop = a->isMicroop();
    bool isMacroop = a->isMacroop();
    cout << "is micro op: " << isMicroop << endl;
    cout << "is macro op: " << isMacroop << endl;

    // a->fetchMicroop(0x0);
    // gem5::StaticInst *a0 = a->fetchMicroop(0).get();


    int num_src_regs = a->numSrcRegs();
    int num_dest_regs = a->numDestRegs();
    cout << "numSrcRegs: " << num_src_regs << endl;
    cout << "numDestRegs: " << num_dest_regs << endl;
    for (int i = 0; i < num_src_regs; i++) {
        cout << "Src register: " << a->srcRegIdx(i) << endl;
    }
    for (int i = 0; i < num_dest_regs; i++) {
        cout << "Dest register: " << a->destRegIdx(i) << endl;
    }
}