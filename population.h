#ifndef H_POPULATION
#define H_POPULATION
//--------------------------------------------------------------------------------------------------
#include <vector>
#include "representation.h"
#include "randomgenerator.h"
#include "graph.h"
#include "graphEvaluator.h"
#include "shared.h"
//--------------------------------------------------------------------------------------------------
class CPopulation
{
public:
    CPopulation(const int total, const int totalPerRep,Graph graph,
             GraphEvaluator evaluator, const bool generateRandom = true, 
                const double mutationRate = DEFAULT_MUTATION_RATIO, 
                const double crossoverRate = DEFAULT_CROSS_RATIO);
    ~CPopulation();

    CRepresentation*    Get(const int idx) const;
    int                 GetCount() const;
    int                 GetPopSize() const;
    int                 GetGeneration() const;
    bool                AddRep(CRepresentation* rep);
    bool                RemoveByRep(const CRepresentation* rep);
    bool                RemoveByIdx(const int idx);
    
public:
    void                Evolve(bool isDestructive);
    void                Mutate(bool isDestructive);
    void                Crossover(bool isDestructive);
    void                Select();


private:
    bool IsIndexValid(const int idx) const;

private:
    Graph                           m_graph;
    GraphEvaluator                  m_evaluator;
    int                             m_GenerationIdx;
    int                             m_Count;
    double                          m_MutationRate;
    double                          m_CrossRate;
    std::vector<CRepresentation*>   m_Elements;
    
};
//--------------------------------------------------------------------------------------------------
#endif // H_POPULATION
//--------------------------------------------------------------------------------------------------
