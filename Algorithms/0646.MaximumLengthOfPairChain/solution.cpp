#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findLongestChain(std::vector<std::vector<int>> const &pairs) const
    {
        std::vector<std::vector<int>> sortedPairs(pairs);
        std::sort(sortedPairs.begin(), sortedPairs.end(), [](std::vector<int> const &left, std::vector<int> const &right){ return left[0] < right[0]; });
        std::vector<size_t> chainLengths(sortedPairs.size(), 0);
        for (size_t index = 0; index < sortedPairs.size(); ++index)
        {
            size_t bestLength = 0;
            for (size_t prevIndex = 0; prevIndex < index; ++prevIndex)
            {
                if (sortedPairs[index - prevIndex - 1][1] < sortedPairs[index][0])
                {
                    bestLength = chainLengths[index - prevIndex - 1];
                    break;
                }
            }
            chainLengths[index] = bestLength + 1;
        }
        return static_cast<int>(*std::max_element(chainLengths.cbegin(), chainLengths.cend()));
    }
};

}

namespace MaximumLengthOfPairChainTask
{

TEST(MaximumLengthOfPairChainTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.findLongestChain({{1, 2}, {2, 3}, {3, 4}}));
}

}