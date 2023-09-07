#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findLeastNumOfUniqueInts(std::vector<int> const &arr, int k) const
    {
        std::unordered_map<int, size_t> numberFrequencyMap;
        for (int number : arr)
            ++numberFrequencyMap[number];
        std::vector<size_t> frequencies;
        frequencies.reserve(numberFrequencyMap.size());
        for (auto const& [_, frequency] : numberFrequencyMap)
            frequencies.emplace_back(frequency);
        std::ranges::sort(frequencies);
        size_t index = 0;
        size_t removeCount = k;
        for (; (index < frequencies.size()) && (frequencies[index] <= removeCount); ++index)
            removeCount -= frequencies[index];
        return static_cast<int>(frequencies.size() - index);
    }
};

}

namespace LeastNumberUniqueIntsAfterKRemovalsTask
{

TEST(LeastNumberUniqueIntsAfterKRemovalsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.findLeastNumOfUniqueInts({5, 5, 4}, 1));
    ASSERT_EQ(2, solution.findLeastNumOfUniqueInts({4, 3, 1, 1, 3, 3, 2}, 3));
}

}