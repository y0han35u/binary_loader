/* Demonstrate the binary loader from ../inc/loader.cc */

#include <cstdlib>
#include <stdio.h>
#include <stdint.h>
#include <string>
#include <unistd.h>

#include "./inc/loader.h"

int
main(int argc, char *argv[])
{
  int c;
  int sflag = 0;
  size_t i, j;
  Binary bin;
  Section *sec;
  Symbol *sym;
  std::string fname;
  char *svalue = NULL;

  if(argc < 2) {
    printf("Usage: %s <binary>\n", argv[0]);
    return 1;
  }

  optind = 2;
  while((c = getopt(argc, argv, "s:")) != -1) {
    switch(c){
      case 's':
        sflag = 1;
        svalue = optarg;
        break;
      case '?':
        return 1;
      default:
        abort();
    }
  }

  fname.assign(argv[1]);
  if(load_binary(fname, &bin, Binary::BIN_TYPE_AUTO) < 0) {
    return 1;
  }

  printf("loaded binary '%s' %s/%s (%u bits) entry@0x%016jx\n", 
         bin.filename.c_str(), 
         bin.type_str.c_str(), bin.arch_str.c_str(), 
         bin.bits, bin.entry);

  if(sflag){
    printf("HEXDUMP: %s\n", svalue);
    for(i = 0; i < bin.sections.size(); i++) {
      sec = &bin.sections[i];
      if(sec->name != svalue) continue;
      for(j = 1; j <= sec->size; j++) {
        printf("%02x", sec->bytes[j-1]);
        if(!(j%4)){
          printf(" ");
          if(!(j%32)){
            printf("\n");
          }
        }
      }
      printf("\n");
      break;
    }
    goto cleanup;
  }

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
      printf("  %-40s 0x%016jx %s\n", 
             sym->name.c_str(), sym->addr, 
             (sym->type & Symbol::SYM_TYPE_FUNC) ? "FUNC" : "");
    }
  }

cleanup:
  unload_binary(&bin);

  return 0;
}

