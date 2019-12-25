#include "population.h"
#include "randomgenerator.h"

//--------------------------------------------------------------------------------------------------
using namespace std;
using namespace randgen;

//--------------------------------------------------------------------------------------------------
CPopulation::CPopulation(const int total, 
             const int totalPerRep,
             const bool generateRandom, 
             const double mutationRate,
             const double crossoverRate)
{
    m_GenerationIdx = 0;
    m_Count = total;
    m_Elements.clear();
    m_CrossRate = crossoverRate;
    m_MutationRate = mutationRate;

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
int CPopulation::GetGeneration() const
{
    return m_GenerationIdx;
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
    m_GenerationIdx++;
}

//--------------------------------------------------------------------------------------------------
void  CPopulation::Mutate()
{
    for(auto cromosome:m_Elements)
        for(int i = 0;i < cromosome->GetCount(); i++)
            if(CRandomGenerator::ComputeRandomInInterval(0, 1) <= m_MutationRate)
            {
                int newValue = CRandomGenerator::ComputeRandomInteger(cromosome->GetCount() - i);
                cromosome->Set(i, newValue);
            }
}

//--------------------------------------------------------------------------------------------------
void  CPopulation::Crossover()
{
    for(unsigned int i = 0; i < m_Elements.size(); i++)
        for(unsigned int j = i + 1; j < m_Elements.size(); j++)
            if(CRandomGenerator::ComputeRandomInInterval(0, 1) <= m_CrossRate)
                CRepresentation::CrossOver(*m_Elements[i], *m_Elements[j]);
}

//--------------------------------------------------------------------------------------------------
void  CPopulation::Select()
{

}

//--------------------------------------------------------------------------------------------------