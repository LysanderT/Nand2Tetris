CC=g++
CFLAGS=-Wall -g -c -std=c++11

VMTranslator: Parser.o CodeWriter.o VMTranslator.o
	$(CC) -g -Wall -std=c++11 -I. -o VMTranslator Parser.o CodeWriter.o VMTranslator.o
	chmod ugo+x ./VMTranslator

Parser.o: Parser.cpp Parser.h
	$(CC) $(CFLAGS) Parser.cpp

CodeWriter.o: CodeWriter.cpp CodeWriter.h
	$(CC) $(CFLAGS) CodeWriter.cpp

VMTranslator.o: VMTranslator.cpp VMTranslator.h Parser.h CodeWriter.h
	$(CC) $(CFLAGS) VMTranslator.cpp

.PHONY: clean
clean:
	rm -rf *.o VMTranslator