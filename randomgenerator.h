#ifndef H_RANDOMGENERATOR
#define H_RANDOMGENERATOR
//--------------------------------------------------------------------------------------------------
#include <random>
#include <cstdlib>
#include <ctime>
//--------------------------------------------------------------------------------------------------
namespace randgen {
//--------------------------------------------------------------------------------------------------
inline void init()
{
    srand(time(NULL));
}
//--------------------------------------------------------------------------------------------------
class CRandomGenerator
{
public:

    static double   ComputeRandomInInterval(const double left, const double right);
    static int      ComputeRandomInteger(int maxInt = RAND_MAX);

    static bool     ShuffleRepresentation(std::vector<int>& elements, int times = 1);
};
//--------------------------------------------------------------------------------------------------
};
//--------------------------------------------------------------------------------------------------
#endif // H_RANDOMGENERATOR
//--------------------------------------------------------------------------------------------------
