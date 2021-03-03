#include <stack>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> nextGreaterElement(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        std::stack<int> processedElements;
        std::unordered_map<int, int> nextGreaterElementMap;
        for (int number : nums2)
        {
            while (!processedElements.empty() && (processedElements.top() < number))
            {
                nextGreaterElementMap[processedElements.top()] = number;
                processedElements.pop();
            }
            processedElements.push(number);
            nextGreaterElementMap[number] = -1;
        }
        std::vector<int> dest;
        for (int number : nums1)
            dest.push_back(nextGreaterElementMap[number]);
        return dest;
    }
};

}

namespace NextGreaterElementITask
{

TEST(NextGreaterElementITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({-1, 3, -1}), solution.nextGreaterElement({4, 1, 2}, {1, 3, 4, 2}));
    ASSERT_EQ(std::vector<int>({3, -1}), solution.nextGreaterElement({2, 4}, {1, 2, 3, 4}));
}

}