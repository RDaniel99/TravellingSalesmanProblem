#include "population.h"
#include "randomgenerator.h"

//--------------------------------------------------------------------------------------------------
using namespace std;
using namespace randgen;

//--------------------------------------------------------------------------------------------------
CPopulation::CPopulation(const int total, const int totalPerRep,
             const bool generateRandom = true, const float mutationRate=1,
             const float crossoverRate=1)
{
    m_Count = total;
    m_Elements.clear();
    crossover_Rate=crossoverRate;
    mutation_Rate=mutationRate;

    for(int i = 0; i < total; i++)
        m_Elements.push_back(new CRepresentation(generateRandom, totalPerRep));
}
//--------------------------------------------------------------------------------------------------
CPopulation::~CPopulation()
{

}
//--------------------------------------------------------------------------------------------------
CRepresentation* CPopulation::Get(const int idx) const
{
    if(!IsIndexValid(idx))
        return 0;

    return m_Elements[idx];
}
//--------------------------------------------------------------------------------------------------
int CPopulation::GetCount() const
{
    return m_Count;
}
//--------------------------------------------------------------------------------------------------
bool CPopulation::AddRep(CRepresentation* rep)
{
    if(!rep)
        return false;

    m_Elements.push_back(rep);
    return true;
}
//--------------------------------------------------------------------------------------------------
bool CPopulation::RemoveByRep(const CRepresentation* rep)
{
    for(int i = 0; i < m_Count; i++)
        if(m_Elements[i]->IsEqual(*rep))
            return RemoveByIdx(i);

    return false;
}
//--------------------------------------------------------------------------------------------------
bool CPopulation::RemoveByIdx(const int idx)
{
    if(!IsIndexValid(idx))
        return false;

    for(int i = idx; i < m_Count - 1; i++)
        m_Elements[i] = m_Elements[i + 1];

    m_Count--;
    return true;
}
//--------------------------------------------------------------------------------------------------
bool CPopulation::IsIndexValid(const int idx) const
{
    if(idx < 0 || idx >= m_Count)
        return false;

    return true;
}
//--------------------------------------------------------------------------------------------------
void  CPopulation::Evolve()
{
    Mutate();
    Crossover();
    Select();
    generation++;
    
}

//--------------------------------------------------------------------------------------------------
void  CPopulation::Mutate()
{
    for(auto cromosome:m_Elements)
    {
        for(int i=0;i<cromosome->GetCount();i++)
        {
            if(CRandomGenerator::ComputeRandomInInterval(0,1)<=mutation_Rate)
            {
                cromosome->Set(i,(cromosome->Get(i)+1)%2);
            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
void  CPopulation::Crossover()
{

}

//--------------------------------------------------------------------------------------------------
void  CPopulation::Select()
{

}

//--------------------------------------------------------------------------------------------------