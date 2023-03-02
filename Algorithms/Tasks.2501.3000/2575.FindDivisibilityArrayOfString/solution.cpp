#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> divisibilityArray(std::string const &word, int m) const
    {
        std::vector<int> result(word.size(), 0);
        uint64_t current = 0;
        for (size_t index = 0; index < word.size(); ++index)
        {
            current = 10 * current + (word[index] - '0');
            if ((current % m) == 0)
                result[index] = 1;
            current %= m;
        }
        return result;
    }
};

}

namespace FindDivisibilityArrayOfStringTask
{

TEST(FindDivisibilityArrayOfStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1, 0, 0, 0, 1, 1, 0, 0}), solution.divisibilityArray("998244353", 3));
    ASSERT_EQ(std::vector<int>({0, 1, 0, 1}), solution.divisibilityArray("1010", 10));
}

}