#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> largestDivisibleSubset(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        std::vector<std::vector<int>> subsets;
        subsets.reserve(numbers.size());
        for (int number : numbers)
            subsets.emplace_back(std::vector<int>({number}));
        for (size_t current = 1; current < numbers.size(); ++current)
        {
            for (size_t index = 0; index < current; ++index)
            {
                if ((numbers[current] % numbers[index]) == 0)
                {
                    if (subsets[current].size() <= subsets[index].size())
                    {
                        std::vector<int> subset(subsets[index]);
                        subset.push_back(numbers[current]);
                        subsets[current] = subset;
                    }
                }
            }
        }
        auto bestIterator = subsets.cbegin();
        for (auto iterator = subsets.cbegin(); iterator != subsets.cend(); ++iterator)
        {
            if (bestIterator->size() < iterator->size())
                bestIterator = iterator;
        }
        return *bestIterator;
    }
};

}

namespace LargestDivisibleSubsetTask
{

TEST(LargestDivisibleSubsetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2}), solution.largestDivisibleSubset({1, 2, 3}));
    ASSERT_EQ(std::vector<int>({1, 2, 4, 8}), solution.largestDivisibleSubset({1, 2, 4, 8}));
}

TEST(LargestDivisibleSubsetTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({4, 8, 16}), solution.largestDivisibleSubset({3, 4, 16, 8}));
    ASSERT_EQ(std::vector<int>({9, 18, 90, 180, 360, 720}), solution.largestDivisibleSubset({5, 9, 18, 54, 108, 540, 90, 180, 360, 720}));
}

}