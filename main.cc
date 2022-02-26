#include <iostream>

#include "arch/sparc/decoder.hh"

using namespace std;

int main(int argc,char *argv[]) {
    if (argc != 2) {
        cout << "need a hex inst arg! eg. d50342df" << endl;
        exit(1);
    }
    int64_t inst = strtoul(argv[1], nullptr, 16);
    inst |= 1L << 34; // set bit 34 of inst = 1, bit 34 of inst is a extra flag for aarch64 of ExtMachInst; 
    gem5::StaticInst *a = gem5::SparcISA::Decoder::decodeInst(inst).get();
    cout << a->getName() << endl;
}