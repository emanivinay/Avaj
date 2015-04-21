COMP= g++ --std=c++11 -Wall -I. -Icompiler

all: source_buffer 

.PHONY: source_buffer
source_buffer: obj/SourceBuffer.o

obj/SourceBuffer.o: compiler/SourceBuffer.h compiler/SourceBuffer.cpp
	$(COMP) -c -o obj/SourceBuffer.o compiler/SourceBuffer.cpp

clean:
	rm -rf bin/* obj/*
