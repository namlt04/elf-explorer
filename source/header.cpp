
#include "header.h"

#include "utils.h"




char* get_flags(const uint32_t flags)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "0x%x", flags); 
  return buffer;
}

char* get_start_of_program_header(const uint64_t phoff)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%llu (bytes into file)", phoff); 
  return buffer;
}
char* get_size_of_this_header(const uint16_t ehsize)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%d (bytes)", ehsize); 
  return buffer;
}
char* get_size_of_program_header(const uint16_t phentsize)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%d (bytes)", phentsize); 
  return buffer;
}
char* get_size_of_section_header(const uint16_t shentsize)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%d (bytes)", shentsize); 
  return buffer;
}
char* get_number_of_section_header(const uint64_t shnum)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%llu", shnum); 
  return buffer;
}

char* get_section_header_string_table_index_header(const uint64_t shstrndx)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%llu", shstrndx); 
  return buffer;
}



char* get_start_of_section_header(const uint64_t shoff)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%llu (bytes into file)", shoff); 
  return buffer;


}
char* get_entrypoint_address(const uint32_t entrypoint)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "0x%X", entrypoint); 
  return buffer;
  
}
char* get_type(const uint16_t type)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%x", type); 
  return buffer;
  

}
char* get_version_num(const uint32_t version)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%x", version); 
  return buffer;
}
char* get_abi_version(const uint8_t abi_version)
{
  char* buffer= (char*) malloc(256);
  buffer[0] = '\0';
  snprintf(buffer, BUFF_SIZE, "%x", abi_version); 
  return buffer;
}
char* get_magic(const unsigned char* e_ident)
{
  
  size_t buff_size = EI_NIDENT * 3 + 1; // + 1 \0 là kí tự NULL 
  char* buffer = (char* ) malloc(buff_size);
  buffer[0] = '\0'; // Đảm bảo buffer không chứa kí tự rác
  int i = 0;
  for(; i < EI_NIDENT; i++)
  {
      char buf[4]; 
      snprintf(buf, sizeof(buf), " %02x", e_ident[i]);
      strcat(buffer, buf);
  }
  return buffer;

}
char* get_class(const unsigned char* e_ident)
{
    switch(e_ident[EI_CLASS])
    {
        case ELFCLASSNONE : return "None"; 
        case ELFCLASS32   : return "32 bit";
        case ELFCLASS64   : return "64 bit"; 
        default: 
            return "<unknow>";
    }
}

char* get_data(const unsigned char* e_ident)
{
    switch(e_ident[EI_DATA])
    {
        case ELFDATANONE : return "None"; 
        case ELFDATA2LSB: return "2's complement, little endian";
        case ELFDATA2MSB: return "2's complement, big endian";
        default: 
            return "<unknow>";
    }
}
char* get_version(const unsigned char* e_ident)
{
    switch(e_ident[EI_VERSION])
    {
        case EV_NONE : return "0"; 
        case EV_CURRENT : return "1 (Current)";
        default :
            return "<unknow>";
    }
}
char *get_osabi_name(unsigned char* osabi) {
  static char buf[32];

  switch (osabi[EI_OSABI]) {
  case ELFOSABI_NONE:     return "UNIX - System V";
  case ELFOSABI_HPUX:     return "UNIX - HP-UX";
  case ELFOSABI_NETBSD:   return "UNIX - NetBSD";
  case ELFOSABI_GNU:      return "UNIX - GNU";
  case ELFOSABI_SOLARIS:  return "UNIX - Solaris";
  case ELFOSABI_AIX:      return "UNIX - AIX";
  case ELFOSABI_IRIX:     return "UNIX - IRIX";
  case ELFOSABI_FREEBSD:  return "UNIX - FreeBSD";
  case ELFOSABI_TRU64:    return "UNIX - TRU64";
  case ELFOSABI_MODESTO:  return "Novell - Modesto";
  case ELFOSABI_OPENBSD:  return "UNIX - OpenBSD";
  case ELFOSABI_OPENVMS:  return "VMS - OpenVMS";
  case ELFOSABI_NSK:      return "HP - Non-Stop Kernel";
  case ELFOSABI_AROS:     return "AROS";
  case ELFOSABI_FENIXOS:  return "FenixOS";
  case ELFOSABI_CLOUDABI: return "Nuxi - CloudABI";
  case ELFOSABI_OPENVOS:  return "Stratus Technologies OpenVOS";
  default:
    if (osabi[EI_OSABI] >= 64) {
      // TODO: machine dependent osabi
      return "";
    } else {
      snprintf(buf, sizeof(buf), "<unknown: %x>", osabi[EI_OSABI]);
    }
  }

  return buf;
}

char *get_file_type(const uint16_t e_type) {
  static char buf[32];

  switch (e_type) {
  case ET_NONE: return "NONE (None)";
  case ET_REL:  return "REL (Relocatable file)";
  case ET_EXEC: return "EXEC (Executable file)";
  case ET_DYN:  return "DYN (Shared object file)";
  case ET_CORE: return "CORE (Core file)";
  default:
    if (e_type >= ET_LOOS && e_type <= ET_HIOS) {
      snprintf(buf, sizeof(buf), "OS Specific: (%x)", e_type);
    } else if (e_type >= ET_LOPROC && e_type <= ET_HIPROC) {
      snprintf(buf, sizeof(buf), "Processor Specific: (%x)", e_type);
    } else {
      snprintf(buf, sizeof(buf), "<unknown>: (%x)", e_type);
    }
  }

  return buf;
}

char* get_machine_name(uint16_t e_machine) {

    switch (e_machine) {
        case EM_NONE:           return "None";
        case EM_M32:            return "AT&T WE 32100";
        case EM_SPARC:          return "SUN SPARC";
        case EM_386:            return "Intel 80386";
        case EM_68K:            return "Motorola m68k family";
        case EM_88K:            return "Motorola m88k family";
        case EM_IAMCU:          return "Intel MCU";
        case EM_860:            return "Intel 80860";
        case EM_MIPS:           return "MIPS R3000 big-endian";
        case EM_S370:           return "IBM System/370";
        case EM_MIPS_RS3_LE:    return "MIPS R3000 little-endian";
        case EM_PARISC:         return "HPPA";
        case EM_VPP500:         return "Fujitsu VPP500";
        case EM_SPARC32PLUS:    return "Sun SPARC v8+";
        case EM_960:            return "Intel 80960";
        case EM_PPC:            return "PowerPC";
        case EM_PPC64:          return "PowerPC 64-bit";
        case EM_S390:           return "IBM S390";
        case EM_SPU:            return "IBM SPU/SPC";
        case EM_V800:           return "NEC V800";
        case EM_FR20:           return "Fujitsu FR20";
        case EM_RH32:           return "TRW RH-32";
        case EM_RCE:            return "Motorola RCE";
        case EM_ARM:            return "ARM";
        case EM_FAKE_ALPHA:     return "Digital Alpha";
        case EM_SH:             return "Hitachi SH";
        case EM_SPARCV9:        return "SPARC v9 64-bit";
        case EM_TRICORE:        return "Siemens Tricore";
        case EM_ARC:            return "Argonaut RISC Core";
        case EM_H8_300:         return "Hitachi H8/300";
        case EM_H8_300H:        return "Hitachi H8/300H";
        case EM_H8S:            return "Hitachi H8S";
        case EM_H8_500:         return "Hitachi H8/500";
        case EM_IA_64:          return "Intel Itanium (IA-64)";
        case EM_MIPS_X:         return "Stanford MIPS-X";
        case EM_COLDFIRE:       return "Motorola ColdFire";
        case EM_68HC12:         return "Motorola M68HC12";
        case EM_MMA:            return "Fujitsu MMA Multimedia Accelerator";
        case EM_PCP:            return "Siemens PCP";
        case EM_NCPU:           return "Sony nCPU embedded RISC";
        case EM_NDR1:           return "Denso NDR1";
        case EM_STARCORE:       return "Motorola Star*Core DSP";
        case EM_ME16:           return "Toyota ME16";
        case EM_ST100:          return "STMicro ST100";
        case EM_TINYJ:          return "Advanced Logic TinyJ";
        case EM_X86_64:         return "AMD x86-64";
        case EM_PDSP:           return "Sony DSP";
        case EM_PDP10:          return "Digital PDP-10";
        case EM_PDP11:          return "Digital PDP-11";
        case EM_FX66:           return "Siemens FX66";
        case EM_ST9PLUS:        return "STMicro ST9+";
        case EM_ST7:            return "STMicro ST7";
        case EM_68HC16:         return "Motorola MC68HC16";
        case EM_68HC11:         return "Motorola MC68HC11";
        case EM_68HC08:         return "Motorola MC68HC08";
        case EM_68HC05:         return "Motorola MC68HC05";
        case EM_SVX:            return "SGI SVx";
        case EM_ST19:           return "STMicro ST19";
        case EM_VAX:            return "Digital VAX";
        case EM_CRIS:           return "Axis CRIS";
        case EM_JAVELIN:        return "Infineon Javelin";
        case EM_FIREPATH:       return "Element 14 Firepath";
        case EM_ZSP:            return "LSI Logic ZSP";
        case EM_MMIX:           return "Donald Knuth's MMIX";
        case EM_HUANY:          return "Harvard HUANY";
        case EM_PRISM:          return "SiTera Prism";
        case EM_AVR:            return "Atmel AVR";
        case EM_FR30:           return "Fujitsu FR30";
        case EM_D10V:           return "Mitsubishi D10V";
        case EM_D30V:           return "Mitsubishi D30V";
        case EM_V850:           return "NEC V850";
        case EM_M32R:           return "Mitsubishi M32R";
        case EM_MN10300:        return "Matsushita MN10300";
        case EM_MN10200:        return "Matsushita MN10200";
        case EM_PJ:             return "picoJava";
        case EM_OPENRISC:       return "OpenRISC";
        case EM_ARC_COMPACT:    return "ARC Compact";
        case EM_XTENSA:         return "Tensilica Xtensa";
        case EM_VIDEOCORE:      return "Alphamosaic VideoCore";
        case EM_TMM_GPP:        return "Thompson Multimedia GPP";
        case EM_NS32K:          return "National Semi 32000";
        case EM_TPC:            return "Tenor TPC";
        case EM_SNP1K:          return "Trebia SNP 1000";
        case EM_ST200:          return "STMicro ST200";
        case EM_IP2K:           return "Ubicom IP2K";
        case EM_MAX:            return "MAX processor";
        case EM_CR:             return "National Semi CR";
        case EM_F2MC16:         return "Fujitsu F2MC16";
        case EM_MSP430:         return "TI MSP430";
        case EM_BLACKFIN:       return "Analog Devices Blackfin";
        case EM_SE_C33:         return "Seiko Epson S1C33";
        case EM_SEP:            return "Sharp embedded processor";
        case EM_ARCA:           return "Arca RISC";
        case EM_UNICORE:        return "PKU-Unity UniCore";
        case EM_EXCESS:         return "eXcess";
        case EM_DXP:            return "Icera Deep Execution Processor";
        case EM_ALTERA_NIOS2:   return "Altera Nios II";
        case EM_CRX:            return "National Semi CRX";
        case EM_XGATE:          return "Motorola XGATE";
        case EM_C166:           return "Infineon C166";
        case EM_M16C:           return "Renesas M16C";
        case EM_DSPIC30F:       return "Microchip dsPIC30F";
        case EM_CE:             return "Freescale Communication Engine";
        case EM_M32C:           return "Renesas M32C";
        case EM_TSK3000:        return "Altium TSK3000";
        case EM_RS08:           return "Freescale RS08";
        case EM_SHARC:          return "Analog Devices SHARC";
        case EM_ECOG2:          return "Cyan eCOG2";
        case EM_SCORE7:         return "Sunplus S+core7";
        case EM_DSP24:          return "NJR DSP24";
        case EM_VIDEOCORE3:     return "Broadcom VideoCore III";
        case EM_LATTICEMICO32:  return "Lattice Mico32";
        case EM_SE_C17:         return "Seiko Epson C17";
        case EM_TI_C6000:       return "TI C6000 DSP";
        case EM_TI_C2000:       return "TI C2000 DSP";
        case EM_TI_C5500:       return "TI C55x DSP";
        case EM_TI_ARP32:       return "TI ARP32";
        case EM_TI_PRU:         return "TI PRU";
        case EM_MMDSP_PLUS:     return "STMicro MMDSP+";
        case EM_CYPRESS_M8C:    return "Cypress M8C";
        case EM_R32C:           return "Renesas R32C";
        case EM_TRIMEDIA:       return "NXP TriMedia";
        case EM_QDSP6:          return "Qualcomm DSP6";
        case EM_8051:           return "Intel 8051";
        case EM_STXP7X:         return "STMicro STxP7x";
        case EM_NDS32:          return "Andes NDS32";
        case EM_ECOG1X:         return "Cyan eCOG1X";
        case EM_MAXQ30:         return "Dallas MAXQ30";
        case EM_XIMO16:         return "NJR Ximo16";
        case EM_MANIK:          return "M2000 Manik";
        case EM_CRAYNV2:        return "Cray NV2";
        case EM_RX:             return "Renesas RX";
        case EM_METAG:          return "Imagination META";
        case EM_MCST_ELBRUS:    return "MCST Elbrus";
        case EM_ECOG16:         return "Cyan eCOG16";
        case EM_CR16:           return "National Semi CR16";
        case EM_ETPU:           return "Freescale ETPU";
        case EM_SLE9X:          return "Infineon SLE9X";
        case EM_L10M:           return "Intel L10M";
        case EM_K10M:           return "Intel K10M";
        case EM_AARCH64:        return "ARM AArch64";
        case EM_AVR32:          return "Atmel AVR32";
        case EM_STM8:           return "STMicro STM8";
        case EM_TILE64:         return "Tilera TILE64";
        case EM_TILEPRO:        return "Tilera TILEPro";
        case EM_MICROBLAZE:     return "Xilinx MicroBlaze";
        case EM_CUDA:           return "NVIDIA CUDA";
        case EM_TILEGX:         return "Tilera TILE-Gx";
        case EM_CLOUDSHIELD:    return "CloudShield";
        case EM_COREA_1ST:      return "KIPO-KAIST Core-A 1st gen";
        case EM_COREA_2ND:      return "KIPO-KAIST Core-A 2nd gen";
        case EM_ARC_COMPACT2:   return "ARC Compact2";
        case EM_OPEN8:          return "Open8";
        case EM_RL78:           return "Renesas RL78";
        case EM_VIDEOCORE5:     return "Broadcom VideoCore V";
        case EM_78KOR:          return "Renesas 78KOR";
        case EM_56800EX:        return "Freescale 56800EX DSC";
        case EM_BA1:            return "Beyond BA1";
        case EM_BA2:            return "Beyond BA2";
        case EM_XCORE:          return "XMOS xCORE";
        case EM_MCHP_PIC:       return "Microchip PIC";
        case EM_KM32:           return "KM211 KM32";
        case EM_KMX32:          return "KM211 KMX32";
        case EM_EMX16:          return "KM211 EMX16";
        case EM_EMX8:           return "KM211 EMX8";
        case EM_KVARC:          return "KM211 KVARC";
        case EM_CDP:            return "Paneve CDP";
        case EM_COGE:           return "Cognitive COGE";
        case EM_COOL:           return "Bluechip CoolEngine";
        case EM_NORC:           return "Nanoradio NORC";
        case EM_CSR_KALIMBA:    return "CSR Kalimba";
        case EM_Z80:            return "Zilog Z80";
        case EM_VISIUM:         return "CDS VISIUMcore";
        case EM_FT32:           return "FTDI FT32";
        case EM_MOXIE:          return "Moxie";
        case EM_AMDGPU:         return "AMD GPU";
        case EM_RISCV:          return "RISC-V";
        case EM_BPF:            return "Linux BPF";
        case EM_CSKY:           return "C-SKY";

        case EM_ALPHA:          return "Alpha"; // synonym
        default:                return "Unknown";
    }
}




// H
MElf_Ehdr *read_header_file(FILE* file, HeaderCallback callback)
{
    MElf_Ehdr* header = (MElf_Ehdr* ) malloc(sizeof(MElf_Ehdr));

    char* buffer = (char*) read_file(file, sizeof(MElf64_Ehdr), 0) ;
    // create hex view
    callback((size_t) sizeof(MElf64_Ehdr), buffer);

    int isElfFile = check_magic_number(buffer);
    int index; 
    for(index = 0; index < EI_NIDENT; index++)
    {
        header->e_ident[index] = buffer[index]; 
    }
  
    if (!isElfFile)
    {
        if ( buffer[EI_CLASS] == ELFCLASS32) 
        {
            MElf32_Ehdr* elf32 = (MElf32_Ehdr*) buffer;
            header->e_type = elf32->e_type;
            header->e_machine = elf32->e_machine; 
            header->e_version = elf32->e_version; 
            header->e_entry = elf32->e_entry; 
            header->e_phoff = elf32->e_phoff;
            header->e_shoff = elf32->e_shoff; 
            header->e_flags = elf32->e_flags; 
            header->e_ehsize = elf32->e_ehsize; 
            header->e_phentsize = elf32->e_phentsize; 
            header->e_phnum = elf32->e_phnum; 
            header->e_shentsize = elf32->e_shentsize;
            header->e_shnum = elf32->e_shnum; 
            header->e_shstrndx = elf32->e_shstrndx;
        } else 
        {
            MElf64_Ehdr* elf64 = (MElf64_Ehdr*) buffer;
            header->e_type = elf64->e_type;
            header->e_machine = elf64->e_machine; 
            header->e_version = elf64->e_version; 
            header->e_entry = elf64->e_entry; 
            header->e_phoff = elf64->e_phoff;
            header->e_shoff = elf64->e_shoff; 
            header->e_flags = elf64->e_flags; 
            header->e_ehsize = elf64->e_ehsize; 
            header->e_phentsize = elf64->e_phentsize; 
            header->e_phnum = elf64->e_phnum; 
            header->e_shentsize = elf64->e_shentsize;
            header->e_shnum = elf64->e_shnum; 
            header->e_shstrndx = elf64->e_shstrndx;

        } 
    } else 
 
        return NULL;

    free(buffer);
    return header;
    
}
char* get_number_of_program_header(const uint16_t e_phnum)
{
  char* buf = (char*) malloc(256); 

  buf[0] = '\0'; 
  snprintf(buf, 256, "%d", e_phnum); 

  return buf;

}

char* get_section_header_string_table_index()
{
  return "test";
}
MEhdr_Print* display_elf_header(MElf_Ehdr* header)
{

    MEhdr_Print* ret = (MEhdr_Print*)malloc(sizeof(MEhdr_Print));


    ret->s_magic = get_magic(header->e_ident);
    ret->s_class = get_class(header->e_ident); 
    ret->s_data = get_data(header->e_ident); 

    // ret->s_version = get_elf_version(header->e_ident);
    ret->s_version = "test";

    ret->s_osabi = get_osabi_name(header->e_ident);
    ret->s_abiversion = get_abi_version(header->e_ident[EI_ABIVERSION]);
    ret->s_type = get_file_type(header->e_type);
    ret->s_machine = get_machine_name(header->e_machine); 
    ret->s_version0 = get_version(header->e_ident);


    ret->s_entrypoint_address = get_entrypoint_address(header->e_entry);
    ret->s_start_of_program_header = get_start_of_program_header(header->e_phoff);
    ret->s_start_of_section_header = get_start_of_section_header(header->e_shoff);

    ret->s_flags = get_flags(header->e_flags);
    ret->s_size_of_this_header = get_size_of_this_header(header->e_ehsize);
    ret->s_size_of_program_header = get_size_of_program_header(header->e_phentsize);
    ret->s_number_of_program_header  = get_number_of_program_header(header->e_phnum); 

    ret->s_size_of_section_header = get_size_of_section_header(header->e_shentsize); 
    ret->s_number_of_section_header = get_number_of_section_header(header->e_shnum); 
    ret->s_section_header_string_table_index = get_section_header_string_table_index();
    return ret;
}