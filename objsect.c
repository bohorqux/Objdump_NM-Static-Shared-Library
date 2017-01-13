#include "bfd.h"
#include <string.h>

void itostring(long int number, char *buffer) //converts long integer to string
{ 
  long int tmp = number;
  int len = 0;
  int index = 0;
  long int m;

  while(number != 0)
    {
      number = number/10;
      len++;
    }

  number = tmp;

  while(number != 0)
    {
      m = number % 10;
      buffer[len-index-1] = m + '0';
      number = number/10;
      index++;
    }
  buffer[index] = '\0';
}

void itohex(int number, char *buffer) //converts integer to hexadecimal string
{
  int tmp = number;
  int len = 0;
  int index = 0;
  int m;

  while(number != 0)
    {
      number = number/16;
      len++;
    }
  number = tmp;

  while (number != 0)
    {
      m = number%16;
      switch(m) { //case statements for m > 9
      case 10:
	buffer[len-index-1] = 'a';
	break;
      case 11:
	buffer[len-index-1] = 'b';
	break;
      case 12:
	buffer[len-index-1] = 'c';
	break;
      case 13:
	buffer[len-index-1] = 'd';
	break;
      case 14:
	buffer[len-index-1] = 'e';
	break;
      case 15:
	buffer[len-index-1] = 'f';
	break;

      default:
	buffer[len-index-1] = m + '0';
      }
      number = number/16;
      index++;
    }
  buffer[index] = '\0';
}

void getSections(bfd *file, asection *sec, void *obj) //displays information of single section
{
  char vma[100]; //store all values into char arrays
  char rawsize[100];
  char size[100];
  char position[100];

  write(1, sec->name, strlen(sec->name)); //formatting
  write(1, "\n", strlen("\n"));

  write(1, "\t", strlen("\t"));
  write(1, "VMA:", strlen("VMA:"));
  itohex(sec->vma, vma);
  write(1, vma, strlen(vma));

  write(1, "\t", strlen("\t"));
  write(1, "RAWSIZE:", strlen("RAWSIZE:"));
  itohex(sec->rawsize, rawsize);
  write(1, rawsize, strlen(rawsize));

  write(1, "\t", strlen("\t"));
  write(1, "COOKED:", strlen("COOKED:"));
  itohex(sec->size, size);
  write(1, size, strlen(size));

  write(1, "\t", strlen("\t"));
  write(1, "POSITION:", strlen("POSITION:"));
  itohex(sec->filepos, position);
  write(1, position, strlen(position));

  write(1, "\n", strlen("\n"));
}
