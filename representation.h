#ifndef H_REPRESENTATION
#define H_REPRESENTATION
//--------------------------------------------------------------------------------------------------
#include <vector>
#include <list>
#include "shared.h"
//--------------------------------------------------------------------------------------------------
class CRepresentation
{
public:
    CRepresentation(const bool generateRandom, const int totalElements);
    CRepresentation(const CRepresentation &rep);
    ~CRepresentation();

    int  Get(const int idx) const;
    int  GetCount() const;

    bool Set(const int idx, const int value);
    bool IsEqual(const CRepresentation &rep) const;

public:
    static bool CrossOver(CRepresentation &rep1,
                          CRepresentation &rep2);

    static std::list<int> Decode(const CRepresentation &rep);

private:
    bool IsIndexValid(const int idx) const;

private:
    static void UpdateAib(int pos, int N, std::vector<int>& aib);
    static int  QueryAib(int pos, std::vector<int>& aib);


private:
    int                 m_Count;
    std::vector<int>    m_Elements;
};
//--------------------------------------------------------------------------------------------------
#endif // H_REPRESENTATION
//--------------------------------------------------------------------------------------------------
