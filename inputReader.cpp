#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    std::cout<<"TEST1\n";
    string path = "ALL_tsp/a280.tsp";
    Graph t(path);
    t.printGraph();
    cout<<"\n";
    return 0;
}