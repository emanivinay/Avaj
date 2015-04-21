COMP=g++ -Wall -I. -Icompiler

all: source_buffer

source_buffer: compiler/SourceBuffer.h compiler/SourceBuffer.cpp
	$(COMP) -c -o bin/SourceBuffer.o compiler/SourceBuffer.cpp

clean:
	rm -rf bin/* obj/*
