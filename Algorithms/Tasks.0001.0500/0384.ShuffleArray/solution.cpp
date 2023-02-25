#include <chrono>
#include <map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    Solution(std::vector<int> const &nums) : _numbers(nums)
    {
        srand(static_cast<unsigned int>(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())));
    }

    /* Resets the array to its original configuration and return it. */
    std::vector<int> reset() const
    {
        return _numbers;
    }

    /* Returns a random shuffling of the array. */
    std::vector<int> shuffle() const
    {
        std::vector<int> result(_numbers);
        for (size_t index = 0; index < _numbers.size(); ++index)
            std::swap(result[index], result[rand() % _numbers.size()]);
        return result;
    }

private:
    std::vector<int> _numbers;
};

}

namespace ShuffleArrayTask
{

TEST(ShuffleArrayTaskTests, Examples)
{
    // TODO (std_string) : think about approach via using lexicographical numbers
    const size_t permutationCount = 6;
    const Solution solution({1, 2, 3});
    std::map<std::vector<int>, size_t> permutationsCounter = {{{1, 2, 3}, 0}, {{1, 3, 2}, 0}, {{2, 1, 3}, 0}, {{2, 3, 1}, 0}, {{3, 1, 2}, 0}, {{3, 2, 1}, 0}};
    const size_t caseCount = 1000;
    for (size_t caseIndex = 0; caseIndex < permutationCount * caseCount; ++caseIndex)
        ++permutationsCounter[solution.shuffle()];
    const size_t delta = 250;
    for (auto const &permutationCounter : permutationsCounter)
        ASSERT_TRUE((caseCount - delta <= permutationCounter.second) && (permutationCounter.second <= caseCount + delta));
    ASSERT_EQ(std::vector<int>({ 1, 2, 3 }), solution.reset());
}

}