#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findMinDifference(std::vector<std::string> const &timePoints) const
    {
        std::vector<int> minutes;
        std::transform(timePoints.begin(), timePoints.end(), std::back_inserter(minutes), [](std::string const &source){ return 60 * stoi(source) + stoi(source.substr(3)); });
        std::sort(minutes.begin(), minutes.end());
        int minDifference = minutes.front() + 24 * 60 - minutes.back();
        for (size_t index = 1; index < minutes.size(); ++index)
            minDifference = std::min(minDifference, minutes[index] - minutes[index - 1]);
        return minDifference;
    }
};

}

namespace MinimumTimeDifferenceTask
{

TEST(MinimumTimeDifferenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.findMinDifference({"23:59", "00:00"}));
}

}