#include <vector>

#include "gtest/gtest.h"

namespace
{

int sqr(int value)
{
    return value * value;
}

int scalarProduct(std::vector<int> const &p1Start, std::vector<int> const &p1End, std::vector<int> const &p2Start, std::vector<int> const &p2End)
{
    return (p1End[0] - p1Start[0]) * (p2End[0] - p2Start[0]) + (p1End[1] - p1Start[1]) * (p2End[1] - p2Start[1]);
}

class Solution
{
public:
    bool validSquare(std::vector<int> const &p1, std::vector<int> const &p2, std::vector<int> const &p3, std::vector<int> const &p4) const
    {
        const int p1p2Square = sqr(p2[0] - p1[0]) + sqr(p2[1] - p1[1]);
        const int p1p3Square = sqr(p3[0] - p1[0]) + sqr(p3[1] - p1[1]);
        const int p1p4Square = sqr(p4[0] - p1[0]) + sqr(p4[1] - p1[1]);
        const int p2p3Square = sqr(p3[0] - p2[0]) + sqr(p3[1] - p2[1]);
        const int p2p4Square = sqr(p4[0] - p2[0]) + sqr(p4[1] - p2[1]);
        const int p3p4Square = sqr(p4[0] - p3[0]) + sqr(p4[1] - p3[1]);
        if (p1p2Square == p1p3Square && p1p2Square == p2p4Square && p1p3Square == p3p4Square && p1p4Square == p2p3Square && p1p4Square > p1p2Square)
            return (scalarProduct(p1, p2, p1, p3) == 0) &&
                   (scalarProduct(p1, p2, p2, p4) == 0) &&
                   (scalarProduct(p1, p3, p3, p4) == 0) &&
                   (scalarProduct(p2, p4, p3, p4) == 0);
        if (p1p2Square == p1p4Square &&  p1p2Square == p2p3Square && p1p4Square == p3p4Square && p1p3Square == p2p4Square && p1p3Square > p1p2Square)
            return (scalarProduct(p1, p2, p1, p4) == 0) &&
                   (scalarProduct(p1, p2, p2, p3) == 0) &&
                   (scalarProduct(p1, p4, p4, p3) == 0) &&
                   (scalarProduct(p2, p3, p4, p3) == 0);
        if (p1p3Square == p1p4Square && p1p3Square == p2p3Square && p1p4Square == p2p4Square && p1p2Square == p3p4Square && p1p2Square > p1p3Square)
            return (scalarProduct(p1, p3, p1, p4) == 0) &&
                   (scalarProduct(p1, p3, p3, p2) == 0) &&
                   (scalarProduct(p1, p4, p4, p2) == 0) &&
                   (scalarProduct(p3, p2, p4, p2) == 0);
        return false;
    }
};

}

namespace ValidSquareTask
{

TEST(ValidSquareTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.validSquare({0, 0}, {1, 1}, {1, 0}, {0, 1}));
    ASSERT_EQ(false, solution.validSquare({0, 0}, {1, 1}, {1, 0}, {0, 12}));
    ASSERT_EQ(true, solution.validSquare({1, 0}, {-1, 0}, {0, 1}, {0, -1}));
}

TEST(ValidSquareTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.validSquare({0, 0}, {0, 0}, {0, 0}, {0, 0}));
}

}