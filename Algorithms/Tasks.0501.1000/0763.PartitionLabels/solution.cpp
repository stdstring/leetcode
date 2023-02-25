#include <algorithm>
#include <array>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> partitionLabels(std::string const &s) const
    {
        constexpr size_t alphabetSize = 26;
        constexpr size_t firstLetter = 'a';
        std::array<size_t, alphabetSize> lastDigitPos{};
        lastDigitPos.fill(s.size());
        for (size_t index = 0; index < s.size(); ++index)
            lastDigitPos[s[index] - firstLetter] = index;
        std::vector<int> partitionSizes;
        size_t partitionStart = 0;
        size_t partitionFinish = 0;
        while (partitionStart < s.size())
        {
            size_t index = partitionStart;
            partitionFinish = lastDigitPos[s[partitionStart] - firstLetter];
            while (index < partitionFinish)
                partitionFinish = std::max(partitionFinish, lastDigitPos[s[index++] - firstLetter]);
            partitionSizes.push_back(static_cast<int>(partitionFinish - partitionStart + 1));
            partitionStart = partitionFinish + 1;
        }
        return partitionSizes;
    }
};

}

namespace PartitionLabelsTask
{

TEST(PartitionLabelsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({9, 7, 8}), solution.partitionLabels("ababcbacadefegdehijhklij"));
}

}
