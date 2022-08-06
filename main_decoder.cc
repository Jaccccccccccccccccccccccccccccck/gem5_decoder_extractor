#include <iostream>

#include "arch/x86/decoder.hh"

using namespace std;

int main(int argc,char *argv[]) {
    if (argc != 2) {
        cout << "need a hex inst arg! eg. d50342df" << endl;
        exit(1);
    }
    gem5::X86ISA::ExtMachInst inst;
    gem5::StaticInst *a = gem5::X86ISA::Decoder::decodeInst(inst).get();
    cout << a->getName() << endl;
}