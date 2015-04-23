COMP= g++ --std=c++11 -Wall -I. -Icompiler

.PHONY: source_buffer source_buffer_driver

all: source_buffer source_buffer_driver


source_buffer: obj/SourceBuffer.o

obj/SourceBuffer.o: compiler/SourceBuffer.h compiler/SourceBuffer.cpp
	$(COMP) -c -o obj/SourceBuffer.o compiler/SourceBuffer.cpp

source_buffer_driver: bin/SourceBufferDriver

bin/SourceBufferDriver: obj/SourceBuffer.o tests/SourceBufferDriver.cpp
	$(COMP) -o bin/SourceBufferDriver tests/SourceBufferDriver.cpp obj/SourceBuffer.o

clean:
	rm -rf bin/* obj/*
