
#pragma once
#include "elf.h"
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

char* read_file(FILE* file, size_t size, off_t off );


int check_magic_number(char* edient);

char* get_string_by_index(char* strtab,int index);
