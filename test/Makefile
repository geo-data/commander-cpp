run: test test.sh tests.txt expected/*.txt
	bash test.sh
test: commander.o ../include/commander.hpp test.cpp
	$(CXX) -g -ggdb -Wall -Wextra --pedantic -I./commander/src -I../include -o test test.cpp commander.o
commander.o: commander commander/src/commander.h commander/src/commander.c
	$(CC) -g -ggdb -std=c99 -Wall -Wextra --pedantic -c -o commander.o commander/src/commander.c
commander:
	git submodule update --init

clean:
	rm -f commander.o test

.PHONY: clean run
