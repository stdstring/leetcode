#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long continuousSubarrays(std::vector<int> const &nums) const
    {
        std::map<int, size_t> knownNumbers;
        long long subarraysCount = 0;
        size_t start = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            ++knownNumbers[nums[index]];
            while ((knownNumbers.crbegin()->first - knownNumbers.cbegin()->first) > 2)
                removeNumberFromKnown(knownNumbers, nums[start++]);
            subarraysCount += static_cast<long long>(index - start + 1);
        }
        return subarraysCount;
    }

private:
    void removeNumberFromKnown(std::map<int, size_t> &knownNumbers, int number) const
    {
        const auto iterator = knownNumbers.find(number);
        --iterator->second;
        if (iterator->second == 0)
            knownNumbers.erase(iterator);
    }
};

}

namespace ContinuousSubarraysTask
{

TEST(ContinuousSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.continuousSubarrays({5, 4, 2, 4}));
    ASSERT_EQ(6, solution.continuousSubarrays({1, 2, 3}));
}

}