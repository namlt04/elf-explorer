#include "elf.h"
#include "utils.h"
#include "header.h"
#include <stdio.h>





char* get_name(const uint32_t name);
inline char* get_type(const uint32_t type); 
inline char* get_flags(const uint64_t flags); 
char* get_addr(const uint64_t addr); 
inline char* get_offset(const uint64_t offset); 
char* get_size(const uint64_t size); 
char* get_link(const uint32_t link); 
char* get_info(const uint32_t info); 
char* get_addralign(const uint64_t addralign);
char* get_entsize(const uint64_t entsize);

MElf_Shdr **get_section_header(FILE* file, int is64, uint32_t e_shnum, uint64_t e_shoff);


MElf_Shdr_Print** display_section_header(FILE* file, MElf_Ehdr* elf_header);
