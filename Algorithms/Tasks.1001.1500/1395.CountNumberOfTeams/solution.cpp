#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numTeams(std::vector<int> const &rating) const
    {
        size_t teamCount = 0;
        for (size_t current = 1; current < rating.size() - 1; ++current)
        {
            size_t countBeforeLess = 0;
            size_t countBeforeGreater = 0;
            for (size_t index = 0; index < current; ++index)
            {
                if (rating[index] < rating[current])
                    ++countBeforeLess;
                if (rating[index] > rating[current])
                    ++countBeforeGreater;
            }
            size_t countAfterLess = 0;
            size_t countAfterGreater = 0;
            for (size_t index = current + 1; index < rating.size(); ++index)
            {
                if (rating[index] < rating[current])
                    ++countAfterLess;
                if (rating[index] > rating[current])
                    ++countAfterGreater;
            }
            teamCount += countBeforeLess * countAfterGreater;
            teamCount += countBeforeGreater * countAfterLess;
        }
        return static_cast<int>(teamCount);
    }
};

}

namespace CountNumberOfTeamsTask
{

TEST(CountNumberOfTeamsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numTeams({2, 5, 3, 4, 1}));
    ASSERT_EQ(0, solution.numTeams({2, 1, 3}));
    ASSERT_EQ(4, solution.numTeams({1, 2, 3, 4}));
}

}