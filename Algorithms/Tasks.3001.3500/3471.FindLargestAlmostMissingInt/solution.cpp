#include <algorithm>
#include <map>
#include <ranges>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestInteger(std::vector<int> const &nums, int k) const
    {
        const int n = static_cast<int>(nums.size());
        if (k == n)
            return std::ranges::max(nums);
        std::map<int, bool> numbersMap;
        for (int number : nums)
        {
            auto iterator = numbersMap.find(number);
            if (iterator == numbersMap.cend())
                numbersMap.emplace(number, true);
            else
                iterator->second = false;
        }
        if (k == 1)
        {
            for (auto const &iterator : std::views::reverse(numbersMap))
            {
                if (iterator.second)
                    return iterator.first;
            }
        }
        else
        {
            int maxBorder = std::max(nums.front(), nums.back());
            int minBorder = std::min(nums.front(), nums.back());
            if (numbersMap[maxBorder])
                return maxBorder;
            if (numbersMap[minBorder])
                return minBorder;
        }
        return -1;
    }
};

}

namespace FindLargestAlmostMissingIntTask
{

TEST(FindLargestAlmostMissingIntTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.largestInteger({3, 9, 2, 1, 7}, 3));
    ASSERT_EQ(3, solution.largestInteger({3, 9, 7, 2, 1, 7}, 4));
    ASSERT_EQ(-1, solution.largestInteger({0, 0}, 1));
}

}