#include <random>
#include <ctime>
#include "randomgenerator.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
//--------------------------------------------------------------------------------------------------
CRandomGenerator::CRandomGenerator()
{
    srand(time(NULL));

    m_Seed = rand();
}
//--------------------------------------------------------------------------------------------------
CRandomGenerator::~CRandomGenerator()
{

}
//--------------------------------------------------------------------------------------------------
int CRandomGenerator::ComputeRandomInteger(int maxInt)
{
    int ans = m_Seed % maxInt;
    m_Seed = rand();

    return ans;
}
//--------------------------------------------------------------------------------------------------
int CRandomGenerator::ComputeRandomGene()
{
    return ComputeRandomInteger(2);
}
//--------------------------------------------------------------------------------------------------
double CRandomGenerator::ComputeRandomInInterval(const double left, const double right)
{
    double rd01 = (1.0 * m_Seed) / double(RAND_MAX);
    double ans = (right - left) * rd01 + left;

    m_Seed = rand();

    return ans;
}
//--------------------------------------------------------------------------------------------------
