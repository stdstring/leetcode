#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int divisorSubstrings(int num, int k) const
    {
        const std::string number(std::to_string(num));
        size_t divisorCount = 0;
        for (size_t start = 0; start <= number.size() - k; ++start)
        {
            const int possibleDivisor = std::stoi(number.substr(start, k));
            if ((possibleDivisor > 0) && (num % possibleDivisor == 0))
                ++divisorCount;
        }
        return static_cast<int>(divisorCount);
    }
};

}

namespace FindKBeautyOfNumberTask
{

TEST(FindKBeautyOfNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.divisorSubstrings(240, 2));
    ASSERT_EQ(2, solution.divisorSubstrings(430043, 2));
}

}