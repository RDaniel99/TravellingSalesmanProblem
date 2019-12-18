#ifndef H_REPRESENTATION
#define H_REPRESENTATION
//--------------------------------------------------------------------------------------------------
#include <vector>
#include "shared.h"
//--------------------------------------------------------------------------------------------------
class CRepresentation
{
public:
    CRepresentation(bool generateRandom, int nrOfDimensions, int genesPerDim);
    CRepresentation(const CRepresentation &rep);
    ~CRepresentation();

    int     GetGene(const int dimIdx, const int geneIdx) const;
    int     GetNrOfDimensions() const;
    int     GetGenesPerDimension() const;

    bool    SetGene(const int dimIdx, const int geneIdx, const int geneValue);
    bool    FlipGene(const int dimIdx, const int geneIdx);
    int     ComputeIntForDim(const int dimIdx) const;

private:
    bool    IsDimIdxValid(const int dimIdx) const;
    bool    IsGeneIdxValid(const int geneIdx) const;

private:
    int                                 m_NrOfDimensions;
    int                                 m_GenesPerDimension;
    std::vector<std::vector<int> >      m_Genes;
    /// to-do: check if genes can be bool (if it is worth it)
};
//--------------------------------------------------------------------------------------------------
#endif // H_REPRESENTATION
//--------------------------------------------------------------------------------------------------
