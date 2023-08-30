#include <ranges>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumReplacement(std::vector<int> const &nums) const
    {
        long long result = 0;
        int lastNumber = nums.back();
        for (const int currentNumber : std::ranges::reverse_view(nums))
        {
            const int portionCount = (currentNumber + lastNumber - 1) / lastNumber;
            result += (portionCount - 1);
            lastNumber = currentNumber / portionCount;
        }
        return result;
    }
};

}

namespace MinReplacementsToSortArrayTask
{

TEST(MinReplacementsToSortArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimumReplacement({3, 9, 3}));
    ASSERT_EQ(0, solution.minimumReplacement({1, 2, 3, 4, 5}));
}

TEST(MinReplacementsToSortArrayTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minimumReplacement({3, 3, 4, 3}));
    ASSERT_EQ(3, solution.minimumReplacement({3, 7, 3}));
}

TEST(MinReplacementsToSortArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(17748, solution.minimumReplacement({368, 112, 2, 282, 349, 127, 36, 98, 371, 79,
                                                  309, 221, 175, 262, 224, 215, 230, 250, 84, 269,
                                                  384, 328, 118, 97, 17, 105, 342, 344, 242, 160,
                                                  394, 17, 120, 335, 76, 101, 260, 244, 378, 375,
                                                  164, 190, 320, 376, 197, 398, 353, 138, 362, 38,
                                                  54, 172, 3, 300, 264, 165, 251, 24, 312, 355,
                                                  237, 314, 397, 101, 117, 268, 36, 165, 373, 269,
                                                  351, 67, 263, 332, 296, 13, 118, 294, 159, 137,
                                                  82, 288, 250, 131, 354, 261, 192, 111, 16, 139,
                                                  261, 295, 112, 121, 234, 335, 256, 303, 328, 242,
                                                  260, 346, 22, 277, 179, 223}));
}

}