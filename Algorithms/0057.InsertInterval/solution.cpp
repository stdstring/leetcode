#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> insert(std::vector<std::vector<int>> &intervals, std::vector<int> const &newInterval)
    {
        if (intervals.empty())
            return {newInterval};
        std::sort(intervals.begin(), intervals.end(), [](std::vector<int> const &left, std::vector<int> const &right){ return left[0] < right[0]; });
        std::vector<std::vector<int>> dest;
        for (std::vector<int> const &interval : intervals)
        {
            if (interval[1] < newInterval[0])
                dest.push_back(interval);
            else if (interval[0] > newInterval[1])
            {
                if (dest.empty() || dest.back()[1] < newInterval[0])
                    dest.push_back(newInterval);
                dest.push_back(interval);
            }
            else if (interval[0] <= newInterval[0])
                dest.push_back({interval[0], std::max(interval[1], newInterval[1])});
            else
            {
                if (dest.empty() || dest.back()[1] < newInterval[0])
                    dest.push_back({newInterval[0], std::max(interval[1], newInterval[1])});
                else
                    dest.back()[1] = std::max(interval[1], newInterval[1]);
            }
        }
        if (dest.back()[1] < newInterval[0])
            dest.push_back(newInterval);
        return dest;
    }
};

}

namespace InsertIntervalTask
{

TEST(InsertIntervalTask, Examples)
{
    Solution solution;
    std::vector<std::vector<int>> source1({{1, 3},{6, 9}});
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 5}, {6, 9}}), solution.insert(source1, {2, 5}));
    std::vector<std::vector<int>> source2({{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}});
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2}, {3, 10}, {12, 16}}), solution.insert(source2, {4, 8}));
}

TEST(InsertIntervalTask, FromWrongAnswers)
{
    Solution solution;
    std::vector<std::vector<int>> source1({{1, 5}});
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 5}, {6, 8}}), solution.insert(source1, {6, 8}));
    std::vector<std::vector<int>> source2({{0, 5}, {9, 12}});
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 5}, {7, 16}}), solution.insert(source2, {7, 16}));
}

}