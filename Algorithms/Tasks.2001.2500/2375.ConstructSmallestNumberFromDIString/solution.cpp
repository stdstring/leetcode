#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string smallestNumber(std::string const &pattern) const
    {
        std::string dest;
        int left = 1;
        if (pattern.front() == 'I')
        {
            dest.push_back('1');
            ++left;
        }
        for (size_t index = 0; index < pattern.size();)
        {
            if (pattern[index] == 'D')
            {
                const int count = countSameLetters(pattern, index);
                int right = left + count;
                while (right >= left)
                {
                    dest.push_back(static_cast<char>('0' + right));
                    --right;
                }
                left += (count + 1);
                index += count;
            }
            else
            {
                const size_t maxIndex = pattern.size() - 1;
                if ((index == maxIndex) || (pattern[index + 1] == 'I'))
                {
                    dest.push_back(static_cast<char>('0' + left));
                    ++left;
                }
                ++index;
            }
        }
        return dest;
    }

private:
    [[nodiscard]] int countSameLetters(std::string const &pattern, size_t start) const
    {
        int count = 0;
        while ((start + count < pattern.size()) && (pattern[start + count] == pattern[start]))
            ++count;
        return count;
    }
};

}

namespace ConstructSmallestNumberFromDIStringTask
{

TEST(ConstructSmallestNumberFromDIStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("123549876", solution.smallestNumber("IIIDIDDD"));
    ASSERT_EQ("4321", solution.smallestNumber("DDD"));
}

}