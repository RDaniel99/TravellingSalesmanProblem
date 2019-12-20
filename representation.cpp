#include "representation.h"
#include "randomgenerator.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
using namespace randgen;
//--------------------------------------------------------------------------------------------------
CRepresentation::CRepresentation(const bool generateRandom, const int totalElements)
{
    m_Count = totalElements;

    m_Elements.clear();
    for(int i = 1; i <= totalElements; i++)
        m_Elements.push_back(i);

    if(generateRandom)
    {
        CRandomGenerator::ShuffleRepresentation(m_Elements);
    }
}
//--------------------------------------------------------------------------------------------------
CRepresentation::CRepresentation(const CRepresentation &rep)
{
    m_Count = rep.GetCount();

    m_Elements.clear();

    for(int i = 0; i < m_Count; i++)
        m_Elements[i] = rep.Get(i);
}
//--------------------------------------------------------------------------------------------------
CRepresentation::~CRepresentation()
{

}
//--------------------------------------------------------------------------------------------------
int CRepresentation::Get(const int idx) const
{
    if(!IsIndexValid(idx))
        return -1;

    return m_Elements[idx];
}
//--------------------------------------------------------------------------------------------------
int CRepresentation::GetCount() const
{
    return m_Count;
}
//--------------------------------------------------------------------------------------------------
bool CRepresentation::Swap(const int idx1, const int idx2)
{
    if(!IsIndexValid(idx1) || !IsIndexValid(idx2))
        return false;

    swap(m_Elements[idx1], m_Elements[idx2]);

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CRepresentation::IsEqual(const CRepresentation &rep) const
{
    if(m_Count != rep.GetCount())
        return false;

    for(int i = 0; i < m_Count; i++)
        if(m_Elements[i] != rep.Get(i))
            return false;

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CRepresentation::IsIndexValid(const int idx) const
{
    if(idx < 0 || idx >= m_Count)
        return false;

    return true;
}
//--------------------------------------------------------------------------------------------------
