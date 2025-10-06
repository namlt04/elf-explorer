#include "section.h"


// goifile

char* get_section_name(char* strtab, const uint32_t name)
{
    char* buff = (char*) malloc(BUFF_SIZE);
    char* ret = get_string_by_index(strtab, name);
    buff[0] = '\0'; 
    snprintf(buff, BUFF_SIZE, "%s", ret);
    return buff;
}
char* get_section_type(const uint32_t type)
{
    char* buff = (char*) malloc(BUFF_SIZE);
    buff[0] = '\0'; 
    switch (type) {
        case SHT_NULL:
            return "NULL";
        case SHT_PROGBITS:
            return "PROGBITS";
        case SHT_SYMTAB:
            return "SYMTAB";
        case SHT_STRTAB:
            return "STRTAB";
        case SHT_RELA:
            return "RELA";
        case SHT_HASH:
            return "HASH"; 
        case SHT_DYNAMIC:
            return "DYNAMIC";
        case SHT_NOTE:
            return "NOTE";
        case SHT_NOBITS:
            return "NOBITS";
        case SHT_REL:
            return "REL";
        case SHT_SHLIB:
            return "SHLIB";
        case SHT_DYNSYM:
            return "DYNSYM";
        case SHT_INIT_ARRAY:
            return "INIT_ARRAY";
        case SHT_FINI_ARRAY:
            return "FINI_ARRAY";
        case SHT_PREINIT_ARRAY:
            return "PREINIT_ARRAY";
        case SHT_GROUP:
            return "GROUP";
        case SHT_SYMTAB_SHNDX:
            return "STMTAB SECTION INDICES";
        default:
            snprintf(buff, BUFF_SIZE, "%08x: <unknown>", type); 
    }
    return buff;
}
char *get_section_flags(const uint64_t flags) {
  char* buff = (char*) malloc(BUFF_SIZE);
  uint64_t mask = 1;
  int index = 0;
  while (flags >= mask) {
    switch (flags & mask) {
    case SHF_WRITE:
      buff[index] = 'W';
      break;
    case SHF_ALLOC:
      buff[index]= 'A';
      break;
    case SHF_EXECINSTR:
      buff[index] = 'X';
      break;
    case SHF_MERGE:
      buff[index] = 'M';
      break;
    case SHF_STRINGS:
      buff[index] = 'S';
      break;
    case SHF_INFO_LINK:
      buff[index] = 'I';
      break;
    case SHF_LINK_ORDER:
      buff[index] = 'L';
      break;
    case SHF_OS_NONCONFORMING:
      buff[index] = 'O';
      break;
    case SHF_GROUP:
      buff[index] = 'G';
      break;
    case SHF_TLS:
      buff[index] = 'T';
      break;
    case SHF_COMPRESSED:
      buff[index] = 'C';
      break;
    default:
      mask <<= 1;
      continue;
    }

    index++;
    mask <<= 1;
  }

  buff[index] = '\0';

  return buff;
}


char* get_section_addr(const uint64_t addr)
{
    char* buff = (char*) malloc(BUFF_SIZE);
    buff[0] = '\0'; 
    snprintf(buff, BUFF_SIZE, "%016llx", addr);
    return buff;
}
char* get_section_offset(const uint64_t offset)
{
    char* buff = (char*) malloc(BUFF_SIZE);
    buff[0] = '\0'; 
    snprintf(buff, BUFF_SIZE, "%08llx", offset);
    return buff;
}
char* get_section_size(const uint64_t size)
{
    char* buff = (char*) malloc(BUFF_SIZE);
    buff[0] = '\0'; 
    snprintf(buff, BUFF_SIZE, "%016llx", size);
    return buff;
}
char* get_section_link(const uint32_t link)
{
    char* buff = (char*) malloc(BUFF_SIZE);
    buff[0] = '\0'; 
    snprintf(buff, BUFF_SIZE, "%u", link);
    return buff;
}
char* get_section_info(const uint32_t info)
{
    char* buff = (char*) malloc(BUFF_SIZE);
    buff[0] = '\0'; 
    snprintf(buff, BUFF_SIZE, "%u", info);
    return buff;
}
char* get_section_addralign(const uint64_t addralign)
{
    char* buff = (char*) malloc(BUFF_SIZE);
    buff[0] = '\0'; 
    snprintf(buff, BUFF_SIZE, "%llu", addralign);
    return buff;
}
char* get_section_entsize(const uint64_t entsize)
{

    char* buff = (char*) malloc(BUFF_SIZE);
    buff[0] = '\0'; 
    snprintf(buff, BUFF_SIZE, "%016llx", entsize);
    return buff;
}
MElf_Shdr **get_section_header(FILE* file, int is64, uint32_t e_shnum, uint64_t e_shoff,SectionCallback callback)
{

    size_t size = (is64 ? sizeof(MElf64_Shdr) : sizeof(MElf32_Shdr)) * e_shnum;
    // size_t size = e_phentsize * e_phnum
    char* buffer = (char*) read_file(file, size, e_shoff);
    callback(size, buffer, e_shoff);
    MElf_Shdr** headers = (MElf_Shdr** ) malloc(sizeof(MElf_Shdr*) * e_shnum);
    int index = 0; 
    for (; index < e_shnum; index++)
    {
        MElf_Shdr* header =(MElf_Shdr*) malloc(sizeof(MElf_Shdr));
        headers[index] = header;   // Lư
        if (!is64)
        {
            MElf32_Shdr* elf32 = (MElf32_Shdr* ) (buffer + index * sizeof(MElf32_Shdr));
            header->sh_name = elf32->sh_name;
            header->sh_type = elf32->sh_type; 
            header->sh_flags = elf32->sh_flags; 
            header->sh_addr = elf32->sh_addr;
            header->sh_offset = elf32->sh_offset; 
            header->sh_size = elf32->sh_size; 
            header->sh_link = elf32->sh_link; 
            header->sh_info = elf32->sh_info; 
            header->sh_addralign = elf32->sh_addralign;
            header->sh_entsize = elf32->sh_entsize; 
        } else 
        {
            MElf64_Shdr* elf64 = (MElf64_Shdr* ) (buffer + index * sizeof(MElf64_Shdr));
            header->sh_name = elf64->sh_name;
            header->sh_type = elf64->sh_type; 
            header->sh_flags = elf64->sh_flags; 
            header->sh_addr = elf64->sh_addr;
            header->sh_offset = elf64->sh_offset; 
            header->sh_size = elf64->sh_size; 
            header->sh_link = elf64->sh_link; 
            header->sh_info = elf64->sh_info; 
            header->sh_addralign = elf64->sh_addralign;
            header->sh_entsize = elf64->sh_entsize; 
        }
    }
    free(buffer);
    return headers;

}



// duyet mang xong, dua vao mang cac struct de dua len hien thi 

MElf_Shdr_Print** display_section_header(FILE* file, MElf_Ehdr* elf_header, SectionCallback callback)
{
    // hien thi struct nay


    MElf_Shdr** array = get_section_header(file, elf_header->e_ident[EI_CLASS] == ELFCLASS64, elf_header->e_shnum, elf_header->e_shoff, callback);

    MElf_Shdr_Print** ret = (MElf_Shdr_Print**) malloc (elf_header->e_shnum * sizeof(MElf_Shdr_Print*));
    
    char* strtab = get_string_table(file, elf_header, array);
    for (uint16_t i = 0; i < elf_header->e_shnum; i++)
    // for (uint16_t i = 0; i < 10; i++)

    {
        MElf_Shdr_Print *header = (MElf_Shdr_Print*) malloc(sizeof(MElf_Shdr_Print));
        ret[i] = header; 
        // MElf_Phdr_Print *header = (MElf_Phdr_Print* ) ret[i];
  

        // ret[i] =(MElf_Phdr_Print* ) malloc(sizeof(MElf_Phdr_Print)); // ĐẴ từng lỗi ở đây segment fault 
        // cấp phát sai kích thước

        // header = (MElf_Phdr_Print* ) malloc(sizeof(MElf_Phdr_Print)); // ĐẴ từng lỗi ở đây segment fault 

        header->s_name = get_section_name(strtab, array[i]->sh_name);
        header->s_type = get_section_type(array[i]->sh_type); 
        header->s_offset = get_section_offset(array[i]->sh_offset); 
        header->s_addr = get_section_addr(array[i]->sh_addr); 
        header->s_flags = get_section_flags(array[i]->sh_flags ); 
        header->s_size = get_section_size(array[i]->sh_size); 
        header->s_link  = get_section_link(array[i]->sh_link); 
        header->s_info = get_section_info(array[i]->sh_info); 
        header->s_addralign = get_section_addralign(array[i]->sh_addralign);
        header->s_entsize = get_section_entsize(array[i]->sh_entsize);
        

    // header->s_type   = strdup("aaaa");
    // header->s_offset = strdup("aaaa");
    // header->s_vaddr  = strdup("aaaa");
    // header->s_paddr  = strdup("aaaa");
    // header->s_filesz = strdup("aaaa");
    // header->s_memsz  = strdup("aaaa");
    // header->s_flags  = strdup("aaaa");
    // header->s_align  = strdup("aaaa");
      
    }




    return ret;


}