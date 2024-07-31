#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minHeightShelves(std::vector<std::vector<int>> const &books, int shelfWidth) const
    {
        std::vector<int> dp(books.size(), INT_MAX);
        for (size_t start = 0; start < books.size(); ++start)
        {
            const int prevHeight = start > 0 ? dp[start - 1] : 0;
            int currentHeight = 0;
            int currentWidth = 0;
            for (size_t index = start; (index < books.size()) && ((currentWidth + books[index][0]) <= shelfWidth); ++index)
            {
                currentHeight = std::max(currentHeight, books[index][1]);
                currentWidth += books[index][0];
                dp[index] = std::min(dp[index], prevHeight + currentHeight);
            }
        }
        return dp.back();
    }
};

}

namespace FillingBookcaseShelvesTask
{

TEST(FillingBookcaseShelvesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minHeightShelves({{1, 1}, {2, 3}, {2, 3}, {1, 1}, {1, 1}, {1, 1}, {1, 2}}, 4));
    ASSERT_EQ(4, solution.minHeightShelves({{1, 3}, {2, 4}, {3, 2}}, 6));
}

}