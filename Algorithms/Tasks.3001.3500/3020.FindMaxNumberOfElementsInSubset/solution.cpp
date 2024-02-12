#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumLength(std::vector<int> const &nums) const
    {
        std::unordered_map<long long, size_t> numbers;
        for (const int number : nums)
            ++numbers[number];
        size_t maxLength = 0;
        for (auto const &[number, count] : numbers)
        {
            if (number == 1)
                maxLength = std::max(maxLength, count - (count % 2 == 0 ? 1 : 0));
            else
            {
                long long currentNumber = number;
                size_t currentSize = 1;
                maxLength = std::max(maxLength, currentSize);
                while ((numbers[currentNumber] > 1) && numbers.contains(currentNumber * currentNumber))
                {
                    currentSize += 2;
                    maxLength = std::max(maxLength, currentSize);
                    currentNumber *= currentNumber;
                }
            }
        }
        return static_cast<int>(maxLength);
    }
};

}

namespace FindMaxNumberOfElementsInSubsetTask
{

TEST(FindMaxNumberOfElementsInSubsetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumLength({5, 4, 1, 2, 2}));
    ASSERT_EQ(1, solution.maximumLength({1, 3, 2, 4}));
}

TEST(FindMaxNumberOfElementsInSubsetTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maximumLength({1, 1, 1, 1, 1, 1}));
}

}