#include "bfd.h"
#include <string.h>
#include <stdlib.h>

void getSymbols(bfd *abfd)
{

  long storage; //initialize variable for symbol iteration
  asymbol **table;
  long symbols;
  long i;

  table = malloc(bfd_get_symtab_upper_bound(abfd)); //allocate necessary storage for symbol table
  symbols = bfd_canonicalize_symtab(abfd, table);  //get number of symbols in bfd abfd for iteration purposes

    for (i=0; i < symbols; i++)
      {
	char vma[100];
	itohex(table[i]->section->vma + table[i]->value, vma);

	write(1, table[i]->name, strlen(table[i]->name));
	write(1, "\t", strlen("\t"));
	write(1, "VMA: ", strlen("VMA: "));
	write(1, vma, strlen(vma));
	write(1, "\n", strlen("\n"));
      }
}

	
