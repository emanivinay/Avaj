COMP= g++ --std=c++11 -Wall -I. -Icompiler

.PHONY: lexer syntax_error source_buffer tests 

all: lexer syntax_error source_buffer tests

tests: source_buffer_driver lexer_driver

lexer_driver: bin/LexerDriver

lexer: obj/Lexer

bin/LexerDriver: tests/LexerDriver.cpp obj/Lexer obj/SourceBuffer
	$(COMP) -o bin/LexerDriver tests/LexerDriver.cpp obj/Lexer obj/SourceBuffer

obj/Lexer: compiler/Lexer.cpp
	$(COMP) -c -o obj/Lexer compiler/Lexer.cpp

syntax_error: obj/SyntaxError

obj/SyntaxError: compiler/SyntaxError.h compiler/SyntaxError.cpp
	$(COMP) -c -o obj/SyntaxError compiler/SyntaxError.cpp

source_buffer: obj/SourceBuffer

obj/SourceBuffer: obj/SyntaxError compiler/SourceBuffer.h compiler/SourceBuffer.cpp
	$(COMP) -c -o obj/SourceBuffer compiler/SourceBuffer.cpp

source_buffer_driver: bin/SourceBufferDriver

bin/SourceBufferDriver: obj/SourceBuffer tests/SourceBufferDriver.cpp
	$(COMP) -o bin/SourceBufferDriver tests/SourceBufferDriver.cpp obj/SourceBuffer

clean:
	rm -rf bin/* obj/*
