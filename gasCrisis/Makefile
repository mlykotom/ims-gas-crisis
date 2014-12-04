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

$(PROG): main.o stateStats.o inout.o date_time.o timer.o pipe.o state.o json.o
	$(CPP) $(CPPFLAGS) main.o stateStats.o inout.o date_time.o timer.o pipe.o state.o json.o -o $@

main.o: main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp -o $@

state.o: state.cpp state.h
	$(CPP) $(CPPFLAGS) -c state.cpp -o $@

pipe.o: pipe.cpp pipe.h
	$(CPP) $(CPPFLAGS) -c pipe.cpp -o $@

json.o: json.cpp json.h
	$(CPP) $(CPPFLAGS) -c json.cpp -o $@

timer.o: timer.cpp timer.h
	$(CPP) $(CPPFLAGS) -c timer.cpp -o $@

inout.o: inout.cpp inout.h
	$(CPP) $(CPPFLAGS) -c inout.cpp -o $@
	
date_time.o: date_time.cpp date_time.h
	$(CPP) $(CPPFLAGS) -c date_time.cpp -o $@

stateStats.o: stateStats.cpp stateStats.h
	$(CPP) $(CPPFLAGS) -c stateStats.cpp -o $@


rebuild: clean all

run: ./$(PROG)$(PROGSUFF)

clean:
	$(RMPR) *.o *.out $(PROG)$(PROGSUFF)