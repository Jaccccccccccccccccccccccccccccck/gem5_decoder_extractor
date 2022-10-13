/*
 * decodeELF function implementation
 */
#include <array>
#include <string> 
#include <err.h>
#include <fcntl.h>
#include <gelf.h>
#include <libelf.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>
#include <bsd/vis.h>
#include <string.h>
#include <vector> 


#include "arch/x86/decoder.hh"
#include "arch/x86/insts/static_inst.hh"


namespace gem5
{

namespace X86ISA
{

/*
get bits insts from elf .text
*/
std::vector<char> 
get_all_text_insts_fix32(const char *file_path) {
    std::vector<char> res;
    int fd;
    Elf* e;
    char *name;
    char *p;
    Elf_Scn* scn;
    Elf_Data* data;

    GElf_Shdr shdr;
    size_t n, shstrndx, sz;
    if (elf_version(EV_CURRENT) == EV_NONE)
        errx(EX_SOFTWARE,
             " ELF library initialization "
             " failed : % s ",
             elf_errmsg(-1));
    if ((fd = open(file_path, O_RDONLY, 0)) < 0)
        err(EX_NOINPUT, " open \" %s \" failed ", file_path);
    if ((e = elf_begin(fd, ELF_C_READ, NULL)) == NULL)
        errx(EX_SOFTWARE, " elf_begin () failed : % s . ",
             elf_errmsg(-1));
    if (elf_kind(e) != ELF_K_ELF)
        errx(EX_DATAERR, " % s is not an ELF object . ",
             file_path);
    if (elf_getshdrstrndx(e, &shstrndx) != 0)
        errx(EX_SOFTWARE, " elf_getshdrstrndx () failed : % s . ",
               elf_errmsg(-1));
    scn = NULL;
    while ((scn = elf_nextscn(e, scn)) != NULL) {
        if (gelf_getshdr(scn, &shdr) != &shdr) 
            errx(EX_SOFTWARE, " getshdr () failed : % s . ", elf_errmsg(-1));
        if ((name = elf_strptr(e, shstrndx, shdr.sh_name)) == NULL)
            errx(EX_SOFTWARE, " elf_strptr () failed : % s . ",
                   elf_errmsg(-1));
        // (void)printf(" Section %-4.4jd %s \n ", (uintmax_t)elf_ndxscn(scn), name);
        data = elf_getdata(scn, data);
        // if (shdr.sh_flags & 0x4) {
        //     printf("is a executable section \n");
        // } else {
        //     printf("is not a executable section \n");
        // }
        n = 0;
        if (strcmp(name, ".text") == 0 && data != NULL) {
            printf(".text code size: %d\n", data->d_size);
            p = (char *) data->d_buf;
            while ((((char *)p)<(char*)data -> d_buf + data->d_size)) {
                if (n < 256) {
                    printf("%hhx", *p);
                    if (n % 64 == 0) {
                        printf("\n");
                    }
                }
                res.push_back(*p);
                p++;
                n++;

            }
        }
    }

    if ((scn = elf_getscn(e, shstrndx)) == NULL)
        errx(EX_SOFTWARE, " getscn () failed : % s . ",
               elf_errmsg(-1));
    if (gelf_getshdr(scn, &shdr) != &shdr)
        errx(EX_SOFTWARE, " getshdr ( shstrndx ) failed : % s . ",
             elf_errmsg(-1));
    (void)putchar('\n');
    (void)elf_end(e);
    (void)close(fd);
    return res;
}

void Decoder::decode_elf_x86(const char* file_path, std::vector<gem5::StaticInstPtr>& res) {
    std::vector<char> inst_bytes = get_all_text_insts_fix32(file_path);
    unsigned char* bytes = reinterpret_cast<unsigned char*>(inst_bytes.data());
    int offset = 0;
    unsigned long int consumed_bytes = 0;
    int count = 0;
    while (consumed_bytes < inst_bytes.size()) {
        gem5::StaticInstPtr tmp = Decoder::decodeInst(Decoder::predecode(bytes, inst_bytes.size() - consumed_bytes, offset));
        res.push_back(tmp);
        // std::cout << std::hex << &(res.back()) << " : " << res.back()->getName() << std::endl;
        bytes += offset;
        consumed_bytes += offset;
    }
}
} // namespace ArmISA
} // namespace gem5