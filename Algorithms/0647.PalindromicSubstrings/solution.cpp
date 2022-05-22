#include <queue>
#include <string>
#include <utility>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countSubstrings(std::string const &s) const
    {
        const size_t indexMax = s.size() - 1;
        size_t count = 0;
        std::queue<std::pair<size_t, size_t>> palindromes;
        for (size_t index = 0; index < s.size(); ++index)
            palindromes.emplace(index, 1);
        while (!palindromes.empty())
        {
            ++count;
            const size_t currentIndex = palindromes.front().first;
            const size_t currentSize = palindromes.front().second;
            palindromes.pop();
            if ((currentSize == 1) &&
                (currentIndex < indexMax) &&
                (s[currentIndex] == s[currentIndex + 1]))
                palindromes.emplace(currentIndex, 2);
            if ((currentIndex > 0) &&
                ((currentIndex + currentSize) <= indexMax) &&
                (s[currentIndex - 1] == s[currentIndex + currentSize]))
                palindromes.emplace(currentIndex - 1, currentSize + 2);
        }
        return static_cast<int>(count);
    }
};

}

namespace PalindromicSubstringsTask
{

TEST(PalindromicSubstringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.countSubstrings("abc"));
    ASSERT_EQ(6, solution.countSubstrings("aaa"));
}

}