#ifndef H_POPULATION
#define H_POPULATION
//--------------------------------------------------------------------------------------------------
#include <vector>
#include "representation.h"
#include "shared.h"
//--------------------------------------------------------------------------------------------------
class CPopulation
{
public:
    CPopulation(const int total, const int totalPerRep,
                const bool generateRandom = true);

    ~CPopulation();

    CRepresentation*    Get(const int idx) const;
    int                 GetCount() const;
    bool                AddRep(CRepresentation* rep);
    bool                RemoveByRep(const CRepresentation* rep);
    bool                RemoveByIdx(const int idx);

private:
    bool IsIndexValid(const int idx) const;

private:
    int                             m_Count;
    std::vector<CRepresentation*>   m_Elements;
};
//--------------------------------------------------------------------------------------------------
#endif // H_POPULATION
//--------------------------------------------------------------------------------------------------
