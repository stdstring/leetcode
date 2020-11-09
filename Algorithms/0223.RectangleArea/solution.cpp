#include <algorithm>

#include "gtest/gtest.h"

namespace
{


class Solution
{
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) const
    {
        const long long rect1Area = (C - A) * (D - B);
        const long long rect2Area = (G - E) * (H - F);
        const long long intersectionArea = computeIntersectionArea(A, B, C, D, E, F, G, H);
        return static_cast<int>(rect1Area + rect2Area - intersectionArea);
    }

private:
    int computeIntersectionArea(int A, int B, int C, int D, int E, int F, int G, int H) const
    {
        if (B >= H)
            return 0;
        if (F >= D)
            return 0;
        if (E >= C)
            return 0;
        if (A >= G)
            return 0;
        return (std::min(G, C) - std::max(E, A)) * (std::min(H, D) - std::max(F, B));
    }
};

}

namespace RectangleAreaTask
{

TEST(RectangleAreaTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(45, solution.computeArea(-3, 0, 3, 4, 0, -1, 9, 2));
}

TEST(RectangleAreaTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2000000000, solution.computeArea(0, 0, 50000, 40000, 0, 0, 50000, 40000));
}

}