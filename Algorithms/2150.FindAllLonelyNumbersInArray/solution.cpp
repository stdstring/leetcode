#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findLonely(std::vector<int> const &nums) const
    {
        std::unordered_map<int, size_t> numberMap;
        for (int number : nums)
            ++numberMap[number];
        std::vector<int> lonelyNumbers;
        for (auto const &entry : numberMap)
        {
            int number = entry.first;
            const size_t count = entry.second;
            if ((count == 1) &&
                (numberMap.find(number - 1) == numberMap.cend()) &&
                (numberMap.find(number + 1) == numberMap.cend()))
            lonelyNumbers.push_back(number);
        }
        std::sort(lonelyNumbers.begin(), lonelyNumbers.end());
        return lonelyNumbers;
    }
};

}

namespace FindAllLonelyNumbersInArrayTask
{

TEST(FindAllLonelyNumbersInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({8, 10}), solution.findLonely({10, 6, 5, 8}));
    ASSERT_EQ(std::vector<int>({1, 5}), solution.findLonely({1, 3, 5, 3}));
}

}