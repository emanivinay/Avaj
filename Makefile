COMP= g++ --std=c++11 -Wall -I. -I$(CMPLR)
CMPLR= compiler
BIN=bin
OBJ=obj

.PHONY: lexer syntax_error source_buffer source_buffer_driver

all: lexer syntax_error source_buffer source_buffer_driver

lexer: obj/Lexer

obj/Lexer: $(CMPLR)/Lexer.cpp
	$(COMP) -c -o obj/Lexer $(CMPLR)/Lexer.cpp

syntax_error: obj/SyntaxError

obj/SyntaxError: $(CMPLR)/SyntaxError.h $(CMPLR)/SyntaxError.cpp
	$(COMP) -c -o obj/SyntaxError $(CMPLR)/SyntaxError.cpp

source_buffer: obj/SourceBuffer.o

obj/SourceBuffer.o: obj/SyntaxError $(CMPLR)/SourceBuffer.h $(CMPLR)/SourceBuffer.cpp
	$(COMP) -c -o obj/SourceBuffer.o $(CMPLR)/SourceBuffer.cpp

source_buffer_driver: bin/SourceBufferDriver

bin/SourceBufferDriver: obj/SourceBuffer.o tests/SourceBufferDriver.cpp
	$(COMP) -o bin/SourceBufferDriver tests/SourceBufferDriver.cpp obj/SourceBuffer.o

clean:
	rm -rf bin/* obj/*
