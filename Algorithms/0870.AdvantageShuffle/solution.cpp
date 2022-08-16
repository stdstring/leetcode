#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> advantageCount(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        std::multiset<int> nums1Set;
        for (int number : nums1)
            nums1Set.insert(number);
        std::vector<int> result(nums1.size(), 0);
        for (size_t index = 0; index < nums2.size(); ++index)
        {
            auto upperBound = nums1Set.upper_bound(nums2[index]);
            auto iterator = upperBound == nums1Set.end() ? nums1Set.begin() : upperBound;
            result[index] = *iterator;
            nums1Set.erase(iterator);
        }
        return result;
    }
};

}

namespace AdvantageShuffleTask
{

TEST(AdvantageShuffleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 11, 7, 15}), solution.advantageCount({2, 7, 11, 15}, {1, 10, 4, 11}));
    ASSERT_EQ(std::vector<int>({24, 32, 8, 12}), solution.advantageCount({12, 24, 8, 32}, {13, 25, 32, 11}));
}

}
