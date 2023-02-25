#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int garbageCollection(std::vector<std::string> const &garbage, std::vector<int> const &travel) const
    {
        long long mResult = 0;
        long long mFreeTravel = 0;
        long long pResult = 0;
        long long pFreeTravel = 0;
        long long gResult = 0;
        long long gFreeTravel = 0;
        for (size_t index = 0; index < garbage.size(); ++index)
        {
            if (index > 0)
            {
                mFreeTravel += travel[index - 1];
                pFreeTravel += travel[index - 1];
                gFreeTravel += travel[index - 1];
            }
            const long long mCount = std::count(garbage[index].cbegin(), garbage[index].cend(), 'M');
            const long long pCount = std::count(garbage[index].cbegin(), garbage[index].cend(), 'P');
            const long long gCount = std::count(garbage[index].cbegin(), garbage[index].cend(), 'G');
            if (mCount > 0)
            {
                mResult += (mFreeTravel + mCount);
                mFreeTravel = 0;
            }
            if (pCount > 0)
            {
                pResult += (pFreeTravel + pCount);
                pFreeTravel = 0;
            }
            if (gCount > 0)
            {
                gResult += (gFreeTravel + gCount);
                gFreeTravel = 0;
            }
        }
        return static_cast<int>(mResult + pResult + gResult);
    }
};

}

namespace MinTimeAmountToCollectGarbageTask
{

TEST(MinTimeAmountToCollectGarbageTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(21, solution.garbageCollection({"G", "P", "GP", "GG"}, {2, 4, 3}));
    ASSERT_EQ(37, solution.garbageCollection({"MMM", "PGM", "GP"}, {3, 10}));
}

}
