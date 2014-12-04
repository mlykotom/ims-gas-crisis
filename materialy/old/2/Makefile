CC = g++
CFLAGS = -Wall -g

all:	priklad1 priklad2

simulator.o : simulator.cc simulator.h
	${CC} ${CFLAGS} -c simulator.cc

priklad1.o : priklad1.cc
	${CC} ${CFLAGS} -c priklad1.cc

priklad1 : simulator.o priklad1.o
	${CC} ${CFLAGS} simulator.o priklad1.o -o priklad1

priklad2.o : priklad2.cc
	${CC} ${CFLAGS} -c priklad2.cc

priklad2 : simulator.o priklad2.o
	${CC} ${CFLAGS} simulator.o priklad2.o -o priklad2

run:
	./priklad1
	./priklad2

pack:
	zip 02_xseitl01_xsafar13.zip Makefile dokumentace.pdf *.h *.cc 	

clean:
	rm -f priklad1
	rm -f priklad1.o
	rm -f priklad2
	rm -f priklad2.o	
	rm -f simulator.o