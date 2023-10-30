#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> sortByBits(std::vector<int> const &arr) const
    {
        auto comp = [this](int left, int right)
        {
            const int leftCount = calcOneBitsCount(left);
            const int rightCount = calcOneBitsCount(right);
            return (leftCount < rightCount) || ((leftCount == rightCount) && (left < right));
        };
        std::vector<int> result(arr);
        std::ranges::sort(result, comp);
        return result;
    }

private:
    [[nodiscard]] int calcOneBitsCount(int number) const
    {
        int oneBitsCount = 0;
        while (number > 0)
        {
            if ((number & 1) != 0)
                ++oneBitsCount;
            number >>= 1;
        }
        return oneBitsCount;
    }
};

}

namespace SortIntegersByNumber1BitsTask
{

TEST(SortIntegersByNumber1BitsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 2, 4, 8, 3, 5, 6, 7}),
              solution.sortByBits({0, 1, 2, 3, 4, 5, 6, 7, 8}));
    ASSERT_EQ(std::vector<int>({1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024}),
              solution.sortByBits({1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1}));
}

}