#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string digitSum(std::string const &s, int k) const
    {
        const size_t groupSize = k;
        std::string current(s);
        while (current.size() > groupSize)
        {
            std::string next;
            int group = current.front() - '0';
            for (size_t index = 1; index < current.size(); ++index)
            {
                if ((index % groupSize) == 0)
                {
                    next.append(std::to_string(group));
                    group = 0;
                }
                group += (current[index] - '0');
            }
            next.append(std::to_string(group));
            std::swap(current, next);
        }
        return current;
    }
};

}

namespace CalculateDigitSumOfStringTask
{

TEST(CalculateDigitSumOfStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("135", solution.digitSum("11111222223", 3));
    ASSERT_EQ("000", solution.digitSum("00000000", 3));
}

TEST(CalculateDigitSumOfStringTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("37", solution.digitSum("1234", 2));
}

}