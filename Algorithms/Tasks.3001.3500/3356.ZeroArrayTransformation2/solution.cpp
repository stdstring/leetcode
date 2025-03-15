#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minZeroArray(std::vector<int> const &nums, std::vector<std::vector<int>> const &queries) const
    {
        if (std::ranges::all_of(nums, [](int value) { return value == 0; }))
            return 0;
        if (!canZeroArray(nums, queries, queries.size()))
            return -1;
        if (canZeroArray(nums, queries, 1))
            return 1;
        size_t left = 1;
        size_t right = queries.size();
        while (left < right)
        {
            size_t middle = (left + right) / 2;
            if (canZeroArray(nums, queries, middle))
                right = middle;
            else
                left = middle + 1;
        }
        return static_cast<int>(left);
    }

private:
    [[nodiscard]] bool canZeroArray(std::vector<int> const &nums, std::vector<std::vector<int>> const &queries, size_t usedQueries) const
    {
        std::vector<int> changes(nums.size() + 1, 0);
        for (size_t index = 0; index < usedQueries; ++index)
        {
            const int start = queries[index][0];
            const int end = queries[index][1] + 1;
            const int delta = queries[index][2];
            changes[start] += delta;
            changes[end] -= delta;
        }
        int current = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            current += changes[index];
            if (nums[index] > current)
                return false;
        }
        return true;
    }
};

}

namespace ZeroArrayTransformation2Task
{

TEST(ZeroArrayTransformation2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minZeroArray({2, 0, 2}, {{0, 2, 1}, {0, 2, 1}, {1, 1, 3}}));
    ASSERT_EQ(-1, solution.minZeroArray({4, 3, 2, 1}, {{1, 3, 2}, {0, 2, 1}}));
}

TEST(ZeroArrayTransformation2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minZeroArray({0}, {{0, 0, 2}, {0, 0, 4}, {0, 0, 4}, {0, 0, 3}, {0, 0, 5}}));
}

}