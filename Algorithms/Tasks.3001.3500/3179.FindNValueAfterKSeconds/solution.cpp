#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int valueAfterKSeconds(int n, int k) const
    {
        constexpr int modValue = 1000000007;
        if (n == 1)
            return 1;
        if (n == 2)
            return k + 1;
        std::vector<int> numbers(n, 1);
        for (int step = 1; step <= k; ++step)
        {
            for (size_t index = 1; index < numbers.size(); ++index)
                numbers[index] = (numbers[index] + numbers[index - 1]) % modValue;
        }
        return numbers.back();
    }
};

}

namespace FindNValueAfterKSecondsTask
{

TEST(FindNValueAfterKSecondsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(56, solution.valueAfterKSeconds(4, 5));
    ASSERT_EQ(35, solution.valueAfterKSeconds(5, 3));
}

TEST(FindNValueAfterKSecondsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(84793457, solution.valueAfterKSeconds(5, 1000));
}

}