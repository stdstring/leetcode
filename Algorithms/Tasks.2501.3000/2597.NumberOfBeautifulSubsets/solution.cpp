#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int beautifulSubsets(std::vector<int> const &nums, int k) const
    {
        std::unordered_multiset<int> subset;
        return static_cast<int>(countBeautifulSubsets(nums, k, 0, subset));
    }

private:
    [[nodiscard]] size_t countBeautifulSubsets(std::vector<int> const &nums, int k, size_t fromIndex, std::unordered_multiset<int> &subset) const
    {
        size_t count = 0;
        for (size_t index = fromIndex; index < nums.size(); ++index)
        {
            if (subset.contains(nums[index] - k) || subset.contains(nums[index] + k))
                continue;
            ++count;
            subset.emplace(nums[index]);
            count += countBeautifulSubsets(nums, k, index + 1, subset);
            subset.erase(subset.find(nums[index]));
        }
        return count;
    }
};

}

namespace NumberOfBeautifulSubsetsTask
{

TEST(NumberOfBeautifulSubsetsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.beautifulSubsets({2, 4, 6}, 2));
    ASSERT_EQ(1, solution.beautifulSubsets({1}, 1));
}

}