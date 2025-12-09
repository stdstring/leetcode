#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int specialTriplets(std::vector<int> const &nums) const
    {
        std::unordered_map<int, std::vector<size_t>> numbers;
        for (size_t index = 0; index < nums.size(); ++index)
            numbers[nums[index]].emplace_back(index);
        constexpr size_t modValue = 1000000007;
        size_t result = 0;
        for (auto const &[number, indexes] : numbers)
        {
            if (number == 0)
            {
                for (size_t current = 0; current < indexes.size(); ++current)
                    result = (result + (current - 0) * (indexes.size() - 1 - current)) % modValue;
                continue;
            }
            auto doubleIterator = numbers.find(2 * number);
            if (doubleIterator == numbers.cend())
                continue;
            for (size_t index : indexes)
            {
                auto doubleIndexIterator = std::ranges::upper_bound(doubleIterator->second, index);
                if ((doubleIndexIterator == doubleIterator->second.cbegin()) ||
                    (doubleIndexIterator == doubleIterator->second.cend()))
                    continue;
                result += std::distance(doubleIterator->second.begin(), doubleIndexIterator) *
                          std::distance(doubleIndexIterator, doubleIterator->second.end());
                result %= modValue;
            }
        }
        return static_cast<int>(result);
    }
};

}

namespace CountSpecialTripletsTask
{

TEST(CountSpecialTripletsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.specialTriplets({6, 3, 6}));
    ASSERT_EQ(1, solution.specialTriplets({0, 1, 0, 0}));
    ASSERT_EQ(2, solution.specialTriplets({8, 4, 2, 8, 4}));
}

TEST(CountSpecialTripletsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.specialTriplets({0, 0, 0, 0, 0}));
}

}