#include <iostream>
#include "graph.h"
#include "representation.h"
#include "population.h"
#include "randomgenerator.h"
#include "graphEvaluator.h"
#include "csvbuilder.h"

using namespace std;

int main(int argc,char* argv[])
{
    string path = "./ALL_tsp/"+string(argv[1]);
    Graph t(path);

    GraphEvaluator evaluator;

    list<CRepresentation> repr;
    int best=99999999;
    

    CPopulation pop(100,t.number_of_vertexes_,true);

    for(int i=0;i<100;i++)
    {
        cout<<evaluator.getFitness(t, *pop.Get(i))<<"\n";
    }
    return 0;
}