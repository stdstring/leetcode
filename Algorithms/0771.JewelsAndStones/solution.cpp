#include <string>
#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numJewelsInStones(std::string const &jewels, std::string const &stones) const
    {
        std::unordered_set<char> jewelsSet;
        for (char ch : jewels)
            jewelsSet.insert(ch);
        size_t jewelsCount = 0;
        for (char ch : stones)
        {
            if (jewelsSet.count(ch) != 0)
                ++jewelsCount;
        }
        return static_cast<int>(jewelsCount);
    }
};

}

namespace JewelsAndStonesTask
{

TEST(JewelsAndStonesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numJewelsInStones("aA", "aAAbbbb"));
    ASSERT_EQ(0, solution.numJewelsInStones("z", "ZZ"));
}

}