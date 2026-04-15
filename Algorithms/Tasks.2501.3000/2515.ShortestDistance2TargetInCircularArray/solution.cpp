#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int closestTarget(std::vector<std::string> const &words, std::string const &target, int startIndex) const
    {
        const size_t n = words.size();
        size_t shortestDistance = INT_MAX;
        for (size_t index = 0; index < n; ++index)
        {
            if (words[index] != target)
                continue;
            shortestDistance = std::min(shortestDistance, (n + startIndex - index) % n);
            shortestDistance = std::min(shortestDistance, (n + index - startIndex) % n);
        }
        return shortestDistance == INT_MAX ? -1 : static_cast<int>(shortestDistance);
    }
};

}

namespace ShortestDistance2TargetInCircularArrayTask
{

TEST(ShortestDistance2TargetInCircularArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.closestTarget({"hello", "i", "am", "leetcode", "hello"}, "hello", 1));
    ASSERT_EQ(1, solution.closestTarget({"a", "b", "leetcode"}, "leetcode", 0));
    ASSERT_EQ(-1, solution.closestTarget({"i", "eat", "leetcode"}, "ate", 0));
}

}