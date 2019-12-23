all:
	g++ -c graph.cpp
	g++ -c randomgenerator.cpp
	g++ -c representation.cpp
	g++ -c inputReader.cpp

	g++ graph.o randomgenerator.o representation.o inputReader.o -o exec.exe
	rm *.o