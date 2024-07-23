#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> frequencySort(std::vector<int> const &nums) const
    {
        std::unordered_map<int, int> frequencyMap;
        for (int number : nums)
            ++frequencyMap[number];
        std::vector<std::pair<int, int>> frequencyData;
        frequencyData.reserve(frequencyMap.size());
        for(auto const &[number, frequency] : frequencyMap)
            frequencyData.emplace_back(number, frequency);
        auto comp = [](std::pair<int, int> const &l, std::pair<int, int> const &r) { return (l.second < r.second) || ((l.second == r.second) && (l.first > r.first)); };
        std::ranges::sort(frequencyData, comp);
        std::vector<int> result;
        result.reserve(nums.size());
        for (auto const &[number, frequency] : frequencyData)
        {
            for (int item = 0; item < frequency; ++item)
                result.emplace_back(number);
        }
        return result;
    }
};

}

namespace SortArrayByIncreasingFrequencyTask
{

TEST(SortArrayByIncreasingFrequencyTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 1, 1, 2, 2, 2}), solution.frequencySort({1, 1, 2, 2, 2, 3}));
    ASSERT_EQ(std::vector<int>({1, 3, 3, 2, 2}), solution.frequencySort({2, 3, 1, 3, 2}));
    ASSERT_EQ(std::vector<int>({5, -1, 4, 4, -6, -6, 1, 1, 1}), solution.frequencySort({-1, 1, -6, 4, 5, -6, 1, 4, 1}));
}

}