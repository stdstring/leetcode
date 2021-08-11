#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool canReorderDoubled(std::vector<int> const &arr) const
    {
        std::vector<int> source(arr);
        std::sort(source.begin(), source.end());
        std::unordered_map<int, size_t> knownNumbers;
        for (int number : source)
        {
            if (number >= 0 && number % 2 == 0 && knownNumbers.count(number / 2) == 1 && knownNumbers[number / 2] > 0)
                --knownNumbers[number / 2];
            else if (number < 0 && knownNumbers.count(2 * number) == 1 && knownNumbers[2 * number] > 0)
                --knownNumbers[2 * number];
            else
                knownNumbers[number] += 1;
        }
        return std::all_of(knownNumbers.cbegin(), knownNumbers.cend(), [](auto const& entry) { return entry.second == 0; });
    }
};

}

namespace ArrayOfDoubledPairsTask
{

TEST(ArrayOfDoubledPairsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.canReorderDoubled({3, 1, 3, 6}));
    ASSERT_EQ(false, solution.canReorderDoubled({2, 1, 2, 6}));
    ASSERT_EQ(true, solution.canReorderDoubled({4, -2, 2, -4}));
    ASSERT_EQ(false, solution.canReorderDoubled({1, 2, 4, 16, 8, 4}));
}

TEST(ArrayOfDoubledPairsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canReorderDoubled({0, 0}));
    ASSERT_EQ(true, solution.canReorderDoubled({-6, -3}));
    ASSERT_EQ(true, solution.canReorderDoubled({2, 1, 2, 1, 1, 1, 2, 2}));
}

}