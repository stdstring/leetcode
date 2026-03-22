#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool findRotation(std::vector<std::vector<int>> const &mat, std::vector<std::vector<int>> const &target) const
    {
        if (isEqual(mat, target))
            return true;
        std::vector<std::vector<int>> current(mat);
        for (int rotation = 0; rotation < 4; ++rotation)
        {
            current = rotate(current);
            if (isEqual(current, target))
                return true;
        }
        return false;
    }

private:
    [[nodiscard]] std::vector<std::vector<int>> rotate(std::vector<std::vector<int>> const &source) const
    {
        const size_t n = source.size();
        std::vector<std::vector<int>> dest(n, std::vector<int>(n, 0));
        for (size_t row = 0; row < n; ++row)
        {
            for (size_t column = 0; column < n; ++column)
            {
                dest[n - 1 - column][row] = source[row][column];
            }
        }
        return dest;
    }

    [[nodiscard]] bool isEqual(std::vector<std::vector<int>> const &source, std::vector<std::vector<int>> const &target) const
    {
        const size_t n = source.size();
        for (size_t row = 0; row < n; ++row)
        {
            for (size_t column = 0; column < n; ++column)
            {
                if (source[row][column] != target[row][column])
                    return false;
            }
        }
        return true;
    }
};

}

namespace CanMatrixBeObtainedByRotationTask
{

TEST(CanMatrixBeObtainedByRotationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.findRotation({{0, 1}, {1, 0}}, {{1, 0}, {0, 1}}));
    ASSERT_EQ(false, solution.findRotation({{0, 1}, {1, 1}}, {{1, 0}, {0, 1}}));
    ASSERT_EQ(true, solution.findRotation({{0, 0, 0}, {0, 1, 0}, {1, 1, 1}}, {{1, 1, 1}, {0, 1, 0}, {0, 0, 0}}));
}

}