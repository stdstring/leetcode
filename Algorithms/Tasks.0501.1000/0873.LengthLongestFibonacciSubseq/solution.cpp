#include <algorithm>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int lenLongestFibSubseq(std::vector<int> const &arr) const
    {
        const std::unordered_set<int> numbers(arr.cbegin(), arr.cend());
        size_t bestLength = 0;
        for (size_t prevIndex = 0; prevIndex < arr.size() - 1; ++prevIndex)
        {
            for (size_t currentIndex = prevIndex + 1; currentIndex < arr.size(); ++currentIndex)
                bestLength = std::max(bestLength, calcSubseqSize(numbers, arr[prevIndex], arr[currentIndex]));
        }
        return static_cast<int>(bestLength);
    }

private:
    size_t calcSubseqSize(std::unordered_set<int> const &numbers, int prev, int current) const
    {
        size_t subseqSize = 0;
        while (numbers.contains(current + prev))
        {
            const int next = current + prev;
            ++subseqSize;
            prev = current;
            current = next;
        }
        return subseqSize + (subseqSize > 0 ? 2 : 0);
    }
};

}

namespace LengthLongestFibonacciSubseqTask
{

TEST(LengthLongestFibonacciSubseqTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.lenLongestFibSubseq({1, 2, 3, 4, 5, 6, 7, 8}));
    ASSERT_EQ(3, solution.lenLongestFibSubseq({1, 3, 7, 11, 12, 14, 18}));
}

TEST(LengthLongestFibonacciSubseqTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.lenLongestFibSubseq({1, 3, 5}));
}

}