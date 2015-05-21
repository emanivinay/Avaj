COMP= g++ -std=c++14 -Wall -I. -Icompiler -I'compiler/parsing'

.PHONY: lexer parser expression syntax_error source_buffer tests 

all: syntax_error source_buffer lexer parser tests

tests: source_buffer_driver lexer_driver

lexer_driver: bin/LexerDriver

lexer: source_buffer obj/Lexer

bin/LexerDriver: tests/LexerDriver.cpp obj/Lexer obj/SourceBuffer syntax_error
	$(COMP) -o bin/LexerDriver tests/LexerDriver.cpp obj/Lexer obj/SourceBuffer obj/SyntaxError

obj/Lexer: compiler/Lexer.h compiler/Lexer.cpp
	$(COMP) -c -o obj/Lexer compiler/Lexer.cpp

syntax_error: obj/SyntaxError

obj/SyntaxError: compiler/SyntaxError.h compiler/SyntaxError.cpp
	$(COMP) -c -o obj/SyntaxError compiler/SyntaxError.cpp

source_buffer: obj/SourceBuffer

obj/SourceBuffer: obj/SyntaxError compiler/SourceBuffer.h compiler/SourceBuffer.cpp
	$(COMP) -c -o obj/SourceBuffer compiler/SourceBuffer.cpp

source_buffer_driver: bin/SourceBufferDriver

bin/SourceBufferDriver: source_buffer tests/SourceBufferDriver.cpp syntax_error
	$(COMP) -o bin/SourceBufferDriver tests/SourceBufferDriver.cpp obj/SourceBuffer obj/SyntaxError

expression: obj/Expression

obj/Expression: obj/Lexer obj/SourceBuffer compiler/parsing/Expression.h
	$(COMP) -c -o obj/Expression obj/SourceBuffer obj/Lexer compiler/parsing/Expression.h

parser: expression

clean:
	rm -rf bin/* obj/*
