#include <algorithm>
#include <random>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    Solution(std::vector<int> const &nums)
    {
        for (size_t index = 0; index < nums.size(); ++index)
            _targetIndicesMap[nums[index]].push_back(static_cast<int>(index));
    }

    int pick(int target)
    {
        const auto iterator = _targetIndicesMap.find(target);
        const std::uniform_int_distribution<> distribution(0, static_cast<int>(iterator->second.size()) - 1);
        return iterator->second[distribution(_generator)];
    }

private:
    std::mt19937 _generator;
    std::unordered_map<int, std::vector<int>> _targetIndicesMap;
};

}

namespace
{

void checkContains(std::vector<int> const &numbers, int number)
{
    ASSERT_NE(numbers.cend(), std::find(numbers.cbegin(), numbers.cend(), number));
}

}

namespace RandomPickIndexTask
{

TEST(RandomPickIndexTaskTests, Examples)
{
    Solution solution({1, 2, 3, 3, 3});
    checkContains({2, 3, 4}, solution.pick(3));
    checkContains({0}, solution.pick(1));
    checkContains({2, 3, 4}, solution.pick(3));
}

}