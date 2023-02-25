#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string largestNumber(std::vector<int> const &nums) const
    {
        std::vector<std::string> numbers;
        numbers.reserve(nums.size());
        for (int num : nums)
            numbers.push_back(std::to_string(num));
        std::sort(numbers.begin(), numbers.end(), [](std::string const &left, std::string const &right){ return (left + right) > (right + left); });
        if (numbers.front() == "0")
            return "0";
        std::string result;
        for (std::string const &number : numbers)
            result.append(number);
        return result;
    }
};

}

namespace LargestNumberTask
{

TEST(LargestNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("210", solution.largestNumber({10, 2}));
    ASSERT_EQ("9534330", solution.largestNumber({3, 30, 34, 5, 9}));
    ASSERT_EQ("1", solution.largestNumber({1}));
    ASSERT_EQ("10", solution.largestNumber({10}));
}

TEST(LargestNumberTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ("43243432", solution.largestNumber({432, 43243}));
    ASSERT_EQ("0", solution.largestNumber({0, 0}));
}

}