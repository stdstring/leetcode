#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> threeSum(std::vector<int> const &nums)
    {
        std::vector<std::vector<int>> dest;
        std::vector<int> source(nums.begin(), nums.end());
        std::sort(source.begin(), source.end());
        size_t firstIndex = 0;
        while ((firstIndex + 2 < source.size()) && (source[firstIndex] <= 0))
        {
            const int a = source[firstIndex];
            size_t secondIndex = firstIndex + 1;
            size_t thirdIndex = source.size() - 1;
            while (secondIndex < thirdIndex)
            {
                const int b = source[secondIndex];
                const int c = source[thirdIndex];
                const int sum = a + b + c;
                if (sum == 0)
                {
                    dest.push_back({a, b, c});
                    secondIndex = nextItemIndex(source, secondIndex);
                }
                else if (sum < 0)
                {
                    secondIndex = nextItemIndex(source, secondIndex);
                }
                else if (sum > 0)
                {
                    --thirdIndex;
                }
            }
            firstIndex = nextItemIndex(source, firstIndex);
        }
        return dest;
    }

private:
    int nextItemIndex(std::vector<int> const &source, size_t currentIndex)
    {
        const int currentValue = source[currentIndex];
        size_t nextIndex = currentIndex + 1;
        while ((nextIndex < source.size()) && (currentValue == source[nextIndex]))
            ++nextIndex;
        return nextIndex;
    }
};

}

namespace ThreeSumTask
{

TEST(ThreeSumTaskTests, Examples)
{
    Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{-1, -1, 2}, {-1, 0, 1}}), solution.threeSum({-1, 0, 1, 2, -1, -4}));
}

}