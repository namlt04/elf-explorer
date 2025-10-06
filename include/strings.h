

#include "elf.h"
#include "utils.h"
#include <stdio.h>

typedef void (*CallbackFunction) (char* buffer);

void display_strings_valid(FILE* file, CallbackFunction callback);