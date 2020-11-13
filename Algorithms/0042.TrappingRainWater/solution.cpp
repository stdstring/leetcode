#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Brick
{
    Brick(int w, int h) : width(w), height(h)
    {
    }

    int width;
    int height;
};

class Solution
{
public:
    int trap(std::vector<int> const &heights) const
    {
        int volume = 0;
        std::stack<Brick> bricks;
        int maxHeight = 0;
        for (int height : heights)
        {
            if (bricks.empty() || bricks.top().height > height)
                bricks.emplace(1, height);
            else if (bricks.top().height == height)
                ++bricks.top().width;
            else
                volume += calcVolume(bricks, height, maxHeight);
            maxHeight = std::max(maxHeight, height);
        }
        return volume;
    }

private:
    int calcVolume(std::stack<Brick> &bricks, int height, int maxHeight) const
    {
        const int suitableHeight = std::min(height, maxHeight);
        int volume = 0;
        int width = 0;
        while (!bricks.empty() && bricks.top().height < suitableHeight)
        {
            width += bricks.top().width;
            volume += bricks.top().width * (suitableHeight - bricks.top().height);
            bricks.pop();
        }
        if (!bricks.empty() && bricks.top().height == height)
            bricks.top().width += (width + 1);
        else
        {
            if (!bricks.empty() && bricks.top().height < height)
                bricks.pop();
            bricks.emplace(maxHeight < height ? 1 : width + 1, height);
        }
        return volume;
    }
};

}

namespace TrappingRainWaterTask
{

TEST(TrappingRainWaterTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.trap({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}));
    ASSERT_EQ(9, solution.trap({4, 2, 0, 3, 2, 5}));
}

}