#include <cstdint>
#include <numeric>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int nthUglyNumber(int n, int a, int b, int c) const
    {
        const uint64_t nValue = n;
        const uint64_t aValue = a;
        const uint64_t bValue = b;
        const uint64_t cValue = c;
        const uint64_t abLcm = std::lcm(aValue, bValue);
        const uint64_t acLcm = std::lcm(aValue, cValue);
        const uint64_t bcLcm = std::lcm(bValue, cValue);
        const uint64_t abcLcm = std::lcm(abLcm, cValue);
        uint64_t left = 1;
        uint64_t right = 10;
        while (calcUglyNumbersCount(right, aValue, bValue, cValue, abLcm, acLcm, bcLcm, abcLcm) < nValue)
            right *= 10ULL;
        while (right > left)
        {
            const uint64_t middle = (left + right) / 2ULL;
            if (calcUglyNumbersCount(middle, aValue, bValue, cValue, abLcm, acLcm, bcLcm, abcLcm) < nValue)
                left = middle + 1;
            else
                right = middle;
        }
        return static_cast<int>(right);
    }

private:
    [[nodiscard]] uint64_t calcUglyNumbersCount(uint64_t n,
                                                uint64_t a,
                                                uint64_t b,
                                                uint64_t c,
                                                uint64_t abLcm,
                                                uint64_t acLcm,
                                                uint64_t bcLcm,
                                                uint64_t abcLcm) const
    {
        return (n / a) + (n / b) + (n / c) - (n / abLcm) - (n / acLcm) - (n / bcLcm) + (n / abcLcm);
    }
};

}

namespace UglyNumberIIITask
{

TEST(UglyNumberIIITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.nthUglyNumber(3, 2, 3, 5));
    ASSERT_EQ(6, solution.nthUglyNumber(4, 2, 3, 4));
    ASSERT_EQ(10, solution.nthUglyNumber(5, 2, 11, 13));
}

TEST(UglyNumberIIITaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1999999984, solution.nthUglyNumber(1000000000, 2, 217983653, 336916467));
    ASSERT_EQ(8, solution.nthUglyNumber(5, 2, 3, 3));
    ASSERT_EQ(44, solution.nthUglyNumber(25, 2, 4, 7));
}

}