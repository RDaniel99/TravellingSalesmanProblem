#include "graphEvaluator.h"

int64_t GraphEvaluator::getFitness(Graph &graph, CRepresentation &representation)
{
    int64_t sum=0;
    list<int> path=getDecodedRepresentation(representation);
    auto iter=path.begin();

    for (int idx=0;idx<graph.number_of_vertexes_-1;idx++)
    {
        auto iter2=iter;
        iter2++;
        sum+=graph.GetCost(*iter,*iter2);
        iter++;
    }
    return sum;
}

list<int> GraphEvaluator::getDecodedRepresentation(CRepresentation &representation)
{
    list<int> result;
    list<int> nodes;
    for(int i=0;i<representation.GetCount();i++)
    {
        nodes.push_back(i);
    }
    for(int i=0;i<representation.GetCount();i++)
    {
        int aux=representation.Get(i);
        auto iter=nodes.begin();
        for( int j=0; j<aux; j++)
        {
            iter++;
        }

        cout<<aux<<"\n";
        for(auto el:nodes)
        {
            cout<<el<<" ";
        }
        cout<<"\n\n";
        result.push_back(*iter);
        nodes.remove(*iter);
    }
    return result;
}
