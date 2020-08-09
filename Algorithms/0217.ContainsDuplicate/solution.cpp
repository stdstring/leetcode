#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool containsDuplicate(std::vector<int> const &nums) const
    {
        std::unordered_set<int> numberSet;
        for(int number : nums)
        {
            if (numberSet.count(number) > 0)
                return true;
            numberSet.emplace(number);
        }
        return false;
    }
};

}

namespace ContainsDuplicateTask
{

TEST(ContainsDuplicateTaskTests, Example)
{
    const Solution solution;
    ASSERT_EQ(true, solution.containsDuplicate({1, 2, 3, 1}));
    ASSERT_EQ(false, solution.containsDuplicate({1, 2, 3, 4}));
    ASSERT_EQ(true, solution.containsDuplicate({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}));
}

}