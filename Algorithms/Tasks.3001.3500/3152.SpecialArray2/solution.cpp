#include <iterator>
#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<bool> isArraySpecial(std::vector<int> const &nums, std::vector<std::vector<int>> const &queries) const
    {
        std::map<int, int> specialSubarrays;
        for (size_t index = 0; index < nums.size() - 1;++index)
        {
            const int currentRest = nums[index] % 2;
            const int nextRest = nums[index + 1] % 2;
            if (currentRest != nextRest)
            {
                size_t specialSubarrayEnd = findSpecialSubarrayEnd(nums, index);
                specialSubarrays.emplace(static_cast<int>(index), static_cast<int>(specialSubarrayEnd));
                index = specialSubarrayEnd;
            }
        }
        std::vector<bool> answer(queries.size(), false);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            if (queries[index][0] == queries[index][1])
            {
                answer[index] = true;
                continue;
            }
            auto iterator = specialSubarrays.upper_bound(queries[index][0]);
            if (iterator == specialSubarrays.cbegin())
            {
                answer[index] = false;
                continue;
            }
            iterator = std::prev(iterator, 1);
            answer[index] = (iterator->first <= queries[index][0]) && (queries[index][1] <= iterator->second);
        }
        return answer;
    }

private:
    [[nodiscard]] size_t findSpecialSubarrayEnd(std::vector<int> const &nums, size_t start) const
    {
        size_t current = start;
        for (;current < nums.size() - 1;++current)
        {
            const int currentRest = nums[current] % 2;
            const int nextRest = nums[current + 1] % 2;
            if (currentRest == nextRest)
                return current;
        }
        return nums.size() - 1;
    }
};

}

namespace SpecialArray2Task
{

TEST(SpecialArray2Task, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<bool>({false}), solution.isArraySpecial({3, 4, 1, 2, 6}, {{0, 4}}));
    ASSERT_EQ(std::vector<bool>({false, true}), solution.isArraySpecial({4, 3, 1, 6}, {{0, 2}, {2, 3}}));
}

TEST(SpecialArray2Task, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<bool>({true}), solution.isArraySpecial({1}, {{0, 0}}));
}

}