#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numFriendRequests(std::vector<int> const &ages) const
    {
        std::vector<int> sortedAges(ages);
        std::sort(sortedAges.begin(), sortedAges.end());
        size_t requestCount = 0;
        size_t start = 0;
        // 14 / 2 + 7 == 14
        // 15 / 2 + 7 == 14.5
        size_t tooYoungCount = 0;
        for (size_t index = 0; (index < sortedAges.size()) && (sortedAges[index] < 14); ++index)
            ++tooYoungCount;
        for (size_t end = tooYoungCount; end < sortedAges.size();)
        {
            const int leftBorder = sortedAges[end] / 2 + 7;
            if (sortedAges[start] <= leftBorder)
                ++(start < end ? start : end);
            else
            {
                const size_t sameAgesCount = countSameValues(sortedAges, end);
                requestCount += sameAgesCount * (end - start);
                requestCount += sameAgesCount * (sameAgesCount - 1);
                end += sameAgesCount;
            }
        }
        return static_cast<int>(requestCount);
    }

private:
    [[nodiscard]] size_t countSameValues(std::vector<int> const &numbers, size_t start) const
    {
        size_t count = 0;
        for (size_t index = start; (index < numbers.size()) && (numbers[start] == numbers[index]); ++index)
            ++count;
        return count;
    }
};

}

namespace FriendsOfAppropriateAgesTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.numFriendRequests({16, 16}));
    ASSERT_EQ(2, solution.numFriendRequests({16, 17, 18}));
    ASSERT_EQ(3, solution.numFriendRequests({20, 30, 100, 110, 120}));
}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numFriendRequests({101, 56, 69, 48, 30}));
    ASSERT_EQ(2, solution.numFriendRequests({118, 14, 7, 63, 103}));
}

}
