
#include "program.h"


char* get_program_type(const uint32_t type)
{
    char* buffer = (char*) malloc(BUFF_SIZE);
    buffer[0] = '\0';
    switch(type)
    {
        case PT_NULL:
            snprintf(buffer, BUFF_SIZE, "NULL");
            break;
        case PT_LOAD:
            snprintf(buffer, BUFF_SIZE, "LOAD");
            break;
        case PT_DYNAMIC:
            snprintf(buffer, BUFF_SIZE, "DYNAMIC");
            break;
        case PT_INTERP:
            snprintf(buffer, BUFF_SIZE, "INTERP");
            break;
        case PT_NOTE:
            snprintf(buffer, BUFF_SIZE, "NOTE");
            break;
        case PT_SHLIB:
            snprintf(buffer, BUFF_SIZE, "SHLIB");
            break;
        case PT_PHDR:
            snprintf(buffer, BUFF_SIZE, "PHDR");
            break;
        case PT_TLS:
            snprintf(buffer, BUFF_SIZE, "TLS");
            break;
        case PT_GNU_EH_FRAME:
            snprintf(buffer, BUFF_SIZE, "GNU_EH_FRAME");
            break;
        case PT_GNU_STACK:
            snprintf(buffer, BUFF_SIZE, "GNU_STACK");
            break;
        case PT_GNU_RELRO:
            snprintf(buffer, BUFF_SIZE, "GNU_RELRO");
            break;
        case PT_SUNWBSS:
            snprintf(buffer, BUFF_SIZE, "SUNWBSS");
            break;
        case PT_SUNWSTACK:
            snprintf(buffer, BUFF_SIZE, "SUNWSTACK");
            break;
        default:
            snprintf(buffer, BUFF_SIZE, "0x%08x: <unknow>", type);
            break;
    }
    return buffer;
    
}

char* get_program_offset(const uint64_t offset)
{
    char* buf = (char*) malloc(BUFF_SIZE); 
    snprintf(buf, BUFF_SIZE, "0x%016llx" , offset);
    return buf;

}
char* get_program_vaddr(const uint64_t vaddr)
{
    char* buf = (char*) malloc(BUFF_SIZE); 
    snprintf(buf, BUFF_SIZE, "0x%016llx" , vaddr);
    return buf;
}
char* get_program_paddr(const uint64_t paddr)
{
    char* buf = (char*) malloc(BUFF_SIZE); 
    snprintf(buf, BUFF_SIZE, "0x%016llx" , paddr);
    return buf;

}
char* get_program_filesz(const uint64_t filesz)
{
    char* buf = (char*) malloc(BUFF_SIZE); 
    snprintf(buf, BUFF_SIZE, "0x%016llu" , filesz);
    return buf;

}
char* get_program_memsz(const uint64_t memsz) 
{
    char* buf = (char*) malloc(BUFF_SIZE);
    snprintf(buf, BUFF_SIZE, "0x%016llu" , memsz);
    return buf;

}

char* get_program_flags(const uint32_t flags)
{
    char* buff = (char*) malloc(sizeof(char) * 4); // "RWE\0"
    int index = 0;

    buff[index++] = (flags & PF_R) ? 'R' : ' ';
    buff[index++] = (flags & PF_W) ? 'W' : ' ';
    buff[index++] = (flags & PF_X) ? 'E' : ' ';
    buff[index]   = '\0';

    return buff;
}
char* get_program_align(const uint64_t align)
{
    char* buf = (char*) malloc(BUFF_SIZE); 
    snprintf(buf, BUFF_SIZE, "%llu" , align);
    return buf;

}



MElf_Phdr **read_program_header(FILE* file, int is64, uint16_t e_phnum, uint64_t e_phoff)
{

    size_t size = (is64 ? sizeof(MElf64_Phdr) : sizeof(MElf32_Phdr)) * e_phnum;
    // size_t size = e_phentsize * e_phnum
    char* buffer = (char*) read_file(file, size, e_phoff);

    MElf_Phdr** headers = (MElf_Phdr**) malloc(sizeof(MElf_Phdr*) * e_phnum);
    uint16_t index = 0;
    for(; index < e_phnum; index++)
    { 
     
        MElf_Phdr *header = (MElf_Phdr*) malloc(sizeof(MElf_Phdr));
        headers[index] = header;   // Lư
        if (!is64)
        {
            MElf32_Phdr* elf32 = (MElf32_Phdr*) (buffer + index * sizeof(MElf32_Phdr));
            header->p_type = elf32->p_type;
            header->p_offset = elf32->p_offset;
            header->p_vaddr = elf32->p_vaddr;
            header->p_paddr = elf32->p_paddr; 
            header->p_filesz = elf32->p_filesz; 
            header->p_memsz = elf32->p_memsz;
            header->p_flags = elf32->p_flags; 
            header->p_align = elf32->p_align;

        } else 
        {
            MElf64_Phdr* elf64 = (MElf64_Phdr* ) (buffer + index * sizeof(MElf64_Phdr));
            header->p_type = elf64->p_type;
            header->p_offset = elf64->p_offset;
            header->p_vaddr = elf64->p_vaddr;
            header->p_paddr = elf64->p_paddr; 
            header->p_filesz = elf64->p_filesz;
            header->p_memsz = elf64->p_memsz;
            header->p_flags = elf64->p_flags; 
            header->p_align = elf64->p_align;
        }
    }



    free(buffer);
    return headers;

}

MElf_Phdr_Print** display_program_header (FILE* file, MElf_Ehdr* elf_header)
{

    MElf_Phdr** array = read_program_header(file,elf_header->e_ident[EI_CLASS] == ELFCLASS64, elf_header->e_phnum, elf_header->e_phoff);

    MElf_Phdr_Print** ret = (MElf_Phdr_Print**) malloc (elf_header->e_phnum * sizeof(MElf_Phdr_Print*));
    
    for (uint16_t i = 0; i < elf_header->e_phnum; i++)
    {
        MElf_Phdr_Print *header = (MElf_Phdr_Print*) malloc(sizeof(MElf_Phdr_Print));
        ret[i] = header; 
        // MElf_Phdr_Print *header = (MElf_Phdr_Print* ) ret[i];
  

        // ret[i] =(MElf_Phdr_Print* ) malloc(sizeof(MElf_Phdr_Print)); // ĐẴ từng lỗi ở đây segment fault 
        // cấp phát sai kích thước

        // header = (MElf_Phdr_Print* ) malloc(sizeof(MElf_Phdr_Print)); // ĐẴ từng lỗi ở đây segment fault 


        header->s_type = get_program_type(array[i]->p_type); 
        header->s_offset = get_program_offset(array[i]->p_offset); 
        header->s_vaddr = get_program_vaddr(array[i]->p_vaddr); 
        header->s_paddr = get_program_paddr(array[i]->p_paddr ); 
        header->s_filesz = get_program_filesz(array[i]->p_filesz); 
        header->s_memsz  = get_program_memsz(array[i]->p_memsz); 
        header->s_flags = get_program_flags(array[i]->p_flags); 
        header->s_align = get_program_align(array[i]->p_align);
    }




    return ret;

  

}
