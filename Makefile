
all: getsections getsyms getsections_dl getsyms_dl objcopy

getsections: getsections.c libobjdata.a
	gcc -I./include -L./lib/static -o getsections getsections.c -lobjdata -lbfd

getsyms: getsyms.c libobjdata.a
	gcc -I./include -L./lib/static -o getsyms getsyms.c -lobjdata -lbfd

objcopy: objcopy.c libobjdata.a
	gcc -I./include -L./lib/static -o objcopy objcopy.c -lobjdata -lbfd

getsections_dl: getsections_dl.c libobjdata.so
	gcc -I./include -L./lib/static -o getsections_dl getsections_dl.c -lobjdata -lbfd

getsyms_dl: getsyms_dl.c libobjdata.so
	gcc -I./include -L./lib/static -o getsyms_dl getsyms_dl.c -lobjdata -lbfd

libobjdata.a: objsym.o objsect.o objcopy.o
	ar rs libobjdata.a objsym.o objsect.o objcopy.o
	mkdir -p lib/static
	mv libobjdata.a lib/static

libobjdata.so: objsym_dl.o objsect_dl.o 
	gcc -shared -o libobjdata.so objsym_dl.o objsect_dl.o
	mkdir -p lib/shared
	mv libobjdata.so lib/shared

objsect.o: objsect.c
	gcc -c -o objsect.o objsect.c

objsect_dl.o: objsect.c
	gcc -c -fPIC -o objsect_dl.o objsect.c

objsym.o: objsym.c
	gcc -c -o objsym.o objsym.c

objsym_dl.o: objsym.c
	gcc -c -fPIC -o objsym_dl.o objsym.c
clean:
	rm -rf ./lib objsym.o objsect.o objsym_dl.o objsect_dl.o objcopy.o getsections getsyms getsections_dl getsyms_dl objcopy stats libobjdata.a libobjdata.so text-output *~

