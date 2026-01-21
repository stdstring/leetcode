#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> minBitwiseArray(std::vector<int> const &nums) const
    {
        std::vector<int> answer(nums.size(), -1);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const int current = nums[index];
            if (current == 2)
                continue;
            int oneBit = 1;
            while ((current & oneBit) > 0)
                oneBit <<= 1;
            answer[index] = (current - (oneBit >> 1));
        }
        return answer;
    }
};

}

namespace ConstructMinBitwiseArray2Task
{

TEST(ConstructMinBitwiseArray2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({-1, 1, 4, 3}), solution.minBitwiseArray({2, 3, 5, 7}));
    ASSERT_EQ(std::vector<int>({9, 12, 15}), solution.minBitwiseArray({11, 13, 31}));
}

TEST(ConstructMinBitwiseArray2TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({-1, -1, -1}), solution.minBitwiseArray({2, 2, 2}));
}

}