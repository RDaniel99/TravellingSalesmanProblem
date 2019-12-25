#ifndef H_POPULATION
#define H_POPULATION
//--------------------------------------------------------------------------------------------------
#include <vector>
#include "representation.h"
#include "randomgenerator.h"
#include "shared.h"
//--------------------------------------------------------------------------------------------------
class CPopulation
{
public:
    CPopulation(const int total, const int totalPerRep, const bool generateRandom = true, 
                const double mutationRate = DEFAULT_MUTATION_RATIO, 
                const double crossoverRate = DEFAULT_CROSS_RATIO);
    ~CPopulation();

    CRepresentation*    Get(const int idx) const;
    int                 GetCount() const;
    int                 GetGeneration() const;
    bool                AddRep(CRepresentation* rep);
    bool                RemoveByRep(const CRepresentation* rep);
    bool                RemoveByIdx(const int idx);
    
public:
    void                Evolve();
    void                Mutate();
    void                Crossover();
    void                Select();

private:
    bool IsIndexValid(const int idx) const;

private:
    int                             m_GenerationIdx;
    int                             m_Count;
    double                          m_MutationRate;
    double                          m_CrossRate;
    std::vector<CRepresentation*>   m_Elements;
    
};
//--------------------------------------------------------------------------------------------------
#endif // H_POPULATION
//--------------------------------------------------------------------------------------------------
