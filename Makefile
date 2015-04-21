COMP=g++ -Wall -I. -Icompiler

all: source_buffer make_test

obj/SourceBuffer.o: compiler/SourceBuffer.h compiler/SourceBuffer.cpp
	$(COMP) -c -o obj/SourceBuffer.o compiler/SourceBuffer.cpp

bin/make_test: tests/make_test.cpp
	$(COMP) -o bin/make_test tests/make_test.cpp

clean:
	rm -rf bin/* obj/*
