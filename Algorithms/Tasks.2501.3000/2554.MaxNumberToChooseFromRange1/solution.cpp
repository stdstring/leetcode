#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxCount(std::vector<int> const &banned, int n, int maxSum) const
    {
        const std::unordered_set<int> bannedNumbers(banned.cbegin(), banned.cend());
        size_t usedNumbers = 0;
        int sum = 0;
        for (int number = 1; number <= n; ++number)
        {
            if (bannedNumbers.contains(number))
                continue;
            sum += number;
            if (sum > maxSum)
                break;
            ++usedNumbers;
        }
        return static_cast<int>(usedNumbers);
    }
};

}

namespace MaxNumberToChooseFromRange1Task
{

TEST(MaxNumberToChooseFromRange1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxCount({1, 6, 5}, 5, 6));
    ASSERT_EQ(0, solution.maxCount({1, 2, 3, 4, 5, 6, 7}, 8, 1));
    ASSERT_EQ(7, solution.maxCount({11}, 7, 50));
}

}