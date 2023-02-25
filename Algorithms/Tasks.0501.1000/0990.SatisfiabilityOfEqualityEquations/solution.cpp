#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool equationsPossible(std::vector<std::string> const &equations) const
    {
        std::array<size_t, AlphabetSize> leaders{};
        for (size_t index = 0; index < leaders.size(); ++index)
            leaders[index] = index;
        // process equalities
        for (std::string const &equation : equations)
        {
            if (equation[1] != '=')
                continue;
            if (equation[0] == equation[3])
                continue;
            setLeader(leaders, equation[0], equation[3]);
        }
        // check inequalities
        for (std::string const &equation : equations)
        {
            if (equation[1] != '!')
                continue;
            if (equation[0] == equation[3])
                return false;
            if (leaders[equation[0] - AlphabetStart] == leaders[equation[3] - AlphabetStart])
                return false;
        }
        return true;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    void setLeader(std::array<size_t, AlphabetSize> &leaders, char variableA, char variableB) const
    {
        const size_t leaderA = leaders[variableA - AlphabetStart];
        const size_t leaderB = leaders[variableB - AlphabetStart];
        if (leaderA == leaderB)
            return;
        for (size_t index = 0; index < leaders.size(); ++index)
        {
            if (leaders[index] == std::max(leaderA, leaderB))
                leaders[index] = std::min(leaderA, leaderB);
        }
    }
};

}

namespace SatisfiabilityOfEqualityEquationsTask
{

TEST(SatisfiabilityOfEqualityEquationsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.equationsPossible({"a==b", "b!=a"}));
    ASSERT_EQ(true, solution.equationsPossible({"b==a", "a==b"}));
}

}