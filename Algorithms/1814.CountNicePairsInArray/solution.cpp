#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countNicePairs(std::vector<int> const &nums) const
    {
        const int modValue = 1000000007;
        std::unordered_map<int, size_t> valueCountMap;
        for (int number : nums)
            ++valueCountMap[number - reverseNumber(number)];
        size_t totalPairsCount = 0;
        for (auto const &entry : valueCountMap)
        {
            const size_t pairsCount = ((1 + entry.second - 1) * (entry.second - 1) / 2) % modValue;
            totalPairsCount = (totalPairsCount + pairsCount) % modValue;
        }
        return static_cast<int>(totalPairsCount);
    }

private:
    int reverseNumber(int number) const
    {
        int result = 0;
        while (number != 0)
        {
            result = result * 10 + (number % 10);
            number /= 10;
        }
        return result;
    }
};

}

namespace CountNicePairsInArrayTask
{

TEST(CountNicePairsInArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.countNicePairs({42, 11, 1, 97}));
    ASSERT_EQ(4, solution.countNicePairs({13, 10, 35, 24, 76}));
}

}