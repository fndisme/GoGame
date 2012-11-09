main: GoAction.o main.o
	g++ -o $@ $^
main.o : main.cpp GoAction.h GoDef.h
	g++ -std=c++0x -c -o $@ $<
GoAction.o : GoAction.cpp GoDef.h GoAction.h
	g++ -std=c++0x -c -o $@ $<
