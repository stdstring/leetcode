#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int triangleNumber(std::vector<int> const &nums) const
    {
        if (nums.size() < 3)
            return 0;
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        size_t count = 0;
        for (size_t index1 = 0; index1 < numbers.size() - 2; ++index1)
        {
            if (numbers[index1] == 0)
                continue;
            size_t index3End = 0;
            for (size_t index2 = index1 + 1; index2 < numbers.size() - 1; ++index2)
            {
                while ((index3End < numbers.size()) && (numbers[index1] + numbers[index2] > numbers[index3End]))
                    ++index3End;
                count += (index3End - index2 - 1);
            }
        }
        return static_cast<int>(count);
    }
};

}

namespace ValidTriangleNumberTask
{

TEST(ValidTriangleNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.triangleNumber({2, 2, 3, 4}));
}

TEST(ValidTriangleNumberTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.triangleNumber({1}));
}

}