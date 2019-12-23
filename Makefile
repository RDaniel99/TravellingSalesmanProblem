all:
	g++ -c graph.cpp
	g++ -c graphEvaluator.cpp
	g++ -c randomgenerator.cpp
	g++ -c representation.cpp
	g++ -c population.cpp
	g++ -c main.cpp
	g++ -c csvbuilder.cpp



	g++ graph.o graphEvaluator.o randomgenerator.o representation.o main.o population.o csvbuilder.o -o exec.exe
	rm *.o