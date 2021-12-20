#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> minimumAbsDifference(std::vector<int> const &arr) const
    {
        std::vector<int> numbers(arr);
        std::sort(numbers.begin(), numbers.end());
        int minDiff = numbers[1] - numbers[0];
        for (size_t index = 2; index < numbers.size(); ++index)
            minDiff = std::min(minDiff, numbers[index] - numbers[index - 1]);
        std::vector<std::vector<int>> pairs;
        for (size_t index = 1; index < numbers.size(); ++index)
        {
            if (minDiff == (numbers[index] - numbers[index - 1]))
                pairs.push_back(std::vector<int>({numbers[index - 1], numbers[index]}));
        }
        return pairs;
    }
};

}

namespace MinAbsoluteDifferenceTask
{

TEST(MinAbsoluteDifferenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}, {2, 3}, {3, 4}}), solution.minimumAbsDifference({4, 2, 1, 3}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 3}}), solution.minimumAbsDifference({1, 3, 6, 10, 15}));
    ASSERT_EQ(std::vector<std::vector<int>>({{-14, -10}, {19, 23}, {23, 27}}), solution.minimumAbsDifference({3, 8, -10, 23, 19, -4, -14, 27}));
}

}