#include "graph.h"


#include <unistd.h>


#define EDGE_LIST     1                          ////The graph is given by an edge list
#define ADJ_LIST      2                          ////The graph is given as an adjacency list
#define TWOD_COORDS   3                          ////Nodes are specified by coordinates in 2-D
#define THREED_COORDS 4                          ////Nodes are specified by coordinates in 3-D
#define NO_COORDS     5


#define FUNCTION        6           ////Weights are given by a function (see above)
#define FULL_MATRIX     7           ////Weights are given by a full matrix
#define UPPER_ROW       8       ////Upper triangular matrix (row-wise without diagonal entries)
#define LOWER_ROW       9       ////Lower triangular matrix (row-wise without diagonal entries)
#define UPPER_DIAG_ROW  10          ////Upper triangular matrix (row-wise including diagonal entries)
#define LOWER_DIAG_ROW  11         ////Lower triangular matrix (row-wise including diagonal entries)
#define UPPER_COL       12     ////Upper triangular matrix (column-wise without diagonal entries)
#define LOWER_COL       13     ////Lower triangular matrix (column-wise without diagonal entries)
#define UPPER_DIAG_COL  14         ////Upper triangular matrix (column-wise including diagonal entries)
#define LOWER_DIAG_COL  15

std::string ltrim(std::string str, const std::string chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
 
std::string rtrim(std::string str, const std::string chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
 
std::string trim(std::string str, const std::string chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}


float distance(pair<float,float> p1 , pair<float,float> p2,int distance_function)
{
    float aux1=(p1.first-p2.first)*(p1.first-p2.first);
    float aux2=(p1.second-p2.second)*(p1.second-p2.second);
    float res=sqrt(aux1+aux2);
    if(distance_function==EUC_2D)
    {
        return res;
    }
    else
    {
        cout<<"NOT IMPLEMENTED DISTANCE";
        return 0;
    }
    
}

Graph::Graph(string path_to_input_file)
{
    
    string name;
    string type;
    string comment;
    string dimmension;
    string edge_weight_type;

    int representation=NO_COORDS;

    ifstream fin(path_to_input_file);
    char buffer[BUFSIZ];
    memset(buffer,0,BUFSIZ);


    string keyword="";
    string content="";
    while(1)///READ FLAGS
    {
        fin.getline(buffer,BUFSIZ);
        if(string(buffer)=="NODE_COORD_SECTION" || string(buffer)=="EDGE_WEIGHT_SECTION")
        {
            break;
        }
        keyword=string(strtok(buffer,":"));
        keyword=trim(keyword);

        content=string(strtok(NULL,":"));
        content=trim(content);
        cout<<keyword<<"\n"<<content<<"\n\n";
        if(keyword=="COMMENT")
        {
            comment=content;
        }
        else if (keyword=="DIMENSION")
        {
            number_of_vertexes_=atoi(content.c_str());
        }
        else if (keyword=="CAPACITY")
        {
            cout<<"ERROR\n This should not be in the input\n";
            exit(1);
        }
        else if (keyword=="EDGE_WEIGHT_TYPE")
        {
            if(content=="EXPLICIT")
            {
                distance_function_=EXPLICIT;
            }
            else if(content=="EUC_2D")
            {
                distance_function_=EUC_2D;
            }
            else if(content=="CEIL_2D")
            {
                distance_function_=CEIL_2D;
            }
            else if(content=="GEO")
            {
                distance_function_=GEO;
            }
            else if(content=="ATT")
            {
                distance_function_=ATT;
            }
            else
            {
                cout<<"NOT IMPLEMENTED\n";
                exit(1);
            }
        }
        else if (keyword=="EDGE_WEIGHT_FORMAT")
        {
            if(content=="FUNCTION")
            {
                representation= FUNCTION;
            }
            else if(content=="FULL_MATRIX")
            {
                representation= FULL_MATRIX;
            }
            else if(content=="UPPER_DIAG_ROW")
            {
                representation= UPPER_DIAG_ROW;
            }
            else if(content=="LOWER_DIAG_ROW")
            {
                representation= LOWER_DIAG_ROW;
            }
            else
            {
                cout<<"NOT IMPLEMENTED\n";
                exit(1);
            }
        }
    }

    list<pair<float,float>> points;

    for (int i=1;i<=number_of_vertexes_;i++)
    {
        vertexes_.push_back(i+1);
        edges_.push_back(list<pair<int,double>>());
    }

    if(representation==-1)
    {
        std::cout<<"SOMETHIN WENT WRONG\nMISSING FLAG: representation\n";
        exit(1);
    }
    std::cout<<name<<"\n"<<representation<<"\n"<<comment<<"\n";
    while(1)///READ EDGES
    {
        fin.getline(buffer,BUFSIZ);
        ifstream line(trim(string(buffer)));
        if(string(buffer)=="EOF")
        {
            break;
        }
        ///usleep(100000);
        if(distance_function_==EXPLICIT)
        {
            if(representation==FULL_MATRIX)
            {
                std::cout<<"not implemented\n";
                exit(0);
            }
            else if(representation==UPPER_ROW)
            {
                std::cout<<"not implemented\n";
                exit(0);
            }
            else if(representation==UPPER_DIAG_ROW)
            {
                std::cout<<"not implemented\n";
                exit(0);
            }
            else if(representation==LOWER_DIAG_ROW)
            {
                std::cout<<"not implemented\n";
                exit(0);
            }
        }
        else
        {
            if(representation==NO_COORDS)
            {
                int idx;
                float x,y;
                sscanf(trim(string(buffer)).c_str(),"%d %f %f",&idx,&x,&y);
                if(idx==-1)
                {
                    break;
                }
                points.push_back({x,y});
            }
            else if (representation==FUNCTION)
            {
                std::cout<<"not implemented\n";
                exit(0);
            }
        }
    }
    if(distance_function_==EXPLICIT)
    {
        std::cout<<"NOT IMPLEMENTED YET\n";
        exit(0);
    }
    else
    {
        auto i_iterator=points.begin();
        auto j_iterator=points.end();

        for(int i=0;i<number_of_vertexes_;i++)
        {
            j_iterator=i_iterator;
            j_iterator++;
            for(int j=i+1;j<number_of_vertexes_;j++)
            {
                auto k_iterator=edges_.begin();
                for(int k=0;k<number_of_vertexes_;k++)
                {
                    if(k==i)
                    {
                        k_iterator->push_back({j,distance(*i_iterator,*j_iterator,distance_function_)});
                    }
                    else if(k==j)
                    {
                        k_iterator->push_back({i,distance(*i_iterator,*j_iterator,distance_function_)});
                    }
                    k_iterator++;
                }
                j_iterator++;
            }
            i_iterator++;
        }
    }
    cout<<"DONE\n";
}

Graph::~Graph()
{

}

void Graph::printGraph()
{
    cout<<"Distance: "<<this->distance_function_<<"\n";
    cout<<"N of vertexes "<<this->number_of_vertexes_<<"\n";
    cout<<"EDGES";
    int idx=0;
    for(auto idx_adj:edges_)
    {
        cout<<idx<<":\n";
        for (auto el:idx_adj)
        {
            cout<<"node: "<<el.first<<" distance: "<<el.second<<"\n";
        }
        idx++;
    }
    
}
