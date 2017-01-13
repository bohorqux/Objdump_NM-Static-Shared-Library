#include "bfd.h"
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
  bfd_init();

  bfd *file = bfd_openr(argv[1], "elf64-x86-64");

  if(file == NULL)
    {
      bfd_perror(NULL);
      return 0;
    }
  if(!bfd_check_format(file, bfd_object))
    {
      bfd_perror(NULL);
      return 0;
    }

  asection *sec;
  sec = bfd_get_section_by_name(file, ".text"); //obtain text section
  int fd;
  char buffer[sec->size]; //set buffer size to size of section

  fd = open("text-output", O_WRONLY | O_CREAT | O_APPEND, 0666);
  bfd_get_section_contents(file, sec, buffer, sec->moving_line_filepos, sec->size);
  write(fd, buffer, sec->size);

  bfd_close(file);
  close(fd);
}

