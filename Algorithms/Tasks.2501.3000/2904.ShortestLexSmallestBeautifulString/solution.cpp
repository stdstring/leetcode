#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string shortestBeautifulSubstring(std::string const &s, int k) const
    {
        const size_t expectedOnes = k;
        // prepare sliding window
        size_t start = moveStart(s, 0);
        size_t onesCount = 0;
        size_t finish = moveFinish(s, start, onesCount, expectedOnes);
        if (onesCount < expectedOnes)
            return "";
        --finish;
        // move sliding window
        std::string bestSubstring(s.substr(start, finish - start + 1));
        for (;;)
        {
            ++start;
            start = moveStart(s, start);
            --onesCount;
            ++finish;
            finish = moveFinish(s, finish, onesCount, expectedOnes);
            if (onesCount < expectedOnes)
                break;
            --finish;
            std::string currentSubstring(s.substr(start, finish - start + 1));
            if ((currentSubstring.size() < bestSubstring.size()) ||
                ((currentSubstring.size() == bestSubstring.size()) && (currentSubstring < bestSubstring)))
                bestSubstring = currentSubstring;
        }
        return bestSubstring;
    }

private:
    [[nodiscard]] size_t moveStart(std::string const &s, size_t start) const
    {
        while ((start < s.size()) && (s[start] == '0'))
            ++start;
        return start;
    }

    [[nodiscard]] size_t moveFinish(std::string const &s, size_t finish, size_t &onesCount, size_t expectedOnes) const
    {
        while ((finish < s.size()) && (onesCount < expectedOnes))
        {
            if (s[finish] == '1')
                ++onesCount;
            ++finish;
        }
        return finish;
    }
};

}

namespace ShortestLexSmallestBeautifulStringTask
{

TEST(ShortestLexSmallestBeautifulStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("11001", solution.shortestBeautifulSubstring("100011001", 3));
    ASSERT_EQ("11", solution.shortestBeautifulSubstring("1011", 2));
    ASSERT_EQ("", solution.shortestBeautifulSubstring("000", 1));
}

}