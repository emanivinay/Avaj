COMP= g++ --std=c++11 -Wall -I. -Icompiler

.PHONY: source_buffer source_buffer_driver

all: obj/SyntaxError source_buffer source_buffer_driver

obj/SyntaxError: compiler/SyntaxError.h compiler/SyntaxError.cpp
	$(COMP) -c -o obj/SyntaxError compiler/SyntaxError.cpp

source_buffer: obj/SourceBuffer.o

obj/SourceBuffer.o: obj/SyntaxError compiler/SourceBuffer.h compiler/SourceBuffer.cpp
	$(COMP) -c -o obj/SourceBuffer.o compiler/SourceBuffer.cpp

source_buffer_driver: bin/SourceBufferDriver

bin/SourceBufferDriver: obj/SourceBuffer.o tests/SourceBufferDriver.cpp
	$(COMP) -o bin/SourceBufferDriver tests/SourceBufferDriver.cpp obj/SourceBuffer.o

clean:
	rm -rf bin/* obj/*
