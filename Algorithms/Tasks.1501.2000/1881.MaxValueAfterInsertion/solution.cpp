#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string maxValue(std::string const &n, int x) const
    {
        const char xChar = static_cast<char>(x + '0');
        std::string result;
        result.reserve(n.size() + 1);
        const bool isNegative = n.front() == '-';
        if (isNegative)
            result.push_back('-');
        bool isInserted = false;
        for (size_t index = isNegative ? 1 : 0; index < n.size(); ++index)
        {
            const bool canInsert = isNegative ? xChar < n[index] : xChar > n[index];
            if (canInsert && !isInserted)
            {
                result.push_back(xChar);
                isInserted = true;
            }
            result.push_back(n[index]);
        }
        if (!isInserted)
            result.push_back(xChar);
        return result;
    }
};

}

namespace MaxValueAfterInsertionTask
{

TEST(MaxValueAfterInsertionTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("999", solution.maxValue("99", 9));
    ASSERT_EQ("-123", solution.maxValue("-13", 2));
}

TEST(MaxValueAfterInsertionTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ("-122123", solution.maxValue("-12213", 2));
    ASSERT_EQ("322213", solution.maxValue("32213", 2));
}

TEST(MaxValueAfterInsertionTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ("4699757879438632651173569913153377", solution.maxValue("469975787943862651173569913153377", 3));
}

}