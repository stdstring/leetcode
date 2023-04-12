#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<long long> distance(std::vector<int> const &nums) const
    {
        std::unordered_map<int, std::vector<size_t>> numberPositionsMap;
        for (size_t index = 0; index < nums.size(); ++index)
            numberPositionsMap[nums[index]].emplace_back(index);
        std::vector<long long> result(nums.size(), 0);
        for (auto const &[_, positions] : numberPositionsMap)
        {
            if (positions.size() > 1)
                distance(positions, result);
        }
        return result;
    }

private:
    void distance(std::vector<size_t> const &positions, std::vector<long long> &result) const
    {
        long long leftDistance = 0;
        long long rightDistance = 0;
        for (const size_t index : positions)
            rightDistance += static_cast<long long>(index - positions.front());
        result[positions.front()] = leftDistance + rightDistance;
        for (size_t index = 1; index < positions.size(); ++index)
        {
            const size_t prevPosition = positions[index - 1];
            const size_t currentPosition = positions[index];
            rightDistance -= static_cast<long long>((positions.size() - index + 1) * (currentPosition - prevPosition));
            leftDistance += static_cast<long long>((index + 1) * (currentPosition - prevPosition));
            result[currentPosition] = leftDistance + rightDistance;
        }
    }
};

}

namespace SumOfDistancesTask
{

TEST(SumOfDistancesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<long long>({5, 0, 3, 4, 0}), solution.distance({1, 3, 1, 1, 2}));
    ASSERT_EQ(std::vector<long long>({0, 0, 0}), solution.distance({0, 5, 3}));
}

}