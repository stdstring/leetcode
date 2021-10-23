#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string getSmallestString(int n, int k) const
    {
        constexpr int maxValue = 25;
        std::string result(n, 'a');
        k -= n;
        size_t index = 0;
        while (k > 0)
        {
            const int value = std::min(maxValue, k);
            result[result.size() - 1 - index] = static_cast<char>('a' + value);
            k -= value;
            ++index;
        }
        return result;
    }
};

}

namespace SmallestStringWithGivenNumValueTask
{

TEST(SmallestStringWithGivenNumValueTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("aay", solution.getSmallestString(3, 27));
    ASSERT_EQ("aaszz", solution.getSmallestString(5, 73));
    ASSERT_EQ("uzzzzzz", solution.getSmallestString(7, 177));
}

}