DIR := bin

all:
	$(shell mkdir $(DIR))
	g++ -c src/arg.cpp -std=c++17 -O2 -Wall -DNDEBUG  -o $(DIR)/src.arg.cpp.o -I.
	g++ -c src/main.cpp -std=c++17 -O2 -Wall -DNDEBUG  -o $(DIR)/src.main.cpp.o -I.
	g++ -o $(DIR)/dirt.exe $(DIR)/src.arg.cpp.o $(DIR)/src.main.cpp.o -L. -static -static-libgcc -static-libstdc++ -s