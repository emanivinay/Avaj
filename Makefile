CC := g++ -std=c++11 -Wall -I. -I'compiler' -I'compiler/parsing'

###################### PROJECT OVERALL STRUCTURE ##############################

all: components test_drivers 

components: base lexer parser

base: syntax_error source_buffer

test_drivers: source_buffer_driver lexer_driver parser_driver

########################### BASE TARGETS ######################################

# SyntaxError module.
syntax_error: compiler/SyntaxError.cpp
	${CC} -c -o obj/SyntaxError compiler/SyntaxError.cpp

# SourceBuffer module.
source_buffer: compiler/SourceBuffer.cpp
	${CC} -c -o obj/SourceBuffer compiler/SourceBuffer.cpp

# SourceBufferDriver driver exe.
source_buffer_driver: syntax_error source_buffer tests/SourceBufferDriver.cpp
	${CC} -o bin/SourceBufferDriver obj/SyntaxError obj/SourceBuffer tests/SourceBufferDriver.cpp

########################### LEXER TARGETS #####################################

# Lexer module.
lexer: base compiler/Lexer.cpp
	${CC} -c -o obj/Lexer compiler/Lexer.cpp

# Lexer driver exe.
lexer_driver: lexer tests/LexerDriver.cpp
	${CC} -o bin/LexerDriver obj/SyntaxError obj/SourceBuffer obj/Lexer tests/LexerDriver.cpp

########################### PARSER TARGETS ####################################
PARSER_DIR := compiler/parsing

# Group common parser utilities here.
parser_base: ${PARSER_DIR}/TokenBuffer.h ${PARSER_DIR}/ParserUtils.h ${PARSER_DIR}/ParseResult.h

expression: ${PARSER_DIR}/Expression.h ${PARSER_DIR}/Expression.cpp
	${CC} -c -o obj/Expression ${PARSER_DIR}/Expression.cpp

statement: ${PARSER_DIR}/Statement.cpp
	${CC} -c -o obj/Statement ${PARSER_DIR}/Statement.cpp

class: ${PARSER_DIR}/Class.cpp
	${CC} -c -o obj/Class ${PARSER_DIR}/Class.cpp

ast: ${PARSER_DIR}/AST.cpp
	${CC} -c -o obj/AST ${PARSER_DIR}/AST.cpp

parser: lexer parser_base expression statement class ast ${PARSER_DIR}/Parser.cpp
	${CC} -c -o obj/Parser ${PARSER_DIR}/Parser.cpp

parser_driver: parser tests/ParserDriver.cpp
	${CC} -o bin/ParserDriver tests/ParserDriver.cpp obj/*

# Clean every module and every exe.
clean:
	rm -rf obj/* bin/*
