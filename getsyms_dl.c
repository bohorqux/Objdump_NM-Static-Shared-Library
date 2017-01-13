#include <libobjdata.h>
#include <string.h>
#include <fcntl.h>
#include <dlfcn.h>
#define rdtsc(x)   __asm__ __volatile__("rdtsc \n\t" : "=A" (*(x)))
unsigned long long start, finish;

int main(int argc, char *argv[])
{

  bfd_init(); //initialization

  bfd *file = bfd_openr(argv[1], "elf64-x86-64");

   if (file == NULL)
    {
      bfd_perror(NULL);
      return 0;
     }

     if (!bfd_check_format(file, bfd_object))
    {
      bfd_perror(NULL);
      return 0;
     }

     int flag; //initialize integer values
  int i;
  int fd;

  void *lib_handle; //initialize lib_handle for output, lib for iteration, and fn as a function pointer
  void *lib;
  void  (*fn)(bfd *);

  mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH; //setting permissions
  int average_cost = 0;
  char avg[100];

  char *star = "******************************************************************************************"; //formatting purposes; stars signify use of getsyms_dl

  if (strcmp(argv[2], "RTLD_LAZY") == 0) { flag = RTLD_LAZY; } //setting flag values
  else if (strcmp(argv[2], "RTLD_NOW") == 0) {flag = RTLD_NOW; }
 
  fd = open("stats", O_CREAT | O_WRONLY | O_APPEND, mode);

  write(fd, "FLAG: ", strlen("FLAG: "));
  write(fd, argv[2], strlen(argv[2]));

  write(fd, "\t", strlen("\t"));
  write(fd, "BINARY: ", strlen("BINARY: "));
  write(fd, argv[1], strlen(argv[1]));
  write(fd, "\n", strlen("\n"));
  write(fd, star, strlen(star));
  write(fd, "\n", strlen("\n"));

  for (i = 0; i < 50; i++)
    {
      rdtsc(&start);
      lib = dlopen("./lib/shared/libobjdata.so",  flag);
      rdtsc(&finish); //obtaining finish and start times

      char start_T[100]; //initialze arrays for outputting to text
      char finish_T[100];
      char elapsed[100];
      char cost[100];

      unsigned long int e = finish-start; //formatting
      unsigned long int t = e/26000;

      itostring(start, start_T);
      itostring(finish, finish_T);
      itostring(e, elapsed);
      itostring(t, cost);

      write(fd, "Start Time:", strlen("Start Time:"));
      write(fd, start_T, strlen(start_T));
      write(fd, "\t", strlen("\t"));

      write(fd, "End Time:", strlen("End Time:"));
      write(fd, finish_T, strlen(finish_T));
      write(fd, "\t", strlen("\t"));

      write(fd, "Elapsed Time:", strlen("Elapsed Time:"));
      write(fd, elapsed, strlen(elapsed));
      write(fd, "\t", strlen("\t"));

      write(fd, "Cost:", strlen("Cost:"));
      write(fd, cost, strlen(cost));

      write(fd, "\n", strlen("\n"));
      
      average_cost += t; //gets sum total of cost values
      dlclose(lib);
    }

  average_cost /= 50; //obtain approximate average cost value    
  itostring(average_cost, avg);

  write(fd, "\n", strlen("\n"));
  write(fd, "Average Cost: ", strlen("Average Cost: "));
  write(fd, avg, strlen(avg));
  write(fd, "\n", strlen("\n"));

  write(fd, "\n", strlen("\n"));
  close(fd);

  lib_handle = dlopen("./lib/shared/libobjdata.so", flag);
  fn = dlsym(lib_handle, "getSymbols"); //point fn to getSymbols function in libobjdata.so

  (*fn)(file);
  
  return 0;
}
 
