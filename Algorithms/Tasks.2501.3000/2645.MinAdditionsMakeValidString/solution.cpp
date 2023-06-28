#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int addMinimum(std::string const &word) const
    {
        constexpr int completePortionCount = 3;
        int additionCount = 0;
        int portionCount = 0;
        char lastPortionChar = 0;
        for (const char ch : word)
        {
            if (lastPortionChar < ch)
            {
                lastPortionChar = ch;
                ++portionCount;
            }
            else
            {
                additionCount += (completePortionCount - portionCount);
                lastPortionChar = ch;
                portionCount = 1;
            }
        }
        additionCount += (completePortionCount - portionCount);
        return additionCount;
    }
};

}

namespace MinAdditionsMakeValidStringTask
{

TEST(MinAdditionsMakeValidStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.addMinimum("b"));
    ASSERT_EQ(6, solution.addMinimum("aaa"));
    ASSERT_EQ(0, solution.addMinimum("abc"));
}

TEST(MinAdditionsMakeValidStringTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.addMinimum("aaaabb"));
}

}