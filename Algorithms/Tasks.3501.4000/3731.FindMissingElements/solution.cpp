#include <iterator>
#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findMissingElements(std::vector<int> const &nums) const
    {
        const std::set<int> numbers(nums.cbegin(), nums.cend());
        std::vector<int> result;
        result.reserve(nums.size());
        for (auto current = numbers.cbegin(), next = std::next(current, 1); next != numbers.cend(); ++current, ++next)
        {
            for (int number = (*current) + 1; number < (*next); ++number)
                result.emplace_back(number);
        }
        return result;
    }
};

}

namespace FindMissingElementsTask
{

TEST(FindMissingElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3}), solution.findMissingElements({1, 4, 2, 5}));
    ASSERT_EQ(std::vector<int>(), solution.findMissingElements({7, 8, 6, 9}));
    ASSERT_EQ(std::vector<int>({2, 3, 4}), solution.findMissingElements({5, 1}));
}

}