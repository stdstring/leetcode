#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int threeSumClosest(std::vector<int> const &nums, int target) const
    {
        std::vector<int> source(nums.begin(), nums.end());
        std::sort(source.begin(), source.end());
        int result = source[0] + source[1] + source[2];
        size_t firstIndex = 0;
        while ((firstIndex + 2) < source.size())
        {
            const int a = source[firstIndex];
            size_t secondIndex = firstIndex + 1;
            size_t thirdIndex = source.size() - 1;
            while (secondIndex < thirdIndex)
            {
                const int b = source[secondIndex];
                const int c = source[thirdIndex];
                const int sum = a + b + c;
                const int delta = sum - target;
                if (delta == 0)
                    return sum;
                if (abs(delta) < abs(result - target))
                    result = sum;
                if (delta < 0)
                    secondIndex = nextItemIndex(source, secondIndex);
                if (delta > 0)
                    --thirdIndex;
            }
            firstIndex = nextItemIndex(source, firstIndex);
        }
        return result;
    }

private:
    int nextItemIndex(std::vector<int> const &source, size_t currentIndex) const
    {
        const int currentValue = source[currentIndex];
        size_t nextIndex = currentIndex + 1;
        while ((nextIndex < source.size()) && (currentValue == source[nextIndex]))
            ++nextIndex;
        return nextIndex;
    }
};

}

namespace ThreeSumClosestTask
{

TEST(ThreeSumClosestTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.threeSumClosest({-1, 2, 1, -4}, 1));
}

}