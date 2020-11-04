#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numDecodings(std::string const &s) const
    {
        std::vector<size_t> storage;
        // init
        storage.push_back(1);
        for (size_t index = 0; index < s.size(); ++index)
            storage.push_back(0);
        // process
        for (size_t index = 0; index < s.size(); ++index)
        {
            if (s[index] == '0')
                continue;
            // process 1-digit code
            storage[index + 1] += storage[index];
            // process 2-digit code
            if (canFormTwoDigitsCode(s, index))
                storage[index + 2] += storage[index];
        }
        return static_cast<int>(storage[s.size()]);
    }

private:
    bool canFormTwoDigitsCode(std::string const &s, size_t index) const
    {
        if (index == (s.size() - 1))
            return false;
        return (s[index] == '1') || (s[index] == '2' && s[index + 1] >= '0' && s[index + 1] <= '6');
    }
};

}

namespace DecodeWaysTask
{

TEST(DecodeWaysTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.numDecodings("12"));
    ASSERT_EQ(3, solution.numDecodings("226"));
}

TEST(DecodeWaysTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.numDecodings("0"));
    ASSERT_EQ(1, solution.numDecodings("10"));
    ASSERT_EQ(3, solution.numDecodings("12120"));
}

}