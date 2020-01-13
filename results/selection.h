#ifndef H_SELECTION
#define H_SELECTION

#include "population.h"

class CSelection
{
public:
    CSelection();
    ~CSelection();

    void SetPopulation(CPopulation* pop);
    void SetElitismRatio(double rt);
    void SetCrossRatio(double rt);
    void SetMutationRatio(double rt);

    CPopulation* CreateNewGeneration(CPopulation* pop);

private:
    bool UseElitism(CPopulation* pop);
    bool UseCross(CPopulation* pop);
    bool UseMutation(CPopulation* pop);
    bool UseWheel(CPopulation* pop);

private:
    CPopulation *m_Population;
    double       m_ElitismRatio;
    double       m_CrossRatio;
    double       m_MutationRatio;
};

#endif // H_SELECTION
