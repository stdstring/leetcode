#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> simplifiedFractions(int n) const
    {
        std::vector<std::pair<int, int>> fractions;
        for (int denominator = 2; denominator <= n; ++denominator)
        {
            for (int numerator = 1; numerator < denominator; ++numerator)
            {
                if (std::gcd(numerator, denominator) == 1)
                    fractions.emplace_back(numerator, denominator);
            }
        }
        auto compFun = [](std::pair<int, int> const &l, std::pair<int, int> const &r){ return l.first * r.second < r.first * l.second; };
        std::sort(fractions.begin(), fractions.end(), compFun);
        std::vector<std::string> result;
        result.reserve(fractions.size());
        auto transformFun = [](std::pair<int, int> const &fr) { return std::to_string(fr.first).append("/").append(std::to_string(fr.second)); };
        std::transform(fractions.cbegin(), fractions.cend(), std::back_inserter(result), transformFun);
        return result;
    }
};

}

namespace SimplifiedFractionsTask
{

TEST(SimplifiedFractionsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"1/2"}), solution.simplifiedFractions(2));
    ASSERT_EQ(std::vector<std::string>({"1/3", "1/2", "2/3"}), solution.simplifiedFractions(3));
    ASSERT_EQ(std::vector<std::string>({"1/4", "1/3", "1/2", "2/3", "3/4"}), solution.simplifiedFractions(4));
}

}