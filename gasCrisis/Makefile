PROG = gas
SUFF = cpp
CPP  = g++

# chybi -pedantic
CPPFLAGS = -Wall --std=c++11

all: $(PROG)

$(PROG):	$(PROG).$(SUFF) $(PROG).$(SUFF)
	$(CPP) $(CPPFLAGS) -o $@ $(PROG).$(SUFF)

rebuild: clean all

clean:
	rm -f *.o *.out $(PROG)