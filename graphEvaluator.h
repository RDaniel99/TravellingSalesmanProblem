#pragma once

#include "graph.h"
#include "representation.h"

class GraphEvaluator
{
public:
    float ComputeFitness(Graph &graph, CRepresentation &representation);     
};