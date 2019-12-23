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
    CPopulation(const int total, const int totalPerRep, const bool generateRandom = true, const float mutationRate=1,const float crossoverRate=1);
    ~CPopulation();

    CRepresentation*    Get(const int idx) const;
    int                 GetCount() const;
    bool                AddRep(CRepresentation* rep);
    bool                RemoveByRep(const CRepresentation* rep);
    bool                RemoveByIdx(const int idx);
    void                Evolve();
    void                Mutate();
    void                Crossover();
    void                Select();

private:
    bool IsIndexValid(const int idx) const;

private:
    int                             generation;
    int                             m_Count;
    float                           mutation_Rate;
    float                           crossover_Rate;
    std::vector<CRepresentation*>   m_Elements;
    
};
//--------------------------------------------------------------------------------------------------
#endif // H_POPULATION
//--------------------------------------------------------------------------------------------------
