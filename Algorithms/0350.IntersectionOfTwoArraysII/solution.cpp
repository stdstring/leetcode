#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> intersect(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        std::vector<int> dest;
        std::unordered_map<int, int> numbers;
        for (int number: nums1)
        {
            std::unordered_map<int, int>::iterator it = numbers.find(number);
            if (it == numbers.end())
                numbers.emplace(number, 1);
            else
                ++it->second;
        }
        for (int number: nums2)
        {
            std::unordered_map<int, int>::iterator it = numbers.find(number);
            if (it != numbers.end())
            {
                dest.push_back(number);
                --it->second;
                if (it->second == 0)
                    numbers.erase(it);
            }
        }
        return dest;
    }
};

}

namespace IntersectionOfTwoArraysIITask
{

TEST(IntersectionOfTwoArraysIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 2}), solution.intersect({1, 2, 2, 1}, {2, 2}));
    ASSERT_EQ(std::vector<int>({9, 4}), solution.intersect({4, 9, 5}, {9, 4, 9, 8, 4}));
}

}