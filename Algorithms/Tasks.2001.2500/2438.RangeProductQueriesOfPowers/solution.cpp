#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> productQueries(int n, std::vector<std::vector<int>> const &queries) const
    {
        constexpr long long modValue = 1000000007;
        const long long number = n;
        std::vector<long long> powers;
        long long power = 1;
        while (power <= number)
        {
            if ((number & power) > 0)
                powers.emplace_back(power);
            power <<= 1;
        }
        std::vector<int> result(queries.size(), 0);
        for (size_t queryIndex = 0; queryIndex < queries.size(); ++queryIndex)
        {
            long long product = 1;
            const size_t startPowerIndex = queries[queryIndex][0];
            const size_t endPowerIndex = queries[queryIndex][1];
            for (size_t powerIndex = startPowerIndex; powerIndex <= endPowerIndex; ++powerIndex)
                product = (product * powers[powerIndex]) % modValue;
            result[queryIndex] = static_cast<int>(product);
        }
        return result;
    }
};

}

namespace RangeProductQueriesOfPowersTask
{

TEST(RangeProductQueriesOfPowersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 4, 64}), solution.productQueries(15, {{0, 1}, {2, 2}, {0, 3}}));
    ASSERT_EQ(std::vector<int>({2}), solution.productQueries(2, {{0, 0}}));
}

}