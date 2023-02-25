#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxEnvelopes(std::vector<std::vector<int>> const &envelopes) const
    {
        std::vector<std::vector<int>> sortedEnvelopes(envelopes);
        std::sort(sortedEnvelopes.begin(), sortedEnvelopes.end(), [](std::vector<int> const &l, std::vector<int> const &r){ return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] > r[1])); });
        // from https://en.wikipedia.org/wiki/Longest_increasing_subsequence
        std::vector<size_t> m(sortedEnvelopes.size() + 1, 0);
        size_t length = 0;
        for (size_t index = 0; index < sortedEnvelopes.size(); ++index)
        {
            size_t left = 1;
            size_t right = length + 1;
            while (left < right)
            {
                const size_t middle = (left + right) / 2;
                if (sortedEnvelopes[m[middle]][1] < sortedEnvelopes[index][1])
                    left = middle + 1;
                else
                    right = middle;
            }
            m[left] = index;
            length = std::max(left, length);
        }
        return static_cast<int>(length);
    }
};

}

namespace RussianDollEnvelopesTask
{

TEST(RussianDollEnvelopesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxEnvelopes({{5, 4}, {6, 4}, {6, 7}, {2, 3}}));
    ASSERT_EQ(1, solution.maxEnvelopes({{1, 1}, {1, 1}, {1, 1}}));
}

}