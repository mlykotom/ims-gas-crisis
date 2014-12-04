#	Projekt IMS
#
#  xkobli00 - Ondrej Koblizek
#  xmarec12 - Matej Marecek
#
#

PROG = ims
DATASAMPLER = DataSampler.jar
CC = g++

OBJDIR = obj

# pro odevzdani
#CFLAGS = -DNDEBUG 
# pro ladeni
CFLAGS = -g -D_DEBUG

CFLAGS += -pedantic

LDFLAGS = -lsimlib -lm

WARNCFLAGS = -Wall -Wshadow -Wpointer-arith \
		-Wcast-qual -Wcast-align
		
WARNLD = -Wbad-function-cast -Wstrict-prototypes -Wmissing-declarations


SOURCES = $(notdir $(wildcard src/*.cc))

OBJECTS = $(patsubst %.cc,$(OBJDIR)/%.o,$(SOURCES))

.PHONY: all

all: $(PROG) $(DATASAMPLER)
auto: $(PROG) $(DATASAMPLER) run

$(PROG): $(OBJECTS)
	@echo "==> Linkuji: IMS <=="
	$(CC) $(WARNCFLAGS) $(WARNLD) $(CFLAGS) -o $(PROG) $(OBJECTS) $(LDFLAGS)
	@echo "==> OK <=="

$(DATASAMPLER):
	@echo "==> Prekladam DataSampler <=="
	cd src/DataSamplerSrc && javac datasampler/DataSampler.java && jar cfm DataSampler.jar Manifest.txt datasampler/*.class && mv DataSampler.jar ../..
	@echo "==> OK <=="
	
$(OBJDIR)/%.o: src/%.cc
	@mkdir -p $(OBJDIR)
	@mkdir -p out
	@echo "==> Prekladam:" $< "<=="
	$(CC) $(WARNCFLAGS) $(CFLAGS) -c $< -o $@
	@echo "==> OK <=="
	
clean:
	rm -f $(OBJECTS) $(PROG) $(DATASAMPLER)
	rm -f 06_xkobli00_xmarec12.tar.gz
	rm -r $(OBJDIR)
	rm -rf out

tar:
	tar -zcvf 06_xkobli00_xmarec12.tar.gz --exclude=.svn --exclude=obj --exclude=out --exclude=$(PROG) --exclude=$(DATASAMPLER) --exclude="*~" * 

plot:
	java -jar DataSampler.jar out/output.dat 1000 > out/output2.dat
	java -jar DataSampler.jar out/web.dat 1000 > out/web2.dat
	java -jar DataSampler.jar out/web_request.dat 1000 > out/web_request2.dat
	cd out && gnuplot plot.plt && cd ..

run:
	./ims params
	make plot
