#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int longestConsecutive(std::vector<int> const &nums) const
    {
        std::unordered_map<int, std::pair<int, int>> sequencesMap;
        int longestSequenceSize = 0;
        for (int number : nums)
        {
            if (sequencesMap.count(number) == 1)
                continue;
            auto leftRange = sequencesMap.find(number - 1);
            if (leftRange != sequencesMap.cend() && leftRange->second.second > number)
                continue;
            auto rightRange = sequencesMap.find(number + 1);
            if (rightRange != sequencesMap.cend() && rightRange->second.first < number)
                continue;
            std::pair<int, int> range(leftRange == sequencesMap.cend() ? number : leftRange->second.first, rightRange == sequencesMap.cend() ? number : rightRange->second.second);
            if (leftRange != sequencesMap.cend())
            {
                std::pair<int, int> leftRangeData = leftRange->second;
                sequencesMap.erase(leftRangeData.first);
                sequencesMap.erase(leftRangeData.second);
            }
            if (rightRange != sequencesMap.cend())
            {
                std::pair<int, int> rightRangeData = rightRange->second;
                sequencesMap.erase(rightRangeData.first);
                sequencesMap.erase(rightRangeData.second);
            }
            sequencesMap.emplace(range.first, range);
            sequencesMap.emplace(range.second, range);
            longestSequenceSize = std::max(longestSequenceSize, range.second - range.first + 1);
        }
        return longestSequenceSize;
    }
};

}

namespace LongestConsecutiveSequenceTask
{

TEST(LongestConsecutiveSequenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.longestConsecutive({100, 4, 200, 1, 3, 2}));
    ASSERT_EQ(9, solution.longestConsecutive({0, 3, 7, 2, 5, 8, 4, 6, 0, 1}));
}

TEST(LongestConsecutiveSequenceTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(3, solution.longestConsecutive({1, 2, 0, 1}));
}

}