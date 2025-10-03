#include "elf.h"
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"
#include "header.h"

typedef struct
{
    char* s_type; 
    char* s_offset;
    char* s_vaddr;
    char* s_paddr;
    char* s_filesz;
    char* s_memsz;
    char* s_align;
    char* s_flags; 

} MElf_Phdr_Print;


inline char* get_type(const uint32_t type);
inline char* get_offset(const uint64_t offset);
char* get_vaddr(const uint64_t vaddr);
char* get_paddr(const uint64_t paddr);
char* get_filesz(const uint64_t filesz);
char* get_memsz(const uint64_t memsz);
inline char* get_flags(const uint64_t align);
char* get_align(const uint32_t flags);





MElf_Phdr_Print** display_program_header(FILE* file, MElf_Ehdr* elf_header);
MElf_Phdr** read_program_header(FILE* file, int is64, uint32_t e_phnum, uint64_t e_phoff); 