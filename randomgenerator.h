#ifndef H_RANDOMGENERATOR
#define H_RANDOMGENERATOR
//--------------------------------------------------------------------------------------------------
#include <random>
#include <cstdlib>
//--------------------------------------------------------------------------------------------------
class CRandomGenerator
{
public:
    CRandomGenerator();
    ~CRandomGenerator();

    double  ComputeRandomInInterval(const double left, const double right);
    int     ComputeRandomGene();
    int     ComputeRandomInteger(int maxInt = RAND_MAX);

private:
    int m_Seed;
};
//--------------------------------------------------------------------------------------------------
#endif // H_RANDOMGENERATOR
//--------------------------------------------------------------------------------------------------
