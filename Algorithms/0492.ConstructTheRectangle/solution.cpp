#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> constructRectangle(int area) const
    {
        int width = 1;
        int length = area;
        int number = 2;
        while ((number * number) <= area)
        {
            if ((area % number) == 0)
            {
                width = number;
                length = area / number;
            }
            ++number;
        }
        return {length, width};
    }
};

}

namespace ConstructTheRectangleTask
{

TEST(ConstructTheRectangleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 2}), solution.constructRectangle(4));
}

}