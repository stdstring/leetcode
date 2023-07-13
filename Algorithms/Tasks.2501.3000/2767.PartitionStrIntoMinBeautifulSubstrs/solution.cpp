#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumBeautifulSubstrings(std::string const &s) const
    {
        const int maxNumber = (1 << (s.size() + 1)) - 1;
        std::vector<std::string> powers5;
        for (int number = 1; number <= maxNumber; number *= 5)
            powers5.emplace_back(toBinary(number));
        std::vector<int> dp(s.size() + 1, INT_MAX);
        for (std::string const &power5 : powers5)
        {
            if (s.compare(0, power5.size(), power5) == 0)
                dp[power5.size()] = 1;
        }
        for (size_t size = 1; size < dp.size(); ++size)
        {
            if (dp[size] == INT_MAX)
                continue;
            for (std::string const &power5 : powers5)
            {
                if ((size + power5.size()) > s.size())
                    break;
                if (s.compare(size, power5.size(), power5) == 0)
                    dp[size + power5.size()] = std::min(dp[size + power5.size()], dp[size] + 1);
            }
        }
        return dp.back() == INT_MAX ? -1 : dp.back();
    }

private:
    [[nodiscard]] std::string toBinary(int number) const
    {
        std::string binary;
        while (number > 0)
        {
            binary.push_back((number % 2) == 0 ? '0' : '1');
            number /= 2;
        }
        std::ranges::reverse(binary);
        return binary;
    }
};

}

namespace PartitionStrIntoMinBeautifulSubstrsTask
{

TEST(PartitionStrIntoMinBeautifulSubstrsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumBeautifulSubstrings("1011"));
    ASSERT_EQ(3, solution.minimumBeautifulSubstrings("111"));
    ASSERT_EQ(-1, solution.minimumBeautifulSubstrings("0"));
}

}