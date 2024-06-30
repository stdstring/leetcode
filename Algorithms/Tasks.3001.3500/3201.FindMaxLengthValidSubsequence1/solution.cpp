#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumLength(std::vector<int> const &nums) const
    {
        std::vector<size_t> evenNumbers;
        evenNumbers.reserve(nums.size());
        std::vector<size_t> oddNumbers;
        oddNumbers.reserve(nums.size());
        for (size_t index = 0; index < nums.size(); ++index)
            ((nums[index] % 2 == 0) ? evenNumbers : oddNumbers).emplace_back(index);
        if (evenNumbers.empty())
            return static_cast<int>(oddNumbers.size());
        if (oddNumbers.empty())
            return static_cast<int>(evenNumbers.size());
        size_t maxLength = std::max(evenNumbers.size(), oddNumbers.size());
        maxLength = std::max(maxLength, calcMaxLength(evenNumbers, oddNumbers, 0, oddNumbers[0], 1));
        maxLength = std::max(maxLength, calcMaxLength(oddNumbers, evenNumbers, 0, evenNumbers[0], 1));
        return static_cast<int>(maxLength);
    }

private:
    [[nodiscard]] size_t calcMaxLength(std::vector<size_t> const &first,
                                       std::vector<size_t> const &second,
                                       size_t firstIndex,
                                       size_t secondIndex,
                                       size_t length) const
    {
        while ((firstIndex < first.size()) && (first[firstIndex] < second[secondIndex]))
            ++firstIndex;
        if (firstIndex == first.size())
            return length;
        return calcMaxLength(second, first, secondIndex, firstIndex, length + 1);
    }
};

}

namespace FindMaxLengthValidSubsequence1Task
{

TEST(FindMaxLengthValidSubsequence1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maximumLength({1, 2, 3, 4}));
    ASSERT_EQ(6, solution.maximumLength({1, 2, 1, 1, 2, 1, 2}));
    ASSERT_EQ(2, solution.maximumLength({1, 3}));
}

}