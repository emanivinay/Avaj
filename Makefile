CC := g++ -g -std=c++11 -Wall -I. -I'compiler' -I'compiler/parsing' \
	  -I'compiler/types' -I'common'

###################### PROJECT OVERALL STRUCTURE ##############################

all: components test_drivers 

components: base lexer parser types

base: syntax_error source_buffer

test_drivers: source_buffer_driver lexer_driver expression_driver \
			  parser_driver statement_driver hl_reader_driver

########################### BASE TARGETS ######################################

# SyntaxError module.
syntax_error: compiler/SyntaxError.h compiler/SyntaxError.cpp
	${CC} -c -o obj/SyntaxError compiler/SyntaxError.cpp

# SourceBuffer module.
source_buffer: compiler/SourceBuffer.h compiler/SourceBuffer.cpp
	${CC} -c -o obj/SourceBuffer compiler/SourceBuffer.cpp

# SourceBufferDriver driver exe.
source_buffer_driver: syntax_error source_buffer tests/SourceBufferDriver.cpp
	${CC} -o bin/SourceBufferDriver obj/SyntaxError obj/SourceBuffer \
	tests/SourceBufferDriver.cpp

########################### LEXER TARGETS #####################################

# Lexer module.
lexer: base compiler/Lexer.h compiler/Lexer.cpp
	${CC} -c -o obj/Lexer compiler/Lexer.cpp

# Lexer driver exe.
lexer_driver: lexer tests/LexerDriver.cpp
	${CC} -o bin/LexerDriver obj/SyntaxError obj/SourceBuffer obj/Lexer \
	tests/LexerDriver.cpp

########################### PARSER TARGETS ####################################
PARSER_DIR := compiler/parsing

# Group common parser utilities here.
parser_base: ${PARSER_DIR}/TokenBuffer.h ${PARSER_DIR}/ParserUtils.h \
			 ${PARSER_DIR}/ParseResult.h

expression: ${PARSER_DIR}/Expression.h ${PARSER_DIR}/Expression.cpp
	${CC} -c -o obj/Expression ${PARSER_DIR}/Expression.cpp

expression_driver: lexer parser_base expression tests/ExpressionDriver.cpp
	${CC} -o bin/Expression tests/ExpressionDriver.cpp obj/*

statement: ${PARSER_DIR}/Statement.h ${PARSER_DIR}/Statement.cpp
	${CC} -c -o obj/Statement ${PARSER_DIR}/Statement.cpp

statement_driver: lexer parser_base expression statement tests/Statements.cpp
	${CC} -o bin/Statements tests/Statements.cpp obj/*

class: ${PARSER_DIR}/Class.h ${PARSER_DIR}/Class.cpp
	${CC} -c -o obj/Class ${PARSER_DIR}/Class.cpp

ast: ${PARSER_DIR}/AST.h ${PARSER_DIR}/AST.cpp
	${CC} -c -o obj/AST ${PARSER_DIR}/AST.cpp

parser: lexer parser_base expression statement class ast \
		${PARSER_DIR}/Parser.h ${PARSER_DIR}/Parser.cpp
	${CC} -c -o obj/Parser ${PARSER_DIR}/Parser.cpp

parser_driver: parser tests/ParserDriver.cpp
	${CC} -o bin/ParserDriver tests/ParserDriver.cpp obj/*

########################### TYPES TARGETS #####################################
TYPES_DIR := compiler/types

types: parser hl_reader type method builtin

type: ${TYPES_DIR}/Type.h ${TYPES_DIR}/Type.cpp
	${CC} -c -o obj/Type ${TYPES_DIR}/Type.cpp

hl_reader: ${TYPES_DIR}/HLReader.h ${TYPES_DIR}/HLReader.cpp
	${CC} -c -o obj/HLReader ${TYPES_DIR}/HLReader.cpp

hl_reader_driver: hl_reader tests/HLReaderDriver.cpp
	${CC} -o bin/HLReaderDriver obj/HLReader tests/HLReaderDriver.cpp

method: ${TYPES_DIR}/Method.h ${TYPES_DIR}/Method.cpp
	${CC} -c -o obj/Method ${TYPES_DIR}/Method.cpp

builtin: ${TYPES_DIR}/BuiltinType.h ${TYPES_DIR}/BuiltinType.cpp
	${CC} -c -o obj/BuiltinType ${TYPES_DIR}/BuiltinType.cpp

#################################### CLEAN ####################################
# Clean every module and every exe.
clean:
	rm -rf obj/* bin/*
