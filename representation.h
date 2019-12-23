#ifndef H_REPRESENTATION
#define H_REPRESENTATION
//--------------------------------------------------------------------------------------------------
#include <vector>
#include "shared.h"
//--------------------------------------------------------------------------------------------------
class CRepresentation
{
public:
    CRepresentation(const bool generateRandom, const int totalElements);
    CRepresentation(const CRepresentation &rep);
    ~CRepresentation();

    int         Get(const int idx) const;
    int         GetCount() const;

    bool        Set(const int idx, const int value);
    bool        Swap(const int idx1, const int idx2);
    bool        IsEqual(const CRepresentation &rep) const;

    static bool CrossOver(CRepresentation &rep1,
                          CRepresentation &rep2);
private:
    bool    IsIndexValid(const int idx) const;

private:
    int                 m_Count;
    std::vector<int>    m_Elements;
};
//--------------------------------------------------------------------------------------------------
#endif // H_REPRESENTATION
//--------------------------------------------------------------------------------------------------
