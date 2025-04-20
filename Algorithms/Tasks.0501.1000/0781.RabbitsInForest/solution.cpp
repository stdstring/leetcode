#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numRabbits(std::vector<int> const &answers) const
    {
        std::unordered_map<int, size_t> answerMap;
        for (int answer : answers)
            ++answerMap[answer];
        // Use a grouping factor defined as element + 1
        size_t result = 0;
        for (auto [element, count] : answerMap)
        {
            const size_t groupFactor = element + 1;
            const size_t groupCount = (count / groupFactor) + ((count % groupFactor == 0) ? 0 : 1);
            result += groupFactor * groupCount;
        }
        return static_cast<int>(result);
    }
};

}

namespace RabbitsInForestTask
{

TEST(RabbitsInForestTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.numRabbits({1, 1, 2}));
    ASSERT_EQ(11, solution.numRabbits({10, 10, 10}));
}

}