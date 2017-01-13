#include "bfd.h"
#include <libobjdata.h>
#include <string.h>

int main(int argc, char *argv[])
{
  bfd_init(); //initialization

  bfd *file = bfd_openr(argv[1], "elf64-x86-64");

  if (file == NULL) //error checking
    {
      bfd_perror(bfd_errmsg(bfd_get_error()));
      return;
     }

     if (!bfd_check_format(file, bfd_object))
    {
      bfd_perror(bfd_errmsg(bfd_get_error()));
      return;
     }

   getSymbols(file); //display symbol contents of bfd file
    
   return 0;

}
