# Objdump_NM-Static-Shared-Library

#PURPOSE

This library contains functions that behave similarly to the objdump and nm
unix commands through the implementation of the GNU Binary File Descriptor
Library throughout the code. It was written for educational purposes to
learn the inner workings of these UNIX commands, knowing how to implement
shared and static libraries in C code, as well as understanding the BFD
library.

#INSTRUCTIONS

Simply run 'make' after cloning this repository to unpack the libraries as
well as executables

#FILES

getsections - executable compiled from getsections.c and objsect.c
files. When used against a binary file, the sections of the specified
binary file will be outputted. Example:

[user]$ ./getsections {binary-file}

getsections_dl - executable compiled from getsections_dl.c and objsect.c
files. When used against a binary file, the sections of the specified
binary file will be outputted, as well as a text file that logs the elapsed
time needed to access the sections. Use the flags RTLD_NOW or RTLD_LAZY for
different access time results. Example:

[user]$ ./getsections_dl {binary-file} {flag}

getsyms - executable compiled from getsyms.c and objsym.c files. When used
against a binary file, the symbols, as well as their virtual memory
addressed will be outputted. Example:

[user]$ ./getsyms {binary-file}

getsyms_dl - executable compiled from getsyms.c and objsym.c
files. When used against a binary file, the symbols and their
virtual memory addressed will be outputted, as well as a text file that
logs the elapsed time needed to access the sections. Use the flags RTLD_NOW
or RTLD_LAZY for different access time results. Example:

[user]$ ./getsyms {binary-file} {flag}

objcopy - executable compiled from objcopy.c file. When used agains a
binary file, the binary contents of the .text section of the specified
binary file will be copied into a textt file referred to as
text-output. Example:

[user]$ ./objcopy {binary-file}

lib - contains  directories shared and d static which contain shared and
static libraries.
