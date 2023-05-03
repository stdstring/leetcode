#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> findDifference(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        const std::set<int> numbers1(nums1.cbegin(), nums1.cend());
        const std::set<int> numbers2(nums2.cbegin(), nums2.cend());
        std::vector<int> diff1(createDiff(numbers1, numbers2));
        std::vector<int> diff2(createDiff(numbers2, numbers1));
        return {diff1, diff2};
    }

private:
    [[nodiscard]] std::vector<int> createDiff(std::set<int> const &numbers, std::set<int> const &otherNumbers) const
    {
        std::vector<int> diff;
        for (int number : numbers)
        {
            if (otherNumbers.count(number) == 0)
                diff.emplace_back(number);
        }
        return diff;
    }
};

}

namespace FindDifferenceTwoArraysTask
{

TEST(FindDifferenceTwoArraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 3}, {4, 6}}), solution.findDifference({1, 2, 3}, {2, 4, 6}));
    ASSERT_EQ(std::vector<std::vector<int>>({{3}, {}}), solution.findDifference({1, 2, 3, 3}, {1, 1, 2, 2}));
}

}