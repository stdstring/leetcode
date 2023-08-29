#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int digArtifacts(int n, std::vector<std::vector<int>> const &artifacts, std::vector<std::vector<int>> const &dig) const
    {
        std::vector<bool> field(1ULL * n * n, false);
        for (std::vector<int> const &digPos : dig)
            field[digPos[0] * n + digPos[1]] = true;
        auto predicate = [n, &field](std::vector<int> const& artifact) { return canDigArtifact(n, artifact, field); };
        return static_cast<int>(std::ranges::count_if(artifacts, predicate));
    }

private:
    [[nodiscard]] static bool canDigArtifact(int n, std::vector<int> const &artifact, std::vector<bool> const &field)
    {
        const int topRow = artifact[0];
        const int leftColumn = artifact[1];
        const int bottomRow = artifact[2];
        const int rightColumn = artifact[3];
        for (int row = topRow; row <= bottomRow; ++row)
        {
            for (int column = leftColumn; column <= rightColumn; ++column)
            {
                if (!field[row * n + column])
                    return false;
            }
        }
        return true;
    }
};

}

namespace CountArtifactsThatCanBeExtractedTask
{

TEST(CountArtifactsThatCanBeExtractedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.digArtifacts(2, {{0, 0, 0, 0}, {0, 1, 1, 1}}, {{0, 0}, {0, 1}}));
    ASSERT_EQ(2, solution.digArtifacts(2, {{0, 0, 0, 0}, {0, 1, 1, 1}}, {{0, 0}, {0, 1}, {1, 1}}));
}

}