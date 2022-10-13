#include <iostream>

#include "arch/x86/decoder.hh"

using namespace std;

void test_decode_elf_arm(const char* file_path) {
    std::vector<gem5::StaticInst *> insts;
    gem5::X86ISA::Decoder::decode_elf_x86(file_path, insts);
    cout << "elf .text insts count: " << insts.size() << endl;
    cout << "first 10 insts opcode ..." << endl;
    std::cout << std::hex << &insts << std::endl;
    for (int i = 0; i < 10 && i < insts.size(); i++) {
        cout << hex << insts[i] << " : "<< insts[i]->getName() << endl;
    }
}

int main(int argc, char* argv[]) {
    test_decode_elf_arm("../test/hello.x86");
    // unsigned char bytes1[6];  // ff 25 aa 0a 20 00 : jmpq   *0x200aaa(%rip)        # 200fd0 <printf@GLIBC_2.2.5>
    // bytes1[0] = 0xff;
    // bytes1[1] = 0x25;
    // bytes1[2] = 0xaa;
    // bytes1[3] = 0x0a;
    // bytes1[4] = 0x20;
    // bytes1[5] = 0x00;
    // gem5::X86ISA::ExtMachInst extInst = gem5::X86ISA::Decoder::getExtInst(bytes1, sizeof(bytes1));
    // gem5::StaticInst *a = gem5::X86ISA::Decoder::decodeInst(extInst).get();
    // unsigned char bytes2[4];  // 48 83 ec 08  sub    $0x8,%rsp
    // bytes2[0] = 0x48;
    // bytes2[1] = 0x83;
    // bytes2[2] = 0xec;
    // bytes2[3] = 0x08;
    // gem5::X86ISA::ExtMachInst extInst2 = gem5::X86ISA::Decoder::getExtInst(bytes2, sizeof(bytes2));
    // gem5::StaticInst *b = gem5::X86ISA::Decoder::decodeInst(extInst2).get();
    // cout << b->getName() << endl;

    // unsigned char bytes3[2];  // 48 83 ec 08  sub    $0x8,%rsp
    // bytes2[0] = 0x66;
    // bytes2[1] = 0x90;
    // gem5::X86ISA::ExtMachInst extInst3 = gem5::X86ISA::Decoder::getExtInst(bytes2, sizeof(bytes2));
    // gem5::StaticInst *c = gem5::X86ISA::Decoder::decodeInst(extInst3).get();
    // cout << c->getName() << endl;
}