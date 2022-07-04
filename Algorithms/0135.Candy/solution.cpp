#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int candy(std::vector<int> const &ratings) const
    {
        std::vector<size_t> candies(ratings.size(), 0);
        for (size_t index = 0; index < ratings.size(); ++index)
        {
            if (candies[index] == 0)
                processChild(index, ratings, candies);
        }
        return static_cast<int>(std::accumulate(candies.cbegin(), candies.cend(), 0ULL));
    }

private:
    void processChild(size_t index, std::vector<int> const &ratings, std::vector<size_t> &candies) const
    {
        size_t candiesCount = 1;
        if ((index > 0) && (ratings[index - 1] < ratings[index]))
        {
            if (candies[index - 1] == 0)
                processChild(index - 1, ratings, candies);
            candiesCount = std::max(candiesCount, candies[index - 1] + 1);
        }
        if ((index < ratings.size() - 1) && (ratings[index + 1] < ratings[index]))
        {
            if (candies[index + 1] == 0)
                processChild(index + 1, ratings, candies);
            candiesCount = std::max(candiesCount, candies[index + 1] + 1);
        }
        candies[index] = candiesCount;
    }
};

}

namespace CandyTask
{

TEST(CandyTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.candy({1, 0, 2}));
    ASSERT_EQ(4, solution.candy({1, 2, 2}));
}

}
