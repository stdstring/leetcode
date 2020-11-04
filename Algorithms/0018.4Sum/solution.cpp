#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> fourSum(std::vector<int> const &nums, int target) const
    {
        std::vector<std::vector<int>> dest;
        std::vector<int> source(nums.begin(), nums.end());
        std::sort(source.begin(), source.end());
        size_t firstIndex = 0;
        while ((firstIndex + 3) < source.size())
        {
            const int a = source[firstIndex];
            size_t secondIndex = firstIndex + 1;
            while ((secondIndex + 2) < source.size())
            {
                const int b = source[secondIndex];
                size_t thirdIndex = secondIndex + 1;
                size_t fourthIndex = source.size() - 1;
                while (thirdIndex < fourthIndex)
                {
                    const int c = source[thirdIndex];
                    const int d = source[fourthIndex];
                    const int sum = a + b + c + d;
                    if (sum == target)
                    {
                        dest.push_back({a, b, c, d});
                        thirdIndex = nextItemIndex(source, thirdIndex);
                    }
                    else if (sum < target)
                        thirdIndex = nextItemIndex(source, thirdIndex);
                    else if (sum > target)
                        --fourthIndex;
                }
                secondIndex = nextItemIndex(source, secondIndex);
            }
            firstIndex = nextItemIndex(source, firstIndex);
        }
        return dest;
    }

private:
    size_t nextItemIndex(std::vector<int> const &source, size_t currentIndex) const
    {
        const int currentValue = source[currentIndex];
        size_t nextIndex = currentIndex + 1;
        while (nextIndex < source.size() && currentValue == source[nextIndex])
            ++nextIndex;
        return nextIndex;
    }
};

}

namespace FourSumTask
{

TEST(FourSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{-2, -1, 1, 2}, {-2,  0, 0, 2}, {-1,  0, 0, 1}}), solution.fourSum({1, 0, -1, 0, -2, 2}, 0));
}

}