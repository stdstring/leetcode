#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool circularArrayLoop(std::vector<int> const &nums) const
    {
        std::vector<bool> visited(nums.size(), false);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (visited[index])
                continue;
            if (isLoop(nums, visited, index))
                return true;
        }
        return false;
    }

private:
    [[nodiscard]] bool isLoop(std::vector<int> const &nums, std::vector<bool> &visited, size_t start) const
    {
        const int size = static_cast<int>(nums.size());
        int current = static_cast<int>(start);
        int step = 0;
        std::unordered_map<int, int> stepMap;
        while (!visited[current])
        {
            visited[current] = true;
            stepMap.emplace(current, step);
            ++step;
            if (sign(nums[current]) != sign(nums[start]))
            {
                visited[current] = false;
                return false;
            }
            current = (current + nums[current] % size) % size;
            if (current < 0)
                current += size;
        }
        return stepMap.count(current) == 0 ? false : (step - stepMap[current]) > 1;
    }

    [[nodiscard]] int sign(int value) const
    {
        return value == 0 ? 0 : (value > 0 ? 1 : -1);
    }
};

}

namespace CircularArrayLoopTask
{

TEST(CircularArrayLoopTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.circularArrayLoop({2, -1, 1, 2, 2}));
    ASSERT_EQ(false, solution.circularArrayLoop({-1, -2, -3, -4, -5, 6}));
    ASSERT_EQ(true, solution.circularArrayLoop({1, -1, 5, 1, 4}));
}

TEST(CircularArrayLoopTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.circularArrayLoop({-1, -2, -3, -4, -5}));
    ASSERT_EQ(false, solution.circularArrayLoop({2, 2, 2, 2, 2, 4, 7}));
    ASSERT_EQ(true, solution.circularArrayLoop({-1, 2, 1, 2}));
}

}