#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> replaceNonCoprimes(std::vector<int> const &nums) const
    {
        std::vector<int> result;
        for (const int number : nums)
        {
            int current = number;
            int gcdValue = result.empty() ? 1 : std::gcd(current, result.back());
            while (gcdValue > 1)
            {
                current = (current / std::gcd(current, result.back())) * result.back();
                result.pop_back();
                gcdValue = result.empty() ? 1 : std::gcd(current, result.back());
            }
            result.push_back(current);
        }
        return result;
    }
};

}

namespace ReplaceNonCoprimeNumbersInArrayTask
{

TEST(ReplaceNonCoprimeNumbersInArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({12, 7, 6}), solution.replaceNonCoprimes({6, 4, 3, 2, 7, 6, 2}));
    ASSERT_EQ(std::vector<int>({2, 1, 1, 3}), solution.replaceNonCoprimes({2, 2, 1, 1, 3, 3, 3}));
}

TEST(ReplaceNonCoprimeNumbersInArrayTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({31, 97561}), solution.replaceNonCoprimes({31, 97561, 97561, 97561, 97561, 97561, 97561, 97561, 97561}));
}

}