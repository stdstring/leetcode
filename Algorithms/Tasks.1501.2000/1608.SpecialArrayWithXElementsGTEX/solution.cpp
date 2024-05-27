#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int specialArray(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        const int numberCount = static_cast<int>(nums.size());
        if (numbers.front() >= numberCount)
            return numberCount;
        for (int numberIndex = 1; numberIndex < numberCount; ++numberIndex)
        {
            const int numberRestCount = numberCount - numberIndex;
            if (numbers[numberIndex - 1] >= numberRestCount)
                break;
            if (numbers[numberIndex] >= numberRestCount)
                return numberRestCount;
        }
        return -1;
    }
};

}

namespace SpecialArrayWithXElementsGTEXTask
{

TEST(SpecialArrayWithXElementsGTEXTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.specialArray({3, 5}));
    ASSERT_EQ(-1, solution.specialArray({0, 0}));
    ASSERT_EQ(3, solution.specialArray({0, 4, 3, 0, 4}));
}

TEST(SpecialArrayWithXElementsGTEXTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(-1, solution.specialArray({3, 6, 7, 7, 0}));
}

}