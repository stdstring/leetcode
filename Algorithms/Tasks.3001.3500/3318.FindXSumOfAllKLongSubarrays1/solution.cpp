#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findXSum(std::vector<int> const &nums, int k, int x) const
    {
        const size_t subarraySize = k;
        std::vector<int> result(nums.size() - subarraySize + 1, 0);
        std::unordered_map<int, int> slidingWindow;
        // init
        for (size_t index = 0; index < subarraySize; ++index)
            ++slidingWindow[nums[index]];
        result[0] = calcXSum(slidingWindow, x);
        // move
        for (size_t index = 1; index + subarraySize <= nums.size(); ++index)
        {
            auto prevIterator = slidingWindow.find(nums[index - 1]);
            --prevIterator->second;
            if (prevIterator->second == 0)
                slidingWindow.erase(prevIterator);
            ++slidingWindow[nums[index + subarraySize - 1]];
            result[index] = calcXSum(slidingWindow, x);
        }
        return result;
    }

private:
    [[nodiscard]] int calcXSum(std::unordered_map<int, int> const &slidingWindow, int x) const
    {
        std::vector<std::pair<int, int>> frequencyData(slidingWindow.cbegin(), slidingWindow.cend());
        if (frequencyData.size() <= static_cast<size_t>(x))
            return calcXSum(frequencyData.cbegin(), frequencyData.cend());
        auto comparer = [](std::pair<int, int> const &l, std::pair<int, int> const &r)
        {
            return (l.second > r.second) || ((l.second == r.second) && (l.first > r.first));
        };
        auto middle = std::next(frequencyData.begin(), x);
        std::ranges::partial_sort(frequencyData, middle, comparer);
        return calcXSum(frequencyData.begin(), middle);
    }

    [[nodiscard]] int calcXSum(std::vector<std::pair<int, int>>::const_iterator begin,
                               std::vector<std::pair<int, int>>::const_iterator end) const
    {
        int result = 0;
        for (auto iterator = begin; iterator != end; ++iterator)
            result += iterator->first * iterator->second;
        return result;
    }
};

}

namespace FindXSumOfAllKLongSubarrays1Task
{

TEST(FindXSumOfAllKLongSubarrays1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({6, 10, 12}), solution.findXSum({1, 1, 2, 2, 3, 4, 2, 3}, 6, 2));
    ASSERT_EQ(std::vector<int>({11, 15, 15, 15, 12}), solution.findXSum({3, 8, 7, 8, 7, 5}, 2, 2));
}

TEST(FindXSumOfAllKLongSubarrays1TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({13}), solution.findXSum({9, 2, 2}, 3, 3));
}

}