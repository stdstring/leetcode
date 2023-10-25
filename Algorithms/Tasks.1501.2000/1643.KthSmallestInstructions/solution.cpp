#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string kthSmallestPath(std::vector<int> const &destination, int k) const
    {
        const int rowCount = destination[0];
        const int columnCount = destination[1];
        const std::vector<std::vector<int>> binomialCoefficients(generateBinomialCoefficients(rowCount + columnCount));
        std::string result(rowCount + columnCount, 'H');
        int verticalSegmentCount = rowCount;
        for (int index = 0; index < rowCount + columnCount; ++index)
        {
            if (k <= 1)
                break;
            const int position = rowCount + columnCount - index;
            const int nextPositionCombinations = binomialCoefficients[position - 1][verticalSegmentCount];
            if (nextPositionCombinations < k)
            {
                k -= nextPositionCombinations;
                --verticalSegmentCount;
                result[index] = 'V';
            }
        }
        for (int verticalSegment = 1; verticalSegment <= verticalSegmentCount; ++verticalSegment)
            result[rowCount + columnCount - verticalSegment] = 'V';
        return result;
    }

private:
    [[nodiscard]] std::vector<std::vector<int>> generateBinomialCoefficients(int maxN) const
    {
        std::vector<std::vector<int>> binomialCoefficients;
        binomialCoefficients.emplace_back(std::vector<int>({ 1 }));
        for (int n = 1; n <= maxN; ++n)
        {
            std::vector<int> currentRow;
            for (int k = 0; k <= n; ++k)
            {
                int current = (k > 0 ? binomialCoefficients.back()[k - 1] : 0) + (k < n ? binomialCoefficients.back()[k] : 0);
                currentRow.emplace_back(current);
            }
            binomialCoefficients.emplace_back(currentRow);
        }
        return binomialCoefficients;
    }
};

}

namespace KthSmallestInstructionsTask
{

TEST(KthSmallestInstructionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("HHHVV", solution.kthSmallestPath({2, 3}, 1));
    ASSERT_EQ("HHVHV", solution.kthSmallestPath({2, 3}, 2));
    ASSERT_EQ("HHVVH", solution.kthSmallestPath({2, 3}, 3));
}

}