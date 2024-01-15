#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> colorTheArray(int n, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<int> nums(n, 0);
        std::vector<int> answers(queries.size(), 0);
        int adjacentElementCount = 0;
        for (size_t queryIndex = 0; queryIndex < queries.size(); ++queryIndex)
        {
            const int index = queries[queryIndex][0];
            const int color = queries[queryIndex][1];
            if (nums[index] != color)
            {
                if (index > 0)
                {
                    if ((nums[index - 1] != 0) && (nums[index - 1] == nums[index]))
                        --adjacentElementCount;
                    if ((nums[index - 1] != 0) && (nums[index - 1] == color))
                        ++adjacentElementCount;
                }
                if (index < (n - 1))
                {
                    if ((nums[index + 1] != 0) && (nums[index + 1] == nums[index]))
                        --adjacentElementCount;
                    if ((nums[index + 1] != 0) && (nums[index + 1] == color))
                        ++adjacentElementCount;
                }
            }
            nums[index] = color;
            answers[queryIndex] = adjacentElementCount;
        }
        return answers;
    }
};

}

namespace NumberAdjacentElementsWithSameColorTask
{

TEST(NumberAdjacentElementsWithSameColorTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 1, 0, 2}), solution.colorTheArray(4, {{0, 2}, {1, 2}, {3, 1}, {1, 1}, {2, 1}}));
    ASSERT_EQ(std::vector<int>({0}), solution.colorTheArray(1, {{0, 100000}}));
}

}