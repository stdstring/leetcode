#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestArithSeqLength(std::vector<int> const &nums) const
    {
        size_t bestSize = 2;
        std::unordered_map<int, std::vector<size_t>> numberMap;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            auto iterator = numberMap.find(nums[index]);
            if (iterator == numberMap.end())
                iterator = numberMap.emplace(nums[index], std::vector<size_t>()).first;
            iterator->second.emplace_back(index);
            bestSize = std::max(bestSize, iterator->second.size());
        }
        for (size_t firstIndex = 0; firstIndex < nums.size() - 1; ++firstIndex)
        {
            for (size_t secondIndex = firstIndex + 1; secondIndex < nums.size(); ++secondIndex)
            {
                const int firstNumber = nums[firstIndex];
                const int secondNumber = nums[secondIndex];
                bestSize = std::max(bestSize, calcArithSeqLength(firstNumber, secondNumber, secondIndex, numberMap));
            }
        }
        return static_cast<int>(bestSize);
    }

private:
    size_t calcArithSeqLength(int first, int second, size_t lastIndex, std::unordered_map<int, std::vector<size_t>> const &numberMap) const
    {
        if (first == second)
            return 0;
        const int delta = second - first;
        int current = second;
        size_t length = 2;
        while (true)
        {
            int next = current + delta;
            auto nextIterator = numberMap.find(next);
            if (nextIterator == numberMap.cend())
                break;
            auto indexIterator = std::ranges::upper_bound(nextIterator->second, lastIndex);
            if (indexIterator == nextIterator->second.cend())
                break;
            ++length;
            lastIndex = *indexIterator;
            current = next;
        }
        return length;
    }
};

}

namespace LongestArithSubsequenceTask
{

TEST(LongestArithSubsequenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.longestArithSeqLength({3, 6, 9, 12}));
    ASSERT_EQ(3, solution.longestArithSeqLength({9, 4, 7, 2, 10}));
    ASSERT_EQ(4, solution.longestArithSeqLength({20, 1, 15, 3, 10, 5, 8}));
}

}