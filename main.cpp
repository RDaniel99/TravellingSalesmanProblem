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
    

    for(int i=0;i<10;i++)
    {
        auto x=CRepresentation(true,t.number_of_vertexes_);

        auto f=evaluator.getDecodedRepresentation(x);

        auto fit=evaluator.getFitness(t,x);
        cout<<"\n";
        for(auto el:f)
        {
            cout<<el<<" ";
        }
        cout<<"FIT: "<<fit<<"\n";
        if(fit<best) best=fit;
    }
    cout<<best<<"\n";
    return 0;
}