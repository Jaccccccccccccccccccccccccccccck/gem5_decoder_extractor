#include <iostream>

#include "arch/arm/decoder.hh"
#include "arch/arm/generated/decoder.hh"
#include "arch/arm/insts/static_inst.hh"
#include "cpu/static_inst_fwd.hh"

using namespace std;

void test_decode_elf_arm(const char* file_path) {
    std::vector<gem5::StaticInstPtr> insts = gem5::ArmISA::Decoder::decode_elf_arm(file_path);
    cout << "elf .text insts count: " << insts.size() << endl;
    // for (int i = 0; i < 1000 && i < insts.size(); i++) {
    //     if(insts[i]->isMemRef()) {
    //         cout << i << " : " << " " << insts[i]->getName() <<  " is mem " << endl;
    //     }
    // }
}

void get_inst_size() {
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
    printf("  ------\n");
    printf("  size of arm Bl64 inst: %d\n", sizeof(gem5::ArmISAInst::Bl64));
    printf("  size of arm STRW64_IMM inst: %d\n", sizeof(gem5::ArmISAInst::STRW64_IMM));
    printf("  size of arm LDRHFP64_REG inst: %d\n", sizeof(gem5::ArmISAInst::LDRHFP64_REG));
    printf("  size of arm Movz inst: %d\n", sizeof(gem5::ArmISAInst::Movz));
    printf("  size of gem5 RegId inst: %d\n", sizeof(gem5::RegId));
    printf("  size of arm MemoryAtomicPair64 inst: %d\n", sizeof(gem5::ArmISA::MemoryAtomicPair64));
    printf("  size of arm CASP64 inst: %d\n", sizeof(gem5::ArmISAInst::CASP64));
    printf("  size of arm CmnsRegPclr inst: %d\n", sizeof(gem5::ArmISAInst::CmnsRegPclr));
    printf("  size of arm STSMAXH inst: %d\n", sizeof(gem5::ArmISAInst::STSMAXH));
    printf("  size of arm LOAD_REG_PY_AY_WY_SN_UN_SZ1Acc inst: %d\n", sizeof(gem5::ArmISAInst::LOAD_REG_PY_AY_WY_SN_UN_SZ1Acc));
    printf("  size of arm LOAD_IMM_PY_AN_WY_SY_UY_SZ1Acc inst: %d\n", sizeof(gem5::ArmISAInst::LOAD_IMM_PY_AN_WY_SY_UY_SZ1Acc));
    printf("  size of arm LOAD_IMM_PN_AY_WY_SY_UN_SZ2Acc inst: %d\n", sizeof(gem5::ArmISAInst::LOAD_IMM_PN_AY_WY_SY_UN_SZ2Acc));
    printf("  size of arm STORE_IMM_PN_AY_WY_SN_UN_SZ2 inst: %d\n", sizeof(gem5::ArmISAInst::STORE_IMM_PN_AY_WY_SN_UN_SZ2));
    printf("  size of arm SasxReg inst: %d\n", sizeof(gem5::ArmISAInst::SasxReg));
    printf("  size of arm BxjReg inst: %d\n", sizeof(gem5::ArmISAInst::BxjReg));
    printf("  size of arm SbcImm inst: %d\n", sizeof(gem5::ArmISAInst::SbcImm));
    printf("  size of arm NopInst inst: %d\n", sizeof(gem5::ArmISAInst::NopInst));
    printf("  size of arm LDXRX64 inst: %d\n", sizeof(gem5::ArmISAInst::LDXRX64));
    printf("  size of arm LDXRW64 inst: %d\n", sizeof(gem5::ArmISAInst::LDXRW64));
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

void test_decode_mem(const char *file_path) {
    std::vector<gem5::ArmISA::MemInfo*> insts = gem5::ArmISA::Decoder::decode_elf_arm_mem_info(file_path);
    cout << "elf .text insts count: " << insts.size() << endl;
    // for (int i = 0; i < 1000 && i < insts.size(); i++) {
    //     if(insts[i]->isMem) {
    //         cout << i << " : " << " " << insts[i]->isMem <<  " is mem " << endl;
    //     }
    // }
}

int main(int argc, char* argv[]) {
    // test_decode_mem("../test/hello.arm64");
    // test_decode_elf_arm("../test/hello.arm64");
    // test_decode_elf_arm("../test/hello.arm64");
    //gem5::ArmISA::MemInfo* mem_info = gem5::ArmISA::Decoder::decode_mem(0xa9bf7bfd);
    //cout << mem_info->isMem << endl;
    //gem5::ArmISA::Decoder::compare_decode_mem_info("../test/hello.arm64");
    // get_inst_size();
    // test_copy_inst();
    if (argc != 2) {
        cout << "need a hex inst arg! eg. d50342df" << endl;
        exit(1);
    }
    int32_t inst = strtoul(argv[1], nullptr, 16);
    cout << "decoding " << argv[1] << endl; 
    gem5::StaticInstPtr a = gem5::ArmISA::Decoder::decode_inst(inst);
    cout << "is Macro op: " << a->isMacroop() << endl;
    cout << "opcode of " << hex << argv[1] << ": " << a->getName() << endl;

}