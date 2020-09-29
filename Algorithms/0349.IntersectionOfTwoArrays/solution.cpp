#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> intersection(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        std::vector<int> dest;
        std::unordered_set<int> numbers1;
        for (int number : nums1)
            numbers1.insert(number);
        std::unordered_set<int> numbers2;
        for (int number : nums2)
        {
            if (numbers1.count(number) > 0 && numbers2.count(number) == 0)
            {
                dest.push_back(number);
                numbers2.insert(number);
            }
        }
        return dest;
    }
};

}

namespace IntersectionOfTwoArraysTask
{

TEST(IntersectionOfTwoArraysTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2}), solution.intersection({1, 2, 2, 1}, {2, 2}));
    ASSERT_EQ(std::vector<int>({9, 4}), solution.intersection({4, 9, 5}, {9, 4, 9, 8, 4}));
}

}
