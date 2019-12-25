#pragma once

#include "graph.h"
#include "representation.h"

class GraphEvaluator
{
public:
    int64_t ComputeFitness(Graph &graph, CRepresentation &representation);     
};