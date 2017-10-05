COMPILER = g++

all: assembler

assembler: assembler.o
	$(COMPILER) assembler.o -o assembler

assembler.o: assembler.h assembler.cpp
	$(COMPILER) -c assembler.h assembler.cpp

clean:
	@rm -rf *.o *.h.gch assembler
