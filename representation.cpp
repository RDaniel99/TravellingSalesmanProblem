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

    if(generateRandom)
    {
        int N = totalElements;
        while(N--)
            m_Elements.push_back(CRandomGenerator::ComputeRandomInteger(N + 1) + 1);
    }
    else
    {
        for(int i = 1; i <= totalElements; i++)
            m_Elements.push_back(i);
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
bool CRepresentation::Set(const int idx, const int value)
{
    if(!IsIndexValid(idx))
        return 0;

    m_Elements[idx] = value;

    return true;
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
bool CRepresentation::CrossOver(CRepresentation &rep1, CRepresentation &rep2)
{
    if(rep1.GetCount() != rep2.GetCount())
        return false;

    int maxCross = rep1.GetCount() - 1;
    while(maxCross)
    {
        int idxCross = CRandomGenerator::ComputeRandomInteger(maxCross);
        bool flag = false;

        for(int i = idxCross + 1; i < rep1.GetCount(); i++)
        {
            int tmp1 = rep1.Get(i);
            int tmp2 = rep2.Get(i);

            if(flag || tmp1 != tmp2)
            {
                flag = true;

                rep1.Set(i, tmp2);
                rep2.Set(i, tmp1);
            }
        }

        if(flag)
            return true;

        maxCross--;
    }

    return false;
}
//--------------------------------------------------------------------------------------------------
vector<int> CRepresentation::Convert(const CRepresentation &rep)
{
    vector<int> path;
    vector<int> aib;

    int N = rep.GetCount();

    path.clear();

    aib.clear();
    aib.resize(N + 2);

    int pwAux = 1;
    while(pwAux <= N)
        pwAux <<= 1;

    pwAux >>= 1;

    for(int i = 0; i < N; i++)
    {
        int need = rep.Get(i);
        int pw = pwAux;
        int pos = 0;

        while(pw)
        {
            if(pos + pw <= N)
                if(pos + pw - CRepresentation::QueryAib(pos + pw, aib) < need)
                    pos += pw;

            pw >>= 1;
        }

        path.push_back(pos + 1);
        CRepresentation::UpdateAib(pos + 1, N, aib);
    }

    return path;
}
//--------------------------------------------------------------------------------------------------
void CRepresentation::UpdateAib(int pos, int N, vector<int> &aib)
{
    for(;pos <= N; pos += pos & (-pos))
        aib[pos]++;
}
//--------------------------------------------------------------------------------------------------
int CRepresentation::QueryAib(int pos, std::vector<int>& aib)
{
    int ans = 0;

    for(;pos; pos -= pos & (-pos))
        ans += aib[pos];

    return ans;
}
//--------------------------------------------------------------------------------------------------
