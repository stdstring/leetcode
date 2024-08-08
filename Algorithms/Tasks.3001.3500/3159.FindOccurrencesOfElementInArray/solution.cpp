#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> occurrencesOfElement(std::vector<int> const &nums, std::vector<int> const &queries, int x) const
    {
        const int numbersCount = static_cast<int>(nums.size());
        std::vector<int> elementIndices;
        elementIndices.reserve(nums.size());
        for (int index = 0; index < numbersCount; ++index)
        {
            if (nums[index] == x)
                elementIndices.emplace_back(index);
        }
        const int elementsCount = static_cast<int>(elementIndices.size());
        std::vector<int> answer(queries.size(), -1);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            if (queries[index] <= elementsCount)
                answer[index] = elementIndices[queries[index] - 1];
        }
        return answer;
    }
};

}

namespace FindOccurrencesOfElementInArrayTask
{

TEST(FindOccurrencesOfElementInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, -1, 2, -1}), solution.occurrencesOfElement({1, 3, 1, 7}, {1, 3, 2, 4}, 1));
    ASSERT_EQ(std::vector<int>({-1}), solution.occurrencesOfElement({1, 2, 3}, {10}, 5));
}

}