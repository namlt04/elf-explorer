#pragma once
#include "elf.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include <string.h>
#include <inttypes.h>

typedef struct
{
  char* s_magic;
  char* s_class; 
  char* s_data;
  char* s_version; 
  char* s_osabi;
  char* s_abiversion; 
  char* s_type; 
  char* s_machine; 
  char* s_version0; // e_version
  char* s_entrypoint_address; // e_entry
  char* s_start_of_program_header; // e_phoff
  char* s_start_of_section_header; // e_shoff 
  char* s_flags; // e_falgs
  char* s_size_of_this_header;  // e_ehsize
  char* s_size_of_program_header;  // e_phentsize
  char* s_number_of_program_header; // e_phnum
  char* s_size_of_section_header; // e_shentsize 
  char* s_number_of_section_header; // e_shnum
  char* s_section_header_string_table_index; // e_shstrndx
} MEhdr_Print;

// Main function
MEhdr_Print* display_elf_header(MElf_Ehdr* elf_header);

// Helpers - parse ELF header
MElf_Ehdr* read_header_file(FILE* file);

// String formatters
char* get_magic(const unsigned char* e_ident);
char* get_class(const unsigned char* e_ident);
char* get_data(const unsigned char* e_ident);
char* get_elf_version(unsigned char* e_ident);
char* get_osabi_name(unsigned char* osabi);
char* get_abi_version(uint8_t abi_version);
char* get_file_type(uint16_t e_type);
char* get_machine_name(uint16_t e_machine);
char* get_number_of_program_header(const uint16_t e_phnum);

char* get_section_header_string_table_index();
// Numeric to string converters
char* get_entrypoint_address(uint32_t entrypoint);
char* get_start_of_program_header(uint64_t phoff);
char* get_start_of_section_header(uint64_t shoff);
char* get_size_of_this_header(uint16_t ehsize);
char* get_size_of_program_header(uint16_t phentsize);
char* get_size_of_section_header(uint16_t shentsize);
char* get_number_of_section_header(uint64_t shnum);
char* get_section_header_string_table_index_header(uint64_t shstrndx);
char* get_type(uint16_t type);
char* get_version_num(uint32_t version); // tránh trùng với get_version(e_ident)
char* get_flags(uint32_t flags);







