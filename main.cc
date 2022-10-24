#include <iostream>

#include "arch/arm/decoder.hh"
#include "arch/arm/generated/decoder.hh"
#include "arch/arm/insts/static_inst.hh"
#include "cpu/static_inst_fwd.hh"
#include "shm/shm.h"

using namespace std;

void test_decode_elf_arm(const char* file_path) {
    std::vector<gem5::StaticInstPtr> insts;
    gem5::ArmISA::Decoder::decode_elf_arm(file_path, insts);
    cout << "elf .text insts count: " << insts.size() << endl;
    cout << "first 10 insts opcode ..." << endl;
    for (int i = 0; i < 10 && i < insts.size(); i++) {
        cout << i << " : " << hex << insts[i]->getEMI() << " " << insts[i]->getName() << endl;
    }
}

void get_inst_size() {
    printf("  size of RefCounted class: %d\n", sizeof(gem5::RefCounted));
    printf("  size of RegId class: %d\n", sizeof(gem5::RegId));
    printf("  size of StaticInstFlags class: %d\n", sizeof(gem5::StaticInstFlags));
    std::bitset<36> flags;
    printf("  size of bitset<36>: %d\n", sizeof(flags));
    std::unique_ptr<std::string> cachedDisassembly;
    printf("  size of std::unique_ptr<std::string>: %d\n", sizeof(cachedDisassembly));
    
    printf("get size of inst classes:\n");
    printf("  size of static inst: %d\n", sizeof(gem5::StaticInst));
    printf("  size of arm static inst: %d\n", sizeof(gem5::ArmISA::ArmStaticInst));
    printf("  size of arm mightBeMemory64 inst: %d\n", sizeof(gem5::ArmISA::MightBeMicro64));
    printf("  size of arm memory64 inst: %d\n", sizeof(gem5::ArmISA::Memory64));
    printf("  size of arm memoryImm64 inst: %d\n", sizeof(gem5::ArmISA::MemoryImm64));
    printf("  size of arm LDR inst: %d\n", sizeof(gem5::ArmISAInst::LDRX64_IMM));
    printf("  ------\n");
    printf("  size of arm PreOp inst: %d\n", sizeof(gem5::ArmISA::PredOp));
    printf("  size of arm PreMacroOp inst: %d\n", sizeof(gem5::ArmISA::PredMacroOp));
    printf("  size of arm PairMemOp inst: %d\n", sizeof(gem5::ArmISA::PairMemOp));
    printf("  size of arm LDP inst: %d\n", sizeof(gem5::ArmISAInst::LdpStp));
    printf("  ------\n");
    printf("  size of arm BranchReg64 inst: %d\n", sizeof(gem5::ArmISA::BranchReg64));
    printf("  size of arm BranchRet64 inst: %d\n", sizeof(gem5::ArmISA::BranchRet64));
    printf("  size of arm Ret64 inst: %d\n", sizeof(gem5::ArmISAInst::Ret64));
    printf("  ------\n");
    printf("  size of arm BranchReg64 inst: %d\n", sizeof(gem5::ArmISA::BranchReg64));
    printf("  size of arm Br64 inst: %d\n", sizeof(gem5::ArmISAInst::Br64));
    printf("  ------\n");
    printf("  size of arm DataXImmOp inst: %d\n", sizeof(gem5::ArmISA::DataXImmOp));
    printf("  size of arm AddXImm inst: %d\n", sizeof(gem5::ArmISAInst::AddXImm));
}

void test_copy_inst() {
    int64_t inst = strtoul("d50342df", nullptr, 16);
    gem5::StaticInstPtr a = gem5::ArmISA::Decoder::decode_inst(inst);
    cout << "size of *staticInstPtr :" << sizeof(*a) << endl;
    cout << "size of *staticInstPtr :" << sizeof(*a.get()) << endl;
    printf("inst addr:%p\n", a);
    cout << "opcode : " << a->getName() << endl;

    char inst_bytes[128];
    // use asBytes copy a inst, error
    // a->asBytes(inst_bytes, 128);
    memcpy(inst_bytes, a.get(), sizeof(gem5::ArmISA::ArmStaticInst));
    gem5::ArmISA::ArmStaticInst* copied_inst = (gem5::ArmISA::ArmStaticInst*)inst_bytes;
    printf("copied inst addr:%p\n", copied_inst);
    cout << "copied inst op class: " << copied_inst->getName() << endl;
}

void init_shared_mem() {
    // init a shm for bb_inst_info
    char chm_file_path_arg[64];
    char rm_chm_file_comman[64];
    strcpy(chm_file_path_arg, "/tmp/inst");
    strcpy(rm_chm_file_comman, "rm /tmp/inst");
    system(rm_chm_file_comman);
    if (!get_shm_user_base()) {
        if (shm_init(NULL, chm_file_path_arg)) {
            printf("init shm done\n");
        } else {
            printf("init share mem error!\n");
            exit(0);
        }
    }
}
int main(int argc, char* argv[]) {
    // test_decode_elf_arm("../test/hello.arm64");
    get_inst_size();
    // test_copy_inst();
    init_shared_mem();
    if (argc != 2) {
        cout << "need a hex inst arg! eg. d50342df" << endl;
        exit(1);
    }
    int64_t inst = strtoul(argv[1], nullptr, 16);
    gem5::StaticInstPtr a = gem5::ArmISA::Decoder::decode_inst(inst);
    cout << "opcode of " << hex << argv[1] << ": " << a->getName() << endl;

}