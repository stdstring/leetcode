#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long numberOfWays(std::string const &s) const
    {
        long long countPrefix0 = 0;
        long long countPrefix1 = 0;
        long long countPrefix10 = 0;
        long long countPrefix01 = 0;
        long long totalCount = 0;
        for (const char ch : s)
        {
            switch (ch)
            {
            case '0':
                totalCount += countPrefix01;
                countPrefix10 += countPrefix1;
                ++countPrefix0;
                break;
            case '1':
                totalCount += countPrefix10;
                countPrefix01 += countPrefix0;
                ++countPrefix1;
                break;
            default:
                throw std::logic_error("Bad data");
            }
        }
        return totalCount;
    }
};

}

namespace NumberWaysSelectBuildingsTask
{

TEST(NumberWaysSelectBuildingsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.numberOfWays("001101"));
    ASSERT_EQ(0, solution.numberOfWays("11100"));
}

}