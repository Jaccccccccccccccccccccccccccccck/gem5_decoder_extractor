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
    // test_decode_elf_arm("../test/hello.arm64");
    if (argc != 2) {
        cout << "need a hex inst arg! eg. d50342df" << endl;
        exit(1);
    }
    int64_t inst = strtoul(argv[1], nullptr, 16);
    gem5::StaticInst* a = gem5::ArmISA::Decoder::decode_inst(inst).get();
    cout << a->getName() << endl;
}