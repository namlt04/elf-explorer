
#include "library.h"


char* get_dynamic_load_tag(const int64_t tag)
{
    char* buffer = (char*) malloc(BUFF_SIZE); 
    buffer[0] = '\0';
    snprintf(buffer, BUFF_SIZE, "0x%016llx", tag);
    return buffer; 
}
char* get_dynamic_load_type(const int64_t tag)
{
    char* buffer = (char*) malloc(BUFF_SIZE); 
    buffer[0] = '\0';
    switch (tag) {
        case DT_NULL:
            snprintf(buffer, BUFF_SIZE, "%s", "NULL");
            break;
        case DT_NEEDED:
            snprintf(buffer, BUFF_SIZE, "%s", "NEEDED");
            break;
        case DT_PLTRELSZ:
            snprintf(buffer, BUFF_SIZE, "%s", "PLTRELSZ");
            break;
        case DT_PLTGOT:
            snprintf(buffer, BUFF_SIZE, "%s", "PLTGOT");
            break;
        case DT_HASH:
            snprintf(buffer, BUFF_SIZE, "%s", "HASH");
            break;
        case DT_STRTAB:
            snprintf(buffer, BUFF_SIZE, "%s", "STRTAB (string table address)");
            break;
        case DT_SYMTAB:
            snprintf(buffer, BUFF_SIZE, "%s", "SYMTAB (symbol table address)");
            break;
        case DT_RELA:
            snprintf(buffer, BUFF_SIZE, "%s", "RELA");
            break;
        case DT_RELASZ:
            snprintf(buffer, BUFF_SIZE, "%s", "RELASZ");
            break;
        case DT_RELAENT:
            snprintf(buffer, BUFF_SIZE, "%s", "RELAENT");
            break;
        case DT_STRSZ:
            snprintf(buffer, BUFF_SIZE, "%s", "STRSZ");
            break;
        case DT_SYMENT:
            snprintf(buffer, BUFF_SIZE, "%s", "SYMENT");
            break;
        case DT_INIT:
            snprintf(buffer, BUFF_SIZE, "%s", "INIT");
            break;
        case DT_FINI:
            snprintf(buffer, BUFF_SIZE, "%s", "FINI");
            break;
        case DT_SONAME:
            snprintf(buffer, BUFF_SIZE, "%s", "SONAME");
            break;
        case DT_RPATH:
            snprintf(buffer, BUFF_SIZE, "%s", "RPATH");
            break;
        case DT_SYMBOLIC:
            snprintf(buffer, BUFF_SIZE, "%s", "SYMBOLIC");
            break;
        case DT_REL:
            snprintf(buffer, BUFF_SIZE, "%s", "REL");
            break;
        case DT_RELSZ:
            snprintf(buffer, BUFF_SIZE, "%s", "RELSZ");
            break;
        case DT_RELENT:
            snprintf(buffer, BUFF_SIZE, "%s", "RELENT");
            break;
        case DT_PLTREL:
            snprintf(buffer, BUFF_SIZE, "%s", "PLTREL");
            break;
        case DT_DEBUG:
            snprintf(buffer, BUFF_SIZE, "%s", "DEBUG");
            break;
        case DT_TEXTREL:
            snprintf(buffer, BUFF_SIZE, "%s", "TEXTREL");
            break;
        case DT_JMPREL:
            snprintf(buffer, BUFF_SIZE, "%s", "JMPREL");
            break;
        case DT_BIND_NOW:
            snprintf(buffer, BUFF_SIZE, "%s", "BIND_NOW");
            break;
        case DT_INIT_ARRAY:
            snprintf(buffer, BUFF_SIZE, "%s", "INIT_ARRAY");
            break;
        case DT_FINI_ARRAY:
            snprintf(buffer, BUFF_SIZE, "%s", "FINI_ARRAY");
            break;
        case DT_INIT_ARRAYSZ:
            snprintf(buffer, BUFF_SIZE, "%s", "INIT_ARRAYSZ");
            break;
        case DT_FINI_ARRAYSZ:
            snprintf(buffer, BUFF_SIZE, "%s", "FINI_ARRAYSZ");
            break;
        case DT_RUNPATH:
            snprintf(buffer, BUFF_SIZE, "%s", "RUNPATH");
            break;
        case DT_FLAGS:
            snprintf(buffer, BUFF_SIZE, "%s", "FLAGS");
            break;
        case DT_ENCODING:
            snprintf(buffer, BUFF_SIZE, "%s", "ENCODING");
            break;
        default:
            snprintf(buffer, BUFF_SIZE, "(0x%llx) <unknow>", tag);
            break;
    }

    return buffer;
} 
char* get_dynamic_load_name(char* strtab, const MElf_Dyn* element)
{
    
    char* buffer = (char*) malloc(BUFF_SIZE); 
    buffer[0] = '\0';
    switch(element->d_tag)
    {
        case DT_NEEDED:
        case DT_SONAME:
        case DT_RPATH:
        case DT_RUNPATH:
            snprintf(buffer, BUFF_SIZE, "%s", strdup(strtab + element->d_un.d_val));
         
            break;

        case DT_STRTAB:
        case DT_SYMTAB:
        case DT_HASH:
        case DT_JMPREL:
        case DT_RELA:
        case DT_REL:
            snprintf(buffer, BUFF_SIZE, "0x%lx", element->d_un.d_ptr);
            break;

        case DT_STRSZ:
        case DT_RELASZ:
        case DT_RELAENT:
        case DT_RELSZ:
        case DT_RELENT:
        case DT_INIT_ARRAYSZ:
        case DT_FINI_ARRAYSZ:
            snprintf(buffer, BUFF_SIZE, "%lu (0x%lx)", element->d_un.d_val, element->d_un.d_val);
            break;

        default:
            snprintf(buffer, BUFF_SIZE, "0x%lx", element->d_un.d_val);     
            break;
    }
  

    return buffer; 

}
MElf_Dyn** get_dynamic_array( FILE* file, MElf_Phdr** phdr, MElf_Ehdr* elf_header,size_t* count)
{
    MElf_Dyn** dyn_array;
	uint16_t index = 0;
    size_t size;
    int is64 = elf_header->e_ident[EI_CLASS] == ELFCLASS64;
	for(; index < elf_header->e_phnum ;index++)
	{
		MElf_Phdr* o_phdr = (MElf_Phdr*) phdr[index];
		if ( o_phdr->p_type == PT_DYNAMIC)
		{
            size_t entsize = is64 ? sizeof(MElf64_Dyn) : sizeof(MElf32_Dyn);
            *count   = o_phdr->p_filesz / entsize;
            dyn_array = (MElf_Dyn**) malloc((*count) * sizeof(MElf_Dyn*));
			char* buffer = (char*) malloc(o_phdr->p_filesz);
			buffer = read_file(file, o_phdr->p_filesz, o_phdr->p_offset);
			if (!is64) 
            {
                MElf32_Dyn* elf32 = (MElf32_Dyn*) buffer; 
                int i = 0; 
                for( ; i < (*count); i++) 
                {
                    MElf_Dyn* item = (MElf_Dyn*) malloc(sizeof(MElf_Dyn)); 
                    dyn_array[i] = item;
                    
                    item->d_tag = elf32[i].d_tag;
                    item->d_un.d_val = elf32[i].d_un.d_val;
                    item->d_un.d_ptr = elf32[i].d_un.d_ptr;
                    
                }

            }
               
            else 
            {
                MElf64_Dyn* elf64 = (MElf64_Dyn*) buffer; 
                int i = 0; 
                for( ; i < (*count); i++) 
                {
                    MElf_Dyn* item = (MElf_Dyn*) malloc(sizeof(MElf_Dyn)); 
                    dyn_array[i] = item;
                    
                    item->d_tag = elf64[i].d_tag;
                    item->d_un.d_val = elf64[i].d_un.d_val;
                    item->d_un.d_ptr = elf64[i].d_un.d_ptr;
                    
                }


            }
        }
    }
    return dyn_array;

}

MElf_Dyn_Print** display_load_library(FILE* file,MElf_Ehdr* elf_header, MElf_Phdr** program_header, size_t* count)
{
    MElf_Dyn** dynamic_array = get_dynamic_array(file, program_header, elf_header, count);


    size_t size;
	uint64_t strtab_vaddr;
    uint64_t index;
    for( index = 0; index < (*count); index++)
	{
        MElf_Dyn* p = dynamic_array[index];

		if (p->d_tag == DT_STRTAB) 
            strtab_vaddr = p->d_un.d_ptr;
        else if( p->d_tag == DT_STRSZ)
			size = p->d_un.d_val; 
	}



    //file_offset = virtual_address - p_vaddr + p_offset
	uint64_t strtab_offset = 0;
    for (int j = 0; j < elf_header->e_phnum; j++) 
    {
        if (program_header[j]->p_type == PT_LOAD) 
        {
            if (strtab_vaddr >= program_header[j]->p_vaddr && strtab_vaddr < program_header[j]->p_vaddr + program_header[j]->p_memsz)
            {
                strtab_offset = strtab_vaddr - program_header[j]->p_vaddr + program_header[j]->p_offset;
                break;
            }
        }
    }
            
    char *strtab = read_file(file, size, strtab_offset);
    
    MElf_Dyn_Print** ret = (MElf_Dyn_Print**) malloc((*count) * sizeof(MElf_Dyn_Print*));
   
    for (index = 0; index < (*count); index++) 
    {
        MElf_Dyn_Print* element =(MElf_Dyn_Print*) malloc(sizeof(MElf_Dyn_Print)); 
        ret[index] = element;
        element->tag = get_dynamic_load_tag(dynamic_array[index]->d_tag);
        element->type = get_dynamic_load_type(dynamic_array[index]->d_tag);
        element->name = get_dynamic_load_name(strtab, dynamic_array[index]);
	}

    return ret;
    // return NULL;

}
