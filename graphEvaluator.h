#pragma once

#include "graph.h"
#include "representation.h"

class GraphEvaluator
{
    public:
    int64_t getFitness(Graph &graph, CRepresentation &representation);     
    list<int> getDecodedRepresentation(CRepresentation &representation);
};