ifeq ($(OS),Windows_NT)
	RMPR = del
	PROGSUFF = .exe
else
	RMPR = rm -f
	PROGSUFF =
endif

PROG = gas
SUFF = cpp
CPP  = g++

# chybi 
CPPFLAGS = -Wall -pedantic --std=c++11

all: $(PROG)

#$(PROG): json.o	$(PROG).$(SUFF) $(PROG).$(SUFF)
#	$(CPP) $(CPPFLAGS) -o $@ $(PROG).$(SUFF)

$(PROG): gas.o pipe.o state.o json.o
	$(CPP) $(CPPFLAGS) gas.o pipe.o state.o json.o -o $@


gas.o: gas.cpp
	$(CPP) $(CPPFLAGS) -c gas.cpp -o $@

state.o: state.cpp state.h
	$(CPP) $(CPPFLAGS) -c state.cpp -o $@

pipe.o: pipe.cpp pipe.h
	$(CPP) $(CPPFLAGS) -c pipe.cpp -o $@

json.o: json.cpp json.h
	$(CPP) $(CPPFLAGS) -c json.cpp -o $@


rebuild: clean all



clean:
	$(RMPR) *.o *.out $(PROG)$(PROGSUFF)