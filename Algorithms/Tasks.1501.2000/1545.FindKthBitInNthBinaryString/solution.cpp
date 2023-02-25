#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    char findKthBit(int n, int k) const
    {
        if (n == 1)
            return '0';
        std::string prevBinaryString("0");
        for (size_t length = 1; length < static_cast<size_t>(n) - 1; ++length)
        {
            const size_t prevSize = prevBinaryString.size();
            prevBinaryString.push_back('1');
            for (size_t revIndex = 0; revIndex < prevSize; ++revIndex)
                prevBinaryString.push_back(prevBinaryString[prevSize - 1 - revIndex] == '0' ? '1' : '0');
        }
        const size_t index = static_cast<size_t>(k) - 1;
        if (index < prevBinaryString.size())
            return prevBinaryString[index];
        if (index == prevBinaryString.size())
            return '1';
        return prevBinaryString[prevBinaryString.size() - 1 - (index - prevBinaryString.size() - 1)] == '0' ? '1' : '0';
    }
};

}

namespace FindKthBitInNthBinaryStringTask
{

TEST(FindKthBitInNthBinaryStringTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ('0', solution.findKthBit(3, 1));
    ASSERT_EQ('1', solution.findKthBit(4, 11));
    ASSERT_EQ('0', solution.findKthBit(1, 1));
    ASSERT_EQ('1', solution.findKthBit(2, 3));
}

}