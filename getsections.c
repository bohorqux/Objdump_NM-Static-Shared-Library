#include <libobjdata.h>
#include <string.h>

int main(int argc, char *argv[])
{

  bfd_init(); //initialization

  bfd *file = bfd_openr(argv[1], "elf64-x86-64");

  if (file == NULL) //error checking
    {
      bfd_perror(NULL);
      return 0;
     }

     if (!bfd_check_format(file, bfd_object))
    {
      bfd_perror(NULL);
      return 0;
     }

  bfd_map_over_sections(file, getSections, NULL); //function for printing sections

  bfd_close(file);

  return 0;
}
