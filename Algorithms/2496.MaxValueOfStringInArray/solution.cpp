#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumValue(std::vector<std::string> const &strs) const
    {
        int bestValue = 0;
        for (std::string const &source : strs)
        {
            if (std::all_of(source.cbegin(), source.cend(), [](char ch){ return std::isdigit(ch) != 0; }))
                bestValue = std::max(bestValue, stoi(source));
            else
                bestValue = std::max(bestValue, static_cast<int>(source.size()));
        }
        return bestValue;
    }
};

}

namespace MaxValueOfStringInArrayTask
{

TEST(MaxValueOfStringInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maximumValue({"alic3", "bob", "3", "4", "00000"}));
    ASSERT_EQ(1, solution.maximumValue({"1", "01", "001", "0001"}));
}

}