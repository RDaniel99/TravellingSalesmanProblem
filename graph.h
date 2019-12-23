#pragma once

#include <list>
#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <math.h>


using namespace std;



#define EXPLICIT 0                      //// Weights are listed explicitly in the corresponding section
#define EUC_2D   1                      ////Weights are Euclidean distances in 2-D
#define EUC_3D   2                      ////Weights are Euclidean distances in 3-D

#define MAX_2D   3                      ////Weights are maximum distances in 2-D
#define MAX_3D   4                      ////Weights are maximum distances in 3-D
#define MAN_2D   5                      ////Weights are Manhattan distances in 2-D
#define MAN_3D   6                      ////Weights are Manhattan distances in 3-D
#define CEIL_2D  7                      ////Weights are Euclidean distances in 2-D rounded up
#define GEO      8                      ////Weights are geographical distances
#define ATT      9                      ////Special distance function for problems att48 and att532
#define XRAY1    10                     ////Special distance function for crystallography problems (Version 1)
#define XRAY2    11                     ////Special distance function for crystallography problems (Version 2)


class Graph
{
    public:
    int number_of_vertexes_;
    int number_of_edges_;
    int distance_function_;

    list<int>        vertexes_;
    list<list<pair<int,float>>>  edges_;///pair left  - index of neighbour
                                         ////pair right - cost of edge
    
    float GetCost(int idx1,int idx2);
    void printGraph();
    Graph(string path_to_input_file);
    ~Graph();


};