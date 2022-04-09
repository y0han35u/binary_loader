/* Demonstrate the binary loader from ../inc/loader.cc */

#include <stdio.h>
#include <stdint.h>
#include <string>

#include "loader.h"

std::string &check_type(std::string&, Symbol::SymbolType);
std::string &check_bind(std::string&, Symbol::SymbolBind);

int
main(int argc, char *argv[])
{
  size_t i;
  Binary bin;
  Section *sec;
  Symbol *sym;
  std::string fname;
  std::string tname;
  std::string bname;

  if(argc < 2) {
    printf("Usage: %s <binary>\n", argv[0]);
    return 1;
  }

  fname.assign(argv[1]);
  if(load_binary(fname, &bin, Binary::BIN_TYPE_AUTO) < 0) {
    return 1;
  }

  printf("loaded binary '%s' %s/%s (%u bits) entry@0x%016jx\n", 
         bin.filename.c_str(), 
         bin.type_str.c_str(), bin.arch_str.c_str(), 
         bin.bits, bin.entry);

  for(i = 0; i < bin.sections.size(); i++) {
    sec = &bin.sections[i];
    printf("  0x%016jx %-8ju %-20s %s\n", 
           sec->vma, sec->size, sec->name.c_str(), 
           sec->type == Section::SEC_TYPE_CODE ? "CODE" : "DATA");
  }

  if(bin.symbols.size() > 0) {
    printf("scanned symbol tables\n");
    for(i = 0; i < bin.symbols.size(); i++) {
      sym = &bin.symbols[i];
      printf("  %-40s 0x%016jx %s %s\n", 
             sym->name.c_str(), sym->addr, check_type(tname, sym->type).c_str(), check_bind(bname, sym->bind).c_str());
    }
  }

  unload_binary(&bin);

  return 0;
}

std::string
&check_type(std::string &type_name, Symbol::SymbolType stype) {
  switch (stype) {
    case Symbol::SYM_TYPE_FUNC:
      type_name = "FUNC";
      break;

    case Symbol::SYM_TYPE_DATA:
      type_name = "DATA";
      break;

    default:
      type_name = "UKN";
      break;
  }
  return type_name;
}

std::string
&check_bind(std::string &bind_name, Symbol::SymbolBind btype) {
  switch (btype) {
    case Symbol::SYM_BIND_GLOBAL:
      bind_name = "GLOBAL";
      break;

    case Symbol::SYM_BIND_LOCAL:
      bind_name = "LOCAL";
      break;

    case Symbol::SYM_BIND_WEAK:
      bind_name = "WEAK";
      break;

    default:
      bind_name = "UKN";
      break;
  }
  return bind_name;
}











