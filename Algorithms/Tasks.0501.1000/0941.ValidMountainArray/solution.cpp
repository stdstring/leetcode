#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool validMountainArray(std::vector<int> const &arr) const
    {
        if (arr.size() < 3)
            return false;
        if (arr[0] > arr[1])
            return false;
        bool hasPeak = false;
        for (size_t index = 1; index < arr.size(); ++index)
        {
            if (arr[index] == arr[index - 1])
                return false;
            if (hasPeak && arr[index] > arr[index - 1])
                return false;
            if (index < arr.size() - 1 && arr[index] > arr[index - 1] && arr[index] > arr[index + 1])
                hasPeak = true;
        }
        return hasPeak;
    }
};

}

namespace ValidMountainArrayTask
{

TEST(ValidMountainArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.validMountainArray({2, 1}));
    ASSERT_EQ(false, solution.validMountainArray({3, 5, 5}));
    ASSERT_EQ(true, solution.validMountainArray({0, 3, 2, 1}));
}

TEST(ValidMountainArrayTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.validMountainArray({2, 0, 2}));
    ASSERT_EQ(false, solution.validMountainArray({0, 1, 2, 1, 2}));
    ASSERT_EQ(false, solution.validMountainArray({3, 7, 6, 4, 3, 0, 1, 0}));
    ASSERT_EQ(false, solution.validMountainArray({2, 1, 2, 3, 5, 7, 9, 10, 12, 14, 15, 16, 18, 14, 13}));
}

}