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


float distance(pair<float,float> p1 , pair<float,float> p2,int distance_function)////should return rounded integers
{
    if(distance_function==EUC_2D)
    {
        float aux1=(p1.first-p2.first)*(p1.first-p2.first);
        float aux2=(p1.second-p2.second)*(p1.second-p2.second);
        float res=sqrt(aux1+aux2);

        return round(res);
    }
    else if(distance_function==GEO)
    {
        float RRR = 6378.388;
        float PI = 3.141592;

        float deg1 = round( p1.first );
        float min1 = p1.first - deg1;
        float latitude1 = PI * (deg1 + 5.0 * min1 / 3.0 ) / 180.0;
        deg1 = round( p1.second );
        min1 = p1.second - deg1;
        float longitude1 = PI * (deg1 + 5.0 * min1 / 3.0 ) / 180.0;

        float deg2= round( p1.first );
        float min2= p1.first - deg1;
        float latitude2= PI * (deg2+ 5.0 * min2/ 3.0 ) / 180.0;
        deg2= round( p1.second );
        min2= p1.second - deg1;
        float longitude2= PI * (deg2+ 5.0 * min2/ 3.0 ) / 180.0;

        float q1 = cos( longitude1 - longitude2 );
        float q2 = cos( latitude1 - latitude2 );
        float q3 = cos( latitude1 + latitude2 );
        float dij =( RRR * acos( 0.5*((1.0+q1)*q2 - (1.0-q1)*q3) ) + 1.0);

        return round(dij);
    }
    else if (distance_function==MAN_2D)
    {
        return round(abs(p1.first-p2.first)+abs(p1.second-p2.second));
    }
    else if(distance_function==CEIL_2D)
    {
        float aux1=(p1.first-p2.first)*(p1.first-p2.first);
        float aux2=(p1.second-p2.second)*(p1.second-p2.second);
        float res=sqrt(aux1+aux2);

        return ceil(res);
    }
    else
    {
        cout<<"NOT IMPLEMENTED DISTANCE";
        exit(1);
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
        if(trim(string(buffer))=="NODE_COORD_SECTION" || trim(string(buffer))=="EDGE_WEIGHT_SECTION")
        {
            break;
        }
        keyword=string(strtok(buffer,":"));
        keyword=trim(keyword);

        content=string(strtok(NULL,":"));
        content=trim(content);
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
                representation= LOWER_DIAG_ROW;;
            }
            else if(content=="UPPER_ROW")
            {
                representation=UPPER_ROW;
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
        edges_.push_back(list<pair<int,float>>());
    }

    if(representation==-1)
    {
        std::cout<<"SOMETHIN WENT WRONG\nMISSING FLAG: representation\n";
        exit(1);
    }
    while(1)///READ EDGES
    {
        if(distance_function_==EXPLICIT)
        {
            fin.get();
            if(representation==FULL_MATRIX)
            {
                int aux;
                auto it=edges_.begin();
                for (int i=0;i<number_of_vertexes_;i++)
                {
                    for(int j=0;j<number_of_vertexes_;j++)
                    {
                        fin>>aux;
                        it->push_back({j,aux});
                    }
                    it++;
                }
            }
            else if(representation==UPPER_ROW)
            {
                int aux;
                auto it_i=edges_.begin();
                for (int i=0;i<number_of_vertexes_;i++)
                {
                    auto it_j=it_i;
                    it_j++;
                    it_i->push_back({i,0});
                    for(int j=i+1;j<number_of_vertexes_;j++)
                    {
                        fin>>aux;
                        it_i->push_back({j,aux});
                        it_j->push_back({i,aux});
                        it_j++;
                    }
                    it_i++;
                }
            }
            else if(representation==UPPER_DIAG_ROW)
            {
                int aux;
                auto it_i=edges_.begin();
                for (int i=0;i<number_of_vertexes_;i++)
                {
                    auto it_j=it_i;
                    for(int j=i;j<number_of_vertexes_;j++)
                    {
                        fin>>aux;

                        it_i->push_back({j,aux});
                        if(i!=j)
                        {
                            it_j->push_back({i,aux});
                        }
                        it_j++;
                    }
                    it_i++;
                }
            }
            else if(representation==LOWER_DIAG_ROW)
            {
                int aux;
                auto it_i=edges_.begin();
                for (int i=0;i<number_of_vertexes_;i++)
                {
                    auto it_j=edges_.begin();
                    for(int j=0;j<=i;j++)
                    {

                        fin>>aux;

                        it_i->push_back({j,aux});
                        if(i!=j)
                        {
                            it_j->push_back({i,aux});
                        }
                        it_j++;
                    }
                    it_i++;
                }
            }
            else
            {
                cout<<"NOT IMPLEMENTED\n";
                exit(1);
            }
            break;
        }
        else
        {

            fin.getline(buffer,BUFSIZ);

            ifstream line(trim(string(buffer)));
            if(trim(string(buffer))=="EOF")
            {
                break;
            }
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
    if(distance_function_!=EXPLICIT)
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
    for(list<pair<int,float>> &it:edges_)
    {
        it.sort([](pair<int,float> p1,pair<int,float> p2){return p1.first<p2.first;});
    }
}

Graph::~Graph()
{

}

float Graph::GetCost(int idx1,int idx2)
{
    ////if(idx1>idx2) return GetCost(idx2,idx1);
    
    auto it_i=edges_.begin();
    for(int i=0;i<idx1;i++)
    {
        it_i++;
    }
    auto it_j=it_i->begin();
    if(it_j->first==idx2);
       return it_j->second;
    for(int j=0;j<idx2;j++)
    {
        if(it_j->first==idx2);
            return it_j->second;
        it_j++;
    }
    return 99999999;

}

void Graph::printGraph()
{
    cout<<"Distance: "<<this->distance_function_<<"\n";
    cout<<"N of vertexes "<<this->number_of_vertexes_<<"\n";
    cout<<"EDGES";
    int idx=0;
    cout<<"\n\n";
    for(auto idx_adj:edges_)
    {
        cout<<idx<<":\n";
        for (auto el:idx_adj)
        {
        cout<<"node: "<<el.first<<" distance: "<<el.second<<"\n";
        }
        idx++;
    }
    cout<<"\n\n";

}
