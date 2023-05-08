#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> pancakeSort(std::vector<int> const &arr) const
    {
        std::vector<int> buffer(arr);
        std::vector<int> rotations;
        for (int element = static_cast<int>(buffer.size()); element > 0; --element)
        {
            const int elementPos = getPosition(buffer, element, element);
            if (element == elementPos)
                continue;
            std::reverse(buffer.begin(), std::next(buffer.begin(), elementPos));
            rotations.emplace_back(elementPos);
            std::reverse(buffer.begin(), std::next(buffer.begin(), element));
            rotations.emplace_back(element);
        }
        return rotations;
    }

private:
    [[nodiscard]] int getPosition(std::vector<int> const &source, int finishPos, int value) const
    {
        while (source[finishPos - 1] != value)
            --finishPos;
        return finishPos;
    }
};

}

namespace PancakeSortingTask
{

TEST(PancakeSortingTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 4, 2, 3, 1, 2}), solution.pancakeSort({3, 2, 4, 1}));
    ASSERT_EQ(std::vector<int>(), solution.pancakeSort({1, 2, 3}));
}

}