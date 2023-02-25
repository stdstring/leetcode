#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void reverseString(std::vector<char> &s)
    {
        //std::reverse(s.begin(), s.end());
        size_t first = 0;
        size_t last = s.size() - 1;
        while (first < last)
        {
            std::swap(s[first], s[last]);
            ++first;
            --last;
        }
    }
};

}

namespace ReverseStringTask
{

TEST(ReverseStringTaskTests, Examples)
{
    Solution solution;
    std::vector<char> str1({'h', 'e', 'l', 'l', 'o'});
    solution.reverseString(str1);
    ASSERT_EQ(std::vector<char>({'o', 'l', 'l', 'e', 'h'}), str1);
    std::vector<char> str2({'H', 'a', 'n', 'n', 'a', 'h'});
    solution.reverseString(str2);
    ASSERT_EQ(std::vector<char>({'h', 'a', 'n', 'n', 'a', 'H'}), str2);
}

}