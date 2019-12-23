#include <iostream>
#include "graph.h"
#include "representation.h"
#include "population.h"
#include "randomgenerator.h"
#include "graphEvaluator.h"
#include "csvbuilder.h"

using namespace std;

void logPopulation(ofstream &fout,string instanceName,CPopulation &pop,Graph &graph,time_t start,int run)
{
    GraphEvaluator evaluator;
    float bestFit=evaluator.getFitness(graph,*pop.Get(0));
    float meanFit=evaluator.getFitness(graph,*pop.Get(0));
    float worstFit=evaluator.getFitness(graph,*pop.Get(0));

    float sum=0;
    for(int i=0;i<pop.GetCount();i++)
    {
        auto el=pop.Get(i);
        auto fit=evaluator.getFitness(graph,*el);
        sum+=fit;
        if(bestFit>fit)
        {
            bestFit=fit;
        }
        if(worstFit<fit)
        {
            worstFit=fit;
        }
    }
    meanFit=sum/pop.GetCount();
    fout<<run<<","<<instanceName<<","<<pop.GetGeneration()<<","<<bestFit<<","<<meanFit<<","<<worstFit<<","<<time(NULL)-start<<"\n";
}

int main(int argc,char* argv[])
{
    string path = "./ALL_tsp/"+string(argv[1]);
    int popSize=50;
    int MaxGenerations=10000;
    float m_rate=0.2;
    float c_rate=0.2;
    time_t start=time(NULL);


    Graph graph(path);
    GraphEvaluator evaluator;
    string name=string(argv[1]);
    
    name.pop_back();
    name.pop_back();
    name.pop_back();
    name.pop_back();
    ofstream fout(name+".csv");


    CPopulation pop(popSize,graph.number_of_vertexes_,true,0.2,0.2);
    fout<<"run,name, generation, min, mean, max, time ,\n";

    for(int run=1;run<=30;run++)
    {
        CPopulation pop(popSize,graph.number_of_vertexes_,true,m_rate,c_rate);
        for(int i=0;i<=MaxGenerations;i++)
        {
            pop.Evolve();
            if(i%100==0)
            {
                logPopulation(fout, name, pop,graph,start,run);
            }
        }
    }
    return 0;
}