#include "utils.h"

char* read_file(FILE* file, size_t size, off_t off )
{
    char* buffer = (char*) malloc(size);
    if ( !file)
    {
        printf("Khong the mo duoc file"); 
    }
    
    int n = fseeko(file, off , SEEK_SET);
    if ( n != 0)
    {
        printf("Loi khong the di chuyen con tro file"); 
    }
    int large = fread(buffer, size, 1, file);

    return buffer;
    
}


int check_magic_number(char* edient)
{
    return ( edient[EI_MAG0] != ELFMAG0 || edient[EI_MAG1] != ELFMAG1  || edient[EI_MAG2] != ELFMAG2 || edient[EI_MAG3] != ELFMAG3);
    // khai bao cac co dau tien
}

char* get_string_table(FILE* file, MElf_Ehdr* ehdr, MElf_Shdr** shdr)
{
    MElf_Shdr* shrs_name = (MElf_Shdr*) shdr[ehdr->e_shstrndx];

    char* buffer = read_file(file, shrs_name->sh_size, shrs_name->sh_offset);
    return buffer;
}
char* get_string_by_index(char* strtab,int index)
{
    return &strtab[index];
}