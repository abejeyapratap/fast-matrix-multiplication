STD=--std=c++17 -pthread
GCC=g++
OBJ=obj
BIN=bin

bin/mult: src/main.cpp
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o bin/mult src/main.cpp

.PHONY: doc run clean

run: bin/mult
	./bin/mult 7 seq7.txt

clean:
	rm -f obj/*.o
	rm -f bin/search
	rm -r -f bin
	rm -r -f obj
	rm -r -f html
	rm -r -f latex
