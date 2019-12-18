#include "representation.h"
#include "randomgenerator.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
CRepresentation::CRepresentation(bool generateRandom, int nrOfDimensions, int genesPerDim)
{
    m_NrOfDimensions    = nrOfDimensions;
    m_GenesPerDimension = genesPerDim;

    m_Genes.clear();
    m_Genes.resize(nrOfDimensions, vector <int> (genesPerDim));

    if(generateRandom)
    {
        CRandomGenerator randGen;
        for(unsigned int dimIdx = 0; dimIdx < m_NrOfDimensions; dimIdx++)
        {
            for(unsigned int geneIdx = 0; geneIdx < m_GenesPerDimension; geneIdx++)
            {
                m_Genes[dimIdx][geneIdx] = randGen.ComputeRandomGene();
            }
        }
    }
}
//--------------------------------------------------------------------------------------------------
CRepresentation::CRepresentation(const CRepresentation &rep)
{
    m_NrOfDimensions    = rep.GetNrOfDimensions();
    m_GenesPerDimension = rep.GetGenesPerDimension();

    m_Genes.clear();
    m_Genes.resize(m_NrOfDimensions, vector <int> (m_GenesPerDimension));

    for(int dimIdx = 0; dimIdx < m_NrOfDimensions; dimIdx++)
    {
        for(int geneIdx = 0; geneIdx < m_GenesPerDimension; geneIdx++)
        {
            int geneValue = rep.GetGene(dimIdx, geneIdx);
            SetGene(dimIdx, geneIdx, geneValue);
        }
    }
}
//--------------------------------------------------------------------------------------------------
CRepresentation::~CRepresentation()
{

}
//--------------------------------------------------------------------------------------------------
int CRepresentation::GetGene(const int dimIdx, const int geneIdx) const
{
    if(!IsDimIdxValid(dimIdx) || !IsGeneIdxValid(geneIdx))
        return -1;

    return m_Genes[dimIdx][geneIdx];
}
//--------------------------------------------------------------------------------------------------
int CRepresentation::GetNrOfDimensions() const
{
    return m_NrOfDimensions;
}
//--------------------------------------------------------------------------------------------------
int CRepresentation::GetGenesPerDimension() const
{
    return m_GenesPerDimension;
}
//--------------------------------------------------------------------------------------------------
bool CRepresentation::SetGene(const int dimIdx, const int geneIdx, const int geneValue)
{
    if(!IsDimIdxValid(dimIdx) || !IsGeneIdxValid(geneIdx))
        return false;

    m_Genes[dimIdx][geneIdx] = geneValue;
    return true;
}
//--------------------------------------------------------------------------------------------------
bool CRepresentation::IsDimIdxValid(const int dimIdx) const
{
    if(dimIdx < 0 || dimIdx >= m_NrOfDimensions)
        return false;

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CRepresentation::IsGeneIdxValid(const int geneIdx) const
{
    if(geneIdx < 0 || geneIdx >= m_GenesPerDimension)
        return false;

    return true;
}
//--------------------------------------------------------------------------------------------------
bool CRepresentation::FlipGene(const int dimIdx, const int geneIdx)
{
    if(!IsDimIdxValid(dimIdx) || !IsGeneIdxValid(geneIdx))
        return false;

    m_Genes[dimIdx][geneIdx] = 1 - m_Genes[dimIdx][geneIdx];
    return true;
}
//--------------------------------------------------------------------------------------------------
int CRepresentation::ComputeIntForDim(const int dimIdx) const
{
    if(!IsDimIdxValid(dimIdx))
        return -1;

    int x = 0;

    for(unsigned int i = 0; i < m_Genes[dimIdx].size(); i++)
        x = (x << 1) + m_Genes[dimIdx][i];

    return x;
}
//--------------------------------------------------------------------------------------------------
