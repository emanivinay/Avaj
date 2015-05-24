COMP= g++ -std=c++14 -Wall -I. -Icompiler -I'compiler/parsing'

.PHONY: lexer parser expression syntax_error source_buffer tests 

all: syntax_error source_buffer lexer parser tests

tests: source_buffer_driver lexer_driver parser_driver

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

##############   PARSING MODULE START ################################

token_buffer: obj/TokenBuffer

obj/TokenBuffer: lexer compiler/parsing/TokenBuffer.h
	$(COMP) -c -o obj/TokenBuffer compiler/parsing/TokenBuffer.h

obj/ParseResult: compiler/parsing/ParseResult.h 	
	$(COMP) -c -o obj/ParseResult compiler/parsing/ParseResult.h

obj/ParserUtils: obj/TokenBuffer obj/ParseResult compiler/parsing/ParserUtils.h
	$(COMP) -c -o obj/ParserUtils compiler/parsing/ParserUtils.h

expression: obj/Expression

obj/Expression: compiler/parsing/Expression.h compiler/parsing/Expression.cpp
	$(COMP) -c -o obj/Expression compiler/parsing/Expression.cpp

class: obj/ParseResult obj/Class

obj/Class: compiler/parsing/Class.h compiler/parsing/Class.cpp
	$(COMP) -c -o obj/Class compiler/parsing/Class.cpp

ast: obj/AST

obj/AST: obj/ParseResult obj/ParserUtils compiler/parsing/AST.h compiler/parsing/AST.cpp
	$(COMP) -c -o obj/AST compiler/parsing/AST.cpp

parser: token_buffer source_buffer lexer ast expression obj/ParseResult obj/ParserUtils obj/Parser 

parser_driver: parser ast class syntax_error bin/ParserDriver lexer

bin/ParserDriver: tests/ParserDriver.cpp 
	$(COMP) -o bin/ParserDriver obj/SourceBuffer obj/Class obj/Lexer obj/SyntaxError obj/AST obj/Parser tests/ParserDriver.cpp

obj/Parser: compiler/parsing/Parser.h compiler/parsing/Parser.cpp
	$(COMP) -c -o obj/Parser compiler/parsing/Parser.cpp

clean:
	rm -rf bin/* obj/*
