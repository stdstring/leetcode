#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> lexicographicallySmallestArray(std::vector<int> const &nums, int limit) const
    {
        std::vector<size_t> indexes(nums.size(), 0);
        std::iota(indexes.begin(), indexes.end(), 0);
        std::ranges::sort(indexes, [&nums](size_t l, size_t r) { return nums[l] < nums[r]; });
        std::vector<int> result(nums.size(), 0);
        std::vector<size_t>::const_iterator start = indexes.cbegin();
        for (std::vector<size_t>::const_iterator current = std::next(indexes.cbegin(), 1); current != indexes.cend(); ++current)
        {
            std::vector<size_t>::const_iterator prev = std::prev(current, 1);
            if ((nums[*current] - nums[*prev]) > limit)
            {
                processGroup(nums, start, current, result);
                start = current;
            }
        }
        processGroup(nums, start, indexes.cend(), result);
        return result;
    }

private:
    void processGroup(std::vector<int> const &nums,
                      std::vector<size_t>::const_iterator start,
                      std::vector<size_t>::const_iterator end,
                      std::vector<int> &result) const
    {
        std::vector<size_t> group(start, end);
        std::ranges::sort(group);
        for (size_t index = 0; index < group.size(); ++index, ++start)
            result[group[index]] = nums[*start];
    }
};

}

namespace MakeLexSmallestArrayBySwappingElementsTask
{

TEST(MakeLexSmallestArrayBySwappingElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 3, 5, 8, 9}), solution.lexicographicallySmallestArray({1, 5, 3, 9, 8}, 2));
    ASSERT_EQ(std::vector<int>({1, 6, 7, 18, 1, 2}), solution.lexicographicallySmallestArray({1, 7, 6, 18, 2, 1}, 3));
    ASSERT_EQ(std::vector<int>({1, 7, 28, 19, 10}), solution.lexicographicallySmallestArray({1, 7, 28, 19, 10}, 3));
}

TEST(MakeLexSmallestArrayBySwappingElementsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3}), solution.lexicographicallySmallestArray({2, 3, 1}, 1));
}

TEST(MakeLexSmallestArrayBySwappingElementsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 56, 34, 84, 60, 62, 38, 76, 49, 39}),
              solution.lexicographicallySmallestArray({1, 60, 34, 84, 62, 56, 39, 76, 49, 38}, 4));
}

}