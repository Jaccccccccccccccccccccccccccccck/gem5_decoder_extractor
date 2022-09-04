#include <iostream>

#include "arch/x86/decoder.hh"

using namespace std;

int main(int argc,char *argv[]) {
    unsigned char bytes[4];  // 48 83 ec 08
    bytes[0] = 0x48;
    bytes[1] = 0x83;
    bytes[2] = 0xec;
    bytes[3] = 0x08;
    gem5::X86ISA::ExtMachInst extInst = gem5::X86ISA::Decoder::getExtInst(bytes, 4);
    gem5::StaticInst *a = gem5::X86ISA::Decoder::decodeInst(extInst).get();
    cout << a->getName() << endl;
}