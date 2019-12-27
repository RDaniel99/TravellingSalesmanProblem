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
    int bestFitIdx=0;
    float bestFit=evaluator.ComputeFitness(graph,*pop.Get(0));
    float meanFit=evaluator.ComputeFitness(graph,*pop.Get(0));
    int worstFitIdx=0;
    float worstFit=evaluator.ComputeFitness(graph,*pop.Get(0));

    float sum=0;
    for(int i=0;i<pop.GetPopSize();i++)
    {
        auto el=pop.Get(i);
        auto fit=evaluator.ComputeFitness(graph,*el);
        sum+=fit;
        if(bestFit>fit)
        {
            bestFitIdx=i;
            bestFit=fit;
        }
        if(worstFit<fit)
        {
            worstFitIdx=i;
            worstFit=fit;
        }
    }
    meanFit=sum/pop.GetCount();
    fout<<run<<","<<instanceName<<","<<pop.GetGeneration()<<","<<bestFit<<","<<meanFit<<","<<worstFit<<","<<time(NULL)-start<<"\n";
  
    ///cout<<bestFitIdx<<"\n";
    ///list<int> decode= CRepresentation::Decode(*pop.Get(bestFitIdx));
    
    ///for (int i=0;i<pop.Get(bestFitIdx)->GetCount();i++)
    ///{
    ///   cout<<pop.Get(bestFitIdx)->Get(i)<<" ";
    ///}
    ///cout<<"\n";
    ///for(auto el:decode)
    ///{
    ///    cout<<el<<" ";
    ///}
    ///cout<<"\n";
}

int main(int argc,char* argv[])
{
    srand(time(NULL));
    string path = "./ALL_tsp/"+string(argv[1]);
    int popSize=20;
    int MaxGenerations=10000;
    float m_rate=0.01;
    float c_rate=1;
    time_t start=time(NULL);

    Graph graph(path);
    graph.printGraph();
    GraphEvaluator evaluator;
    string name=string(argv[1]);
    
    name.pop_back();
    name.pop_back();
    name.pop_back();
    name.pop_back();
    ofstream fout(name+".csv");


    fout<<"run,name, generation, min, mean, max, time ,\n";

    float best=999999;
    for(int i=0;i<MaxGenerations;i++)
    {
        CRepresentation c(true,graph.number_of_vertexes_);
        if(evaluator.ComputeFitness(graph,c)<best)
        {
            cout<<evaluator.ComputeFitness(graph,c)<<"\n";
            best=evaluator.ComputeFitness(graph,c);
        }
    }
    cout<<"Random search best: "<<best<<"\n";
    cin>>best;

    for(int run=1;run<=1;run++)
    {
        ///std::cout <<"run: "<< run << '\n';
        CPopulation pop(popSize,graph.number_of_vertexes_,graph,evaluator,true,0.05,0.02);
        for(int i=0;i<=MaxGenerations;i++)
        {
            if(i%100==0)
            {
                std::cout<<"    Generation: "<<pop.GetGeneration()<<"\n";
                logPopulation(fout, name, pop,graph,start,run);
            }
            pop.Evolve(false);

        }
    }
    return 0;
}