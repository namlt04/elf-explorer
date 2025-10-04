#pragma once
#include "elf.h"
#include "utils.h"
#include "program.h"
#include <stdio.h>


char* get_dynamic_load_tag(const int64_t tag);
char* get_dynamic_load_type(const uint64_t val);
char* get_dynamic_load_name(const uint64_t ptr);
MElf_Dyn** get_dynamic_array( FILE* file, MElf_Phdr** phdr, MElf_Ehdr* elf_header);
MElf_Dyn_Print** display_load_library(FILE* file,MElf_Ehdr* elf_header, MElf_Phdr** program_header);
