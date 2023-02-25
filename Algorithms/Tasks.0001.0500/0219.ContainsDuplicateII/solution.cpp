#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool containsNearbyDuplicate(std::vector<int> const &nums, int k) const
    {
        const size_t maxDiff = static_cast<size_t>(k);
        std::unordered_map<int, size_t> itemPositionMap;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            std::unordered_map<int, size_t>::iterator it = itemPositionMap.find(nums[index]);
            if (it == itemPositionMap.end())
                itemPositionMap.emplace(nums[index], index);
            else
            {
                if ((index - it->second) > maxDiff)
                    it->second = index;
                else
                    return true;
            }
        }
        return false;
    }
};

}

namespace ContainsDuplicateIITask
{

TEST(ContainsDuplicateIITask, Example)
{
    const Solution solution;
    ASSERT_EQ(true, solution.containsNearbyDuplicate({1, 2, 3, 1}, 3));
    ASSERT_EQ(true, solution.containsNearbyDuplicate({1, 0, 1, 1}, 1));
    ASSERT_EQ(false, solution.containsNearbyDuplicate({1, 2, 3, 1, 2, 3}, 2));
}

}