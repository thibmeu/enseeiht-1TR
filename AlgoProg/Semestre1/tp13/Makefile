CC=gcc
CFLAGS= -std=c99 -g -Wall -pedantic
LDFLAGS= -std=c99 -pg -g -Wall -pedantic

# -ansi 
#
GENERES =	\
	lca.h	\
	th.h	\
	exemple-lca.c	\
	exemple-th.c	\
	interpreteur-lca.c	\
	interpreteur-th.c	\
	tests-lca-commun.c	\
	tests-th-commun.c	\
	performance-lca-commun.c	\
	performance-th-commun.c		\


EXE =	\
	exemple-lca-iterative	\
	exemple-lca-recursive	\
	exemple-th	\
	interpreteur-lca-iterative	\
	interpreteur-lca-recursive	\
	interpreteur-th	\
	tests-lca-iterative	\
	tests-lca-recursive	\
	tests-th	\

PERFORMANCE = \
	performance-lca-iterative	\
	performance-lca-recursive	\
	performance-th	\

TLCA = lca-iterative
#TLCA = lca-recursive
	


all:: ${GENERES} $(EXE)

performance:: 
	make force
	mkdir -p performance
	make ${PERFORMANCE}

interpreteur-lca-iterative: interpreteur-lca.o lca-iterative.o lca-solo.o types.o
	$(CC) $(LDFLAGS) -o $@ $^

interpreteur-lca-recursive: interpreteur-lca.o lca-recursive.o lca-solo.o types.o
	$(CC) $(LDFLAGS) -o $@ $^

interpreteur-th: interpreteur-th.o $(TLCA).o th.o lca-solo.o fonctions-hachage.o types.o
	$(CC) $(LDFLAGS) -o $@ $^

exemple-lca-iterative: exemple-lca.o lca-iterative.o lca-solo.o types.o
	$(CC) $(LDFLAGS) -o $@ $^

exemple-lca-recursive: exemple-lca.o lca-recursive.o lca-solo.o types.o
	$(CC) $(LDFLAGS) -o $@ $^

exemple-th: exemple-th.o th.o fonctions-hachage.o $(TLCA).o lca-solo.o types.o
	$(CC) $(LDFLAGS) -o $@ $^

tests-lca-iterative: tests-lca.o types.o seatest.o lca-iterative.o lca-solo.o
	$(CC) $(LDFLAGS) -o $@ $^
	
tests-lca-recursive: tests-lca.o types.o seatest.o lca-recursive.o lca-solo.o
	$(CC) $(LDFLAGS) -o $@ $^

tests-th: tests-th.o types.o seatest.o th.o $(TLCA).o fonctions-hachage.o lca-solo.o
	$(CC) $(LDFLAGS) -o $@ $^

performance-lca-iterative: types.o seatest.o lca-iterative.o lca-solo.o
	for NB_ELEMENTS in 1 100 10000; do \
		echo Generating performance for $$NB_ELEMENTS with lca-iterative;	\
		$(CC) $(CFLAGS) -DNB_ELEMENTS=$$NB_ELEMENTS -c -o performance-lca.o performance-lca.c;	\
		$(CC) $(LDFLAGS) -o performance/$@-$$NB_ELEMENTS performance-lca.o $^; \
		performance/$@-$$NB_ELEMENTS;	\
		gprof performance/$@-$$NB_ELEMENTS > performance/$@-$$NB_ELEMENTS.txt;	\
		rm performance/$@-$$NB_ELEMENTS;	\
	done

performance-lca-recursive: types.o seatest.o lca-recursive.o lca-solo.o
	for NB_ELEMENTS in 1 100 10000; do \
		echo Generating performance for $$NB_ELEMENTS with lca-recursive;	\
		$(CC) $(CFLAGS) -DNB_ELEMENTS=$$NB_ELEMENTS -c -o performance-lca.o performance-lca.c;	\
		$(CC) $(LDFLAGS) -o performance/$@-$$NB_ELEMENTS performance-lca.o $^; \
		performance/$@-$$NB_ELEMENTS;	\
		gprof performance/$@-$$NB_ELEMENTS > performance/$@-$$NB_ELEMENTS.txt;	\
		rm performance/$@-$$NB_ELEMENTS;	\
	done

SIZES = 1 100 1000
HASHS = taille initiale somme java
performance-th: types.o seatest.o th.o $(TLCA).o fonctions-hachage.o lca-solo.o
	for NB_ELEMENTS in 1 100 10000; do \
		for SIZE in $(SIZES); do \
			for HASH in $(HASHS); do \
				echo Generating performance for $$NB_ELEMENTS with th of size $$SIZE and hash_function $$HASH;	\
				$(CC) $(CFLAGS) -DNB_ELEMENTS=$$NB_ELEMENTS -DSIZE=$$SIZE -DHASH=$$HASH -c -o $@.o $@.c;	\
				$(CC) $(LDFLAGS) -o performance/$@-$$SIZE-$$HASH-$$NB_ELEMENTS $@.o $^; \
				performance/$@-$$SIZE-$$HASH-$$NB_ELEMENTS;	\
				gprof performance/$@-$$SIZE-$$HASH-$$NB_ELEMENTS > performance/$@-$$SIZE-$$HASH-$$NB_ELEMENTS.txt;	\
				rm performance/$@-$$SIZE-$$HASH-$$NB_ELEMENTS;	\
			done;	\
		done;	\
	done


lca.h: sda.h types.h
	cat $< | sed -e s/sda/lca/g -e s/SDA/LCA/g > $@

th.h: sda.h types.h
	cat $< | sed -e s/sda/th/g -e s/SDA/TH/g > $@

tests-lca-commun.c: tests-sda-commun.c
	cat $< | sed -e s/sda/lca/g -e s/SDA/LCA/g > $@
	
tests-th-commun.c: tests-sda-commun.c
	cat $< | sed -e s/sda/th/g -e s/SDA/TH/g > $@

performance-lca-commun.c: performance-sda-commun.c
	cat $< | sed -e s/sda/lca/g -e s/SDA/LCA/g > $@
	
performance-th-commun.c: performance-sda-commun.c
	cat $< | sed -e s/sda/th/g -e s/SDA/TH/g > $@

%-lca.c: %-sda.c
	cat $< | sed -e s/sda/lca/g -e s/SDA/LCA/g > $@

%-th.c: %-sda.c
	cat $< | sed -e s/sda/th/g -e s/SDA/TH/g > $@


types.o: types.h
seatest.o: seatest.h
th.o: th.h
lca-solo.o : lca-solo.h
lca-iterative.o: lca.h
lca-recursive.o: lca.h
exemple-lca.o: lca.h
exemple-th.o: th.h
tests-lca.o: tests-lca.c
tests-th.o: tests-th.c


clean::
	rm -f *.o
	rm -f ${GENERES}
	rm -f $(EXE) a.out
	rm -f -R performance
	rm -f gmon.out

force:: clean all
