#include <iterator>
#include <list>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumPairRemoval(std::vector<int> const &nums) const
    {
        std::list<int> numbers(nums.cbegin(), nums.cend());
        size_t operationCount = 0;
        while (!isNonDecreasing(numbers))
        {
            int minPairSum = INT_MAX;
            auto minPairStart = numbers.end();
            for (auto iterator = std::next(numbers.begin()); iterator != numbers.end(); ++iterator)
            {
                int pairSum = *std::prev(iterator) + *iterator;
                if (pairSum < minPairSum)
                {
                    minPairStart = std::prev(iterator);
                    minPairSum = pairSum;
                }
            }
            numbers.erase(std::next(minPairStart));
            *minPairStart = minPairSum;
            ++operationCount;
        }
        return static_cast<int>(operationCount);
    }

private:
    [[nodiscard]] bool isNonDecreasing(std::list<int> const &numbers) const
    {
        if (numbers.size() == 1)
            return true;
        for (auto iterator = std::next(numbers.cbegin()); iterator != numbers.cend(); ++iterator)
        {
            if (*std::prev(iterator) > *iterator)
                return false;
        }
        return true;
    }
};

}

namespace MinPairRemovalToSortArray1Task
{

TEST(MinPairRemovalToSortArray1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumPairRemoval({5, 2, 3, 1}));
    ASSERT_EQ(0, solution.minimumPairRemoval({1, 2, 2}));
}

}