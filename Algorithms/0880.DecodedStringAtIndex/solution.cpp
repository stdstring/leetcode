#include <stack>
#include <string>

#include "gtest/gtest.h"

namespace
{

struct PrefixData
{
    PrefixData(size_t currentSize, size_t prevSize, size_t index) : CurrentSize(currentSize), PrevSize(prevSize), Index(index)
    {
    }

    size_t CurrentSize;
    size_t PrevSize;
    size_t Index;
};

class Solution
{
public:
    std::string decodeAtIndex(std::string const &s, int k) const
    {
        const size_t charIndex = static_cast<size_t>(k) - 1;
        // size, prev_size, start_pos tuple
        std::stack<PrefixData> prefixStack;
        size_t index = 0;
        while (prefixStack.empty() || (prefixStack.top().CurrentSize <= charIndex))
        {
            size_t prevSize = prefixStack.empty() ? 0 : prefixStack.top().CurrentSize;
            if (std::isdigit(s[index]))
            {
                const size_t factor = static_cast<size_t>(s[index]) - '0';
                prefixStack.emplace(prevSize * factor, prevSize, index);
                ++index;
            }
            else
            {
                size_t length = 0;
                while ((index + length < s.size()) && std::isalpha(s[index + length]))
                    ++length;
                prefixStack.emplace(prevSize + length, prevSize, index);
                index += length;
            }
        }
        return searchChar(s, charIndex, prefixStack);
    }

private:
    std::string searchChar(std::string const &s, size_t charIndex, std::stack<PrefixData> &prefixStack) const
    {
        while (prefixStack.top().PrevSize > charIndex)
            prefixStack.pop();
        if (std::isdigit(s[prefixStack.top().Index]))
        {
            charIndex %= prefixStack.top().PrevSize;
            prefixStack.pop();
            return searchChar(s, charIndex, prefixStack);
        }
        return s.substr(prefixStack.top().Index + (charIndex - prefixStack.top().PrevSize), 1);
    }
};

}

namespace DecodedStringAtIndexTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("o", solution.decodeAtIndex("leet2code3", 10));
    ASSERT_EQ("h", solution.decodeAtIndex("ha22", 5));
    ASSERT_EQ("a", solution.decodeAtIndex("a2345678999999999999999", 1));
}

}