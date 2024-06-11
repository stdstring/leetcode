#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> relativeSortArray(std::vector<int> const &arr1, std::vector<int> const &arr2) const
    {
        std::vector<int> result(arr1.size(), 0);
        std::unordered_map<int, int> arr2Numbers;
        arr2Numbers.reserve(arr2.size());
        for (int number : arr2)
            arr2Numbers.emplace(number, 0);
        size_t arr1RestCount = 0;
        for (int number : arr1)
        {
            auto iterator = arr2Numbers.find(number);
            if (iterator != arr2Numbers.cend())
                ++iterator->second;
            else
                result[arr1RestCount++] = number;
        }
        if (arr1RestCount > 0)
        {
            const auto frontRegionEnd = std::next(result.begin(), static_cast<int>(arr1RestCount));
            const auto backRegionBegin = std::next(result.begin(), static_cast<int>(result.size() - arr1RestCount));
            std::sort(result.begin(), frontRegionEnd);
            std::copy(result.begin(), frontRegionEnd, backRegionBegin);
        }
        for (size_t resultIndex = 0, arr2Index = 0; arr2Index < arr2.size(); ++arr2Index)
        {
            auto iterator = arr2Numbers.find(arr2[arr2Index]);
            if (iterator == arr2Numbers.cend())
                continue;
            for (int iteration = 0; iteration < iterator->second; ++iteration)
                result[resultIndex++] = iterator->first;
        }
        return result;
    }
};

}

namespace RelativeSortArrayTask
{

TEST(RelativeSortArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 2, 2, 1, 4, 3, 3, 9, 6, 7, 19}),
              solution.relativeSortArray({2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19}, {2, 1, 4, 3, 9, 6}));
    ASSERT_EQ(std::vector<int>({22, 28, 8, 6, 17, 44}),
              solution.relativeSortArray({28, 6, 22, 8, 44, 17}, {22, 28, 8, 6}));
}

}