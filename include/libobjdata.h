/*
  libobjdata.h:
  routines in libobjdata.a
*/

#ifndef LIBOBJDATA_H
#define LIBOBJDATA_H

#include "bfd.h"
#include "objsect.h"
#include "objsym.h"

extern void itohex(int number, char *buffer);
extern void getSections(bfd *file, asection *sec, void *obj);
extern void getSymbols(bfd *abfd);
extern void itostring(int num, char *buffer);

#endif
