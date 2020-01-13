#include "selection.h"
#include "randomgenerator.h"
#include "shared.h"

using namespace std;
using namespace randgen;

CSelection::CSelection()
{
    m_ElitismRatio  = 0;
    m_CrossRatio    = 0;
    m_MutationRatio = 0;
    m_Population    = 0;
}

CSelection::~CSelection()
{
    if(m_Population)
        delete m_Population;
}

void CSelection::SetPopulation(CPopulation* pop)
{
    m_Population = pop;
}

void CSelection::SetElitismRatio(double rt)
{
    m_ElitismRatio = rt;
}

void CSelection::SetCrossRatio(double rt)
{
    m_CrossRatio = rt;
}

void CSelection::SetMutationRatio(double rt)
{
    m_MutationRatio = rt;
}

CPopulation* CSelection::CreateNewGeneration(CPopulation* pop)
{
    CPopulation* newPop = pop;

    bool ok = true;

    ok = UseMutation(newPop);
    ok = UseCross(newPop);
    ok = UseElitism(newPop);
    ok = UseWheel(newPop);

    if(ok)
        return newPop;

    return 0;
}
