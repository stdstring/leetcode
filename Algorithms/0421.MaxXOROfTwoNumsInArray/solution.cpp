#include <bitset>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findMaximumXOR(std::vector<int> const &nums) const
    {
        std::vector<std::vector<int>> trie(1, std::vector<int>(2, 0));
        trie.reserve(BitsCount * nums.size());
        addToTrie(trie, std::bitset<BitsCount>(nums.front()));
        int maxXorValue = 0;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            std::bitset<BitsCount> bits(nums[index]);
            maxXorValue = std::max(maxXorValue, calcMaxXor(trie, bits));
            addToTrie(trie, bits);
        }
        return maxXorValue;
    }

private:
    static constexpr size_t BitsCount = 31;

    void addToTrie(std::vector<std::vector<int>> &trie, std::bitset<BitsCount> const &bits) const
    {
        int currentNode = 0;
        for (size_t index = 0; index < bits.size() - 1; ++index)
        {
            const uint8_t currentBit = bits[bits.size() - 1 - index] ? 1 : 0;
            if (trie[currentNode][currentBit] == 0)
            {
                currentNode = trie[currentNode][currentBit] = static_cast<int>(trie.size());
                trie.emplace_back(2, 0);
            }
            else
                currentNode = trie[currentNode][currentBit];
        }
        const uint8_t lastBit = bits[0] ? 1 : 0;
        trie[currentNode][lastBit] = -1;
    }

    [[nodiscard]] int calcMaxXor(std::vector<std::vector<int>> const &trie, std::bitset<BitsCount> const &bits) const
    {
        int result = 0;
        int currentNode = 0;
        for (size_t index = 0; index < bits.size(); ++index)
        {
            result *= 2;
            const uint8_t currentBit = bits[bits.size() - 1 - index] ? 1 : 0;
            const uint8_t bestBit = currentBit == 0 ? 1 : 0;
            if (trie[currentNode][bestBit] != 0)
            {
                result += 1;
                currentNode = trie[currentNode][bestBit];
            }
            else
                currentNode = trie[currentNode][currentBit];
        }
        return result;
    }
};

}

namespace MaxXOROfTwoNumsInArrayTask
{

TEST(MaxXOROfTwoNumsInArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(28, solution.findMaximumXOR({3, 10, 5, 25, 2, 8}));
    ASSERT_EQ(127, solution.findMaximumXOR({14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70}));
}

}