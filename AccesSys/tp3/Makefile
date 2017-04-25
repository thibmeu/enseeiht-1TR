CC=gcc
CFLAGS=  -std=c99 -Wall -pedantic -g
LD=$(CC)

EXECUTABLES= tri-selection

all: ${EXECUTABLES}

tri-selection: tri-selection.sp.o tab-lecture-ecriture.o tri-selection.sp.main.o 
	$(LD) $^ -o $@ 

clean :  
	rm -f *.o
	rm -f *~

realclean: clean
	   rm -f tri-selection

depend:
	makedepend -Y. *.c

# DO NOT DELETE

tab-lecture-ecriture.o: tab-lecture-ecriture.h
tri-selection.sp.o: tri-selection.sp.h tab-lecture-ecriture.h
tri-selection.sp.main.o: tab-lecture-ecriture.h tri-selection.sp.h
