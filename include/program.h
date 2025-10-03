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


char* get_program_type(const uint32_t type);

char* get_program_offset(const uint64_t offset);
char* get_program_vaddr(const uint64_t vaddr);
char* get_program_paddr(const uint64_t paddr);
char* get_program_filesz(const uint64_t filesz);
char* get_program_memsz(const uint64_t memsz);
char* get_program_flags(const uint32_t flags);
char* get_program_align(const uint64_t align);





MElf_Phdr_Print** display_program_header(FILE* file, MElf_Ehdr* elf_header);
MElf_Phdr** read_program_header(FILE* file, int is64, uint16_t e_phnum, uint64_t e_phoff); 