main: GoAction.o main.o GoStone.o GoBoard.o GoGroup.o
	g++ -o $@ $^
main.o : main.cpp GoStone.h GoAction.h GoDef.h 
	g++ -std=c++0x -c -o $@ $<
GoAction.o : GoAction.cpp GoDef.h GoAction.h
	g++ -std=c++0x -c -o $@ $<

GoStone.o: GoStone.cpp GoStone.h GoDef.h
	g++ -std=c++0x -c -o $@ $<

GoBoard.o: GoBoard.cpp GoBoard.h GoAction.h GoDef.h GoStone.h GoGroup.h
	g++ -std=c++0x -c -o $@ $<

GoGroup.o: GoGroup.cpp GoGroup.h GoDef.h 
	g++ -std=c++0x -c -o $@ $<
