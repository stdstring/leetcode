#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int destroyTargets(std::vector<int> const &nums, int space) const
    {
        std::unordered_map<int, RestData> restMap;
        for (const int number : nums)
        {
            int rest = number % space;
            auto iterator = restMap.find(rest);
            if (iterator == restMap.cend())
                restMap.emplace(rest, RestData(number, 1));
            else
            {
                iterator->second.MinValue = std::min(iterator->second.MinValue, number);
                ++iterator->second.Count;
            }
        }
        int minValue = 0;
        size_t targetCount = 0;
        for (auto const &[_, data] : restMap)
        {
            if (data.Count == targetCount)
                minValue = std::min(minValue, data.MinValue);
            if (data.Count > targetCount)
            {
                targetCount = data.Count;
                minValue = data.MinValue;
            }
        }
        return minValue;
    }

private:
    struct RestData
    {
        RestData(int minValue, size_t count) : MinValue(minValue), Count(count)
        {
        }

        int MinValue;
        size_t Count;
    };
};

}

namespace DestroySequentialTargetsTask
{

TEST(DestroySequentialTargetsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.destroyTargets({3, 7, 8, 1, 1, 5}, 2));
    ASSERT_EQ(1, solution.destroyTargets({1, 3, 5, 2, 4, 6}, 2));
    ASSERT_EQ(2, solution.destroyTargets({6, 2, 5}, 100));
}

}