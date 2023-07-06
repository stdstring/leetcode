#include <numeric>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long interchangeableRectangles(std::vector<std::vector<int>> const &rectangles) const
    {
        constexpr int64_t factor = 100000;
        std::unordered_map<int64_t, size_t> ratioMap;
        for (std::vector<int> const &rectangle : rectangles)
        {
            const int gcd = std::gcd(rectangle[0], rectangle[1]);
            const int numerator = rectangle[0] / gcd;
            const int denominator = rectangle[1] / gcd;
            // 1 <= numerator, denominator <= 100000
            int64_t key = factor * (numerator - 1) + (denominator - 1);
            ++ratioMap[key];
        }
        long long result = 0;
        for (auto const& entry : ratioMap)
            result += calcPairCount(entry.second);
        return result;
    }

private:
    [[nodiscard]] long long calcPairCount(size_t itemCount) const
    {
        return itemCount == 1 ? 0 : (1 + (itemCount - 1)) * (itemCount - 1) / 2;
    }
};

}

namespace NumberPairsOfInterchangeableRectanglesTask
{

TEST(NumberPairsOfInterchangeableRectanglesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.interchangeableRectangles({{4, 8}, {3, 6}, {10, 20}, {15, 30}}));
    ASSERT_EQ(0, solution.interchangeableRectangles({{4, 5}, {7, 8}}));
}

}