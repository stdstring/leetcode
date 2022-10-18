#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countDistinctIntegers(std::vector<int> const &nums) const
    {
        std::unordered_set<int> numbers;
        for (int number : nums)
        {
            numbers.insert(number);
            numbers.insert(reverseNumber(number));
        }
        return static_cast<int>(numbers.size());
    }

private:
    [[nodiscard]] int reverseNumber(int number) const
    {
        int result = 0;
        while (number > 0)
        {
            result = 10 * result + (number % 10);
            number /= 10;
        }
        return result;
    }
};

}

namespace CountDistinctIntAfterReverseOpTask
{

TEST(CountDistinctIntAfterReverseOpTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.countDistinctIntegers({1, 13, 10, 12, 31}));
    ASSERT_EQ(1, solution.countDistinctIntegers({2, 2, 2}));
}

}
