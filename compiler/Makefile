COMPILER = g++
CFLAGS   = -std=c++11

all: compile

compile: lexer parser analyzer compiler runner
	$(COMPILER) $(CFLAGS) lexer.o parser.o analyzer.o compiler.o runner.o -o compile

lexer: lexer.h lexer.cpp
	$(COMPILER) $(CFLAGS) -c lexer.h lexer.cpp

parser: lexer parser.h parser.cpp
	$(COMPILER) $(CFLAGS) -c parser.h parser.cpp

analyzer: parser analyzer.h analyzer.cpp
	$(COMPILER) $(CFLAGS) -c analyzer.h analyzer.cpp

compiler: analyzer compiler.h compiler.cpp
	$(COMPILER) $(CFLAGS) -c compiler.h compiler.cpp

runner: compiler runner.cpp
	$(COMPILER) $(CFLAGS) -c runner.cpp

clean:
	@rm -rf *.o *.h.gch compile
