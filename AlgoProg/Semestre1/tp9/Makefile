CC=gcc
CFLAGS=-Wall -std=c11 -c
LDFLAGS=-Wall -std=c11
SOURCES=pile.c test_pile.c afficher_entier.c
OBJECTS=pile.o
EXECUTABLE1=test_pile
EXECUTABLE2=afficher_entier

$(EXECUTABLE1):$(OBJECTS) test_pile.o
	$(CC) $(LDFLAGS) $^ -o $@

$(EXECUTABLE2):$(OBJECTS) afficher_entier.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm *.o $(EXECUTABLE)

depend:
	makedepend $(SOURCES)
# DO NOT DELETE

pile.o: /usr/include/assert.h /usr/include/features.h
pile.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
pile.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
pile.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
pile.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
pile.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
pile.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
pile.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
pile.o: /usr/include/time.h /usr/include/sys/select.h
pile.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
pile.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
pile.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
pile.o: /usr/include/bits/stdlib-float.h pile.h
test_pile.o: /usr/include/stdio.h /usr/include/features.h
test_pile.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
test_pile.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
test_pile.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
test_pile.o: /usr/include/libio.h /usr/include/_G_config.h
test_pile.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
test_pile.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
test_pile.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
test_pile.o: /usr/include/endian.h /usr/include/bits/endian.h
test_pile.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
test_pile.o: /usr/include/sys/types.h /usr/include/time.h
test_pile.o: /usr/include/sys/select.h /usr/include/bits/select.h
test_pile.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
test_pile.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
test_pile.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
test_pile.o: /usr/include/assert.h pile.h
afficher_entier.o: pile.h /usr/include/stdio.h /usr/include/features.h
afficher_entier.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
afficher_entier.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
afficher_entier.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
afficher_entier.o: /usr/include/libio.h /usr/include/_G_config.h
afficher_entier.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
afficher_entier.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
afficher_entier.o: /usr/include/bits/waitflags.h
afficher_entier.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
afficher_entier.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
afficher_entier.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
afficher_entier.o: /usr/include/time.h /usr/include/sys/select.h
afficher_entier.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
afficher_entier.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
afficher_entier.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
afficher_entier.o: /usr/include/bits/stdlib-float.h
