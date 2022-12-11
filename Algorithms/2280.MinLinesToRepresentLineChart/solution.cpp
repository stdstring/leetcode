#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumLines(std::vector<std::vector<int>> const &stockPrices) const
    {
        if (stockPrices.size() < 2)
            return 0;
        std::vector<size_t> indices(stockPrices.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&stockPrices](size_t left, size_t right){ return stockPrices[left][0] < stockPrices[right][0]; });
        size_t linesCount = 1;
        for (size_t index = 2; index < indices.size(); ++index)
        {
            const long long prevDeltaX = stockPrices[indices[index - 1]][0] - stockPrices[indices[index - 2]][0];
            const long long currentDeltaX = stockPrices[indices[index]][0] - stockPrices[indices[index - 1]][0];
            const long long prevDeltaY = stockPrices[indices[index - 1]][1] - stockPrices[indices[index - 2]][1];
            const long long currentDeltaY = stockPrices[indices[index]][1] - stockPrices[indices[index - 1]][1];
            if (prevDeltaY * currentDeltaX != currentDeltaY * prevDeltaX)
                ++linesCount;
        }
        return static_cast<int>(linesCount);
    }
};

}

namespace MinLinesToRepresentLineChartTask
{

TEST(MinLinesToRepresentLineChartTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumLines({{1, 7}, {2, 6}, {3, 5}, {4, 4}, {5, 4}, {6, 3}, {7, 2}, {8, 1}}));
    ASSERT_EQ(1, solution.minimumLines({{3, 4}, {1, 2}, {7, 8}, {2, 3}}));
}

TEST(MinLinesToRepresentLineChartTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(11, solution.minimumLines({{701525690, 453694317},
                                         {954853451, 571451509},
                                         {691549168, 895570156},
                                         {765408118, 904408040},
                                         {230743058, 788990029},
                                         {817142128, 623576430},
                                         {312349756, 258258330},
                                         {998390174, 339475009},
                                         {700184025, 431308850},
                                         {558751425, 702072019},
                                         {190818738, 418700527},
                                         {112109100, 645793905}}));
}

}