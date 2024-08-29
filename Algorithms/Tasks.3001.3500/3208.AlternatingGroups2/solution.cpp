#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfAlternatingGroups(std::vector<int> const &colors, int k) const
    {
        const size_t slidingWindow = k;
        size_t groupCount = 0;
        size_t prefixSize = 0;
        for (size_t start = 0; start < colors.size();)
        {
            size_t groupSize = calcAlternatingGroupSize(colors, slidingWindow, start, prefixSize);
            if (groupSize ==slidingWindow)
            {
                ++groupCount;
                prefixSize = slidingWindow - 1;
                ++start;
            }
            else
            {
                prefixSize = 0;
                start += groupSize;
            }
        }
        return static_cast<int>(groupCount);
    }

private:
    [[nodiscard]] size_t calcAlternatingGroupSize(std::vector<int> const &colors, size_t slidingWindow, size_t start, size_t prefixSize) const
    {
        for (size_t shift = (prefixSize == 0 ? 1 : prefixSize); shift < slidingWindow; ++shift)
        {
            size_t prevIndex = (start + shift - 1) % colors.size();
            size_t currentIndex = (start + shift) % colors.size();
            if (colors[prevIndex] == colors[currentIndex])
                return shift;
        }
        return slidingWindow;
    }
};

}

namespace AlternatingGroups2Task
{

TEST(AlternatingGroups2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numberOfAlternatingGroups({0, 1, 0, 1, 0}, 3));
    ASSERT_EQ(2, solution.numberOfAlternatingGroups({0, 1, 0, 0, 1, 0, 1}, 6));
    ASSERT_EQ(0, solution.numberOfAlternatingGroups({1, 1, 0, 1}, 4));
}

}