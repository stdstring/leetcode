#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getGoodIndices(std::vector<std::vector<int>> const &variables, int target) const
    {
        std::vector<int> result;
        for (size_t index = 0; index < variables.size(); ++index)
        {
            const int a = variables[index][0];
            const int b = variables[index][1];
            const int c = variables[index][2];
            const int m = variables[index][3];
            const int value = power(power(a, b, 10), c, m);
            if (value == target)
                result.emplace_back(index);
        }
        return result;
    }

private:
    [[nodiscard]] int power(int a, int b, int mod) const
    {
        if (a == 0)
            return 0;
        if (b == 0)
            return 1;
        int result = 1;
        for (int product = 1; product <= b; ++product)
            result = (result * a) % mod;
        return result;
    }
};

}

namespace DoubleModularExponentiationTask
{

TEST(DoubleModularExponentiationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 2}), solution.getGoodIndices({{2, 3, 3, 10}, {3, 3, 3, 1}, {6, 1, 1, 4}}, 2));
    ASSERT_EQ(std::vector<int>(), solution.getGoodIndices({{39, 3, 1000, 1000}}, 17));
}

}