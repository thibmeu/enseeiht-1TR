CC=c99
LDFLAGS=-lm

EXE=ordo_simple rate_monotonic round_robbin

all: $(EXE) 

ordo_simple: ordo_simple.o
	 $(CC) -o $@ $^ $(LDFLAGS)

rate_monotonic: rate_monotonic.o
	 $(CC) -o $@ $^ $(LDFLAGS)

round_robbin: round_robbin.o
	 $(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o *~
	rm -f $(EXE)
