COMPILER = g++
CFLAGS   = -std=c++11

all: compile

compile: lexer.o parser.o analyzer.o compiler.o runner.o
	$(COMPILER) $(CFLAGS) lexer.o parser.o analyzer.o compiler.o runner.o -o compile

lexer.o: lexer.h lexer.cpp
	$(COMPILER) $(CFLAGS) -c lexer.h lexer.cpp

parser.o: parser.h parser.cpp
	$(COMPILER) $(CFLAGS) -c parser.h parser.cpp

analyzer.o: analyzer.h analyzer.cpp
	$(COMPILER) $(CFLAGS) -c analyzer.h analyzer.cpp

compiler.o: compiler.h compiler.cpp
	$(COMPILER) $(CFLAGS) -c compiler.h compiler.cpp

runner.o: runner.cpp
	$(COMPILER) $(CFLAGS) -c runner.cpp

clean:
	@rm -rf *.o *.h.gch compile
