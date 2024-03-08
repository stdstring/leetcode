#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxFrequencyElements(std::vector<int> const &nums) const
    {
        int maxFrequency = 0;
        std::unordered_map<int, int> frequencyMap;
        for (int number : nums)
        {
            auto iterator = frequencyMap.find(number);
            if (iterator == frequencyMap.cend())
                iterator = frequencyMap.emplace(number, 0).first;
            ++iterator->second;
            maxFrequency = std::max(maxFrequency, iterator->second);
        }
        int totalFrequency = 0;
        for (const auto [_, frequency] : frequencyMap)
        {
            if (frequency == maxFrequency)
                totalFrequency += frequency;
        }
        return totalFrequency;
    }
};

}

namespace CountElementsWithMaxFreqTask
{

TEST(CountElementsWithMaxFreqTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maxFrequencyElements({1, 2, 2, 3, 1, 4}));
    ASSERT_EQ(5, solution.maxFrequencyElements({1, 2, 3, 4, 5}));
}

}