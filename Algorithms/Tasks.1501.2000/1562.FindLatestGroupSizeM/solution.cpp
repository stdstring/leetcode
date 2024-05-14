#include <iterator>
#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findLatestStepViaMap(std::vector<int> const &arr, int m) const
    {
        if (static_cast<int>(arr.size()) == m)
            return static_cast<int>(arr.size());
        std::map<int, int> groups;
        groups.emplace(1, static_cast<int>(arr.size()));
        for (size_t rIndex = 0; rIndex < arr.size(); ++rIndex)
        {
            const size_t index = arr.size() - 1 - rIndex;
            int current = arr[index];
            auto groupIterator = groups.lower_bound(current);
            if ((groupIterator == groups.cend()) || (groupIterator->first > current))
                groupIterator = std::prev(groupIterator, 1);
            const int groupBeforeSize = current - groupIterator->first;
            const int groupAfterSize = groupIterator->second - groupBeforeSize - 1;
            if ((groupBeforeSize == m) || (groupAfterSize == m))
                return static_cast<int>(index);
            groupIterator->second = groupBeforeSize;
            if (groupBeforeSize == 0)
                groups.erase(groupIterator);
            if (groupAfterSize > 0)
                groups.emplace(current + 1, groupAfterSize);
        }
        return -1;
    }

    [[nodiscard]] int findLatestStepViaVector(std::vector<int> const &arr, int m) const
    {
        if (static_cast<int>(arr.size()) == m)
            return static_cast<int>(arr.size());
        std::vector<int> groups(arr.size() + 2, 0);
        int lastStep = -1;
        for (size_t index = 0; index < arr.size(); ++index)
        {
            const int current = arr[index];
            const int leftSize = groups[current - 1];
            const int rightSize = groups[current + 1];
            const int totalSize = leftSize + 1 + rightSize;
            groups[current - leftSize] = groups[current + rightSize] = totalSize;
            if ((leftSize == m) || (rightSize == m))
                lastStep = static_cast<int>(index);
            if (totalSize == m)
                lastStep = static_cast<int>(index + 1);
        }
        return lastStep;
    }
};

}

namespace
{

void checkFindLatestStep(std::vector<int> const &arr, int m, int expectedValue)
{
    constexpr Solution solution;
    ASSERT_EQ(expectedValue, solution.findLatestStepViaMap(arr, m));
    ASSERT_EQ(expectedValue, solution.findLatestStepViaVector(arr, m));
}

}

namespace FindLatestGroupSizeMTask
{

TEST(FindLatestGroupSizeMTaskTests, Examples)
{
    checkFindLatestStep({3, 5, 1, 2, 4}, 1, 4);
    checkFindLatestStep({3, 1, 5, 4, 2}, 2, -1);
}

TEST(FindLatestGroupSizeMTaskTests, FromWrongAnswers)
{
    checkFindLatestStep({1}, 1, 1);
}

}