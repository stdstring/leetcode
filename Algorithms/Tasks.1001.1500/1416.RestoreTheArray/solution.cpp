#include <cstdint>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numberOfArrays(std::string const &s, int k) const
    {
        constexpr size_t modValue = 1000000007;
        std::vector<size_t> countData(s.size() + 1, 0);
        countData[0] = 1;
        for (size_t index = 0; index < s.size(); ++index)
        {
            int64_t number = 0;
            int64_t factor = 1;
            for (size_t shift = 0; shift <= index; ++shift)
            {
                if (factor > k)
                    break;
                const int digit = s[index - shift] - '0';
                number += (factor * digit);
                if (number > k)
                    break;
                if (digit != 0)
                    countData[index + 1] = (countData[index + 1] + countData[index - shift]) % modValue;
                factor *= 10;
            }
        }
        return static_cast<int>(countData.back());
    }
};

}

namespace RestoreTheArrayTask
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.numberOfArrays("1000", 10000));
    ASSERT_EQ(0, solution.numberOfArrays("1000", 10));
    ASSERT_EQ(8, solution.numberOfArrays("1317", 2000));
    ASSERT_EQ(1, solution.numberOfArrays("2020", 30));
    ASSERT_EQ(34, solution.numberOfArrays("1234567890", 90));
}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(4076, solution.numberOfArrays("1111111111111", 1000000000));
    ASSERT_EQ(0, solution.numberOfArrays("100000000000000000000", 1000000000));
}

}
