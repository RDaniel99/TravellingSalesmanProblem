#include <random>
#include <ctime>
#include <algorithm>
#include "randomgenerator.h"
//--------------------------------------------------------------------------------------------------
using namespace std;
using namespace randgen;
//--------------------------------------------------------------------------------------------------
int CRandomGenerator::ComputeRandomInteger(int maxInt)
{
    if(maxInt)
        return rand() % maxInt;

    return 0;
}
//--------------------------------------------------------------------------------------------------
double CRandomGenerator::ComputeRandomInInterval(const double left, const double right)
{
    double rd01 = (1.0 * rand()) / double(RAND_MAX);
    double ans = (right - left) * rd01 + left;

    return ans;
}
//--------------------------------------------------------------------------------------------------
bool CRandomGenerator::ShuffleRepresentation(vector<int> &elements, int times)
{
    while(times--)
        random_shuffle(elements.begin(), elements.end());

    return true;
}
//--------------------------------------------------------------------------------------------------
