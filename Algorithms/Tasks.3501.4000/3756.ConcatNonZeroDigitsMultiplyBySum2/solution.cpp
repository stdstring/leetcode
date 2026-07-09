#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> sumAndMultiply(std::string const &s, std::vector<std::vector<int>> const &queries) const
    {
        constexpr long long modValue = 1000000007;
        std::vector<int> digitSumPrefix(s.size() + 1, 0);
        std::vector<long long> numberPrefix(s.size() + 1, 0);
        std::vector<int> numberLengthPrefix(s.size() + 1, 0);
        std::vector<long long> power10(s.size() + 1, 0);
        power10[0] = 1;
        for (size_t index = 0; index < s.size(); ++index)
        {
            const int digit = s[index] - '0';
            digitSumPrefix[index + 1] = digitSumPrefix[index] + digit;
            numberPrefix[index + 1] = (digit == 0) ? numberPrefix[index] : (10LL * numberPrefix[index] + digit) % modValue;
            numberLengthPrefix[index + 1] = numberLengthPrefix[index] + (digit == 0 ? 0 : 1);
            power10[index + 1] = (10LL * power10[index]) % modValue;
        }
        std::vector<int> result(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            const size_t left = queries[index][0];
            const size_t right = queries[index][1] + 1;
            const int sum = digitSumPrefix[right] - digitSumPrefix[left];
            const long long numberPrefixFactor = power10[numberLengthPrefix[right] - numberLengthPrefix[left]];
            long long number = (numberPrefix[right] - numberPrefixFactor * numberPrefix[left]) % modValue;
            if (number < 0)
                number += modValue;
            const long long answer = (1LL * sum * number) % modValue;
            result[index] = static_cast<int>(answer);
        }
        return result;
    }
};

}

namespace ConcatNonZeroDigitsMultiplyBySum2Task
{

TEST(ConcatNonZeroDigitsMultiplyBySum2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({12340, 4, 9}), solution.sumAndMultiply("10203004", {{0, 7}, {1, 3}, {4, 6}}));
    ASSERT_EQ(std::vector<int>({1, 0}), solution.sumAndMultiply("1000", {{0, 3}, {1, 1}}));
    ASSERT_EQ(std::vector<int>({444444137}), solution.sumAndMultiply("9876543210", {{0, 9}}));
}

TEST(ConcatNonZeroDigitsMultiplyBySum2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({894996047}), solution.sumAndMultiply("2711785625", {{1, 9}}));
}

}
