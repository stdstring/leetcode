#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numDistinct(std::string const &s, std::string const &t) const
    {
        std::vector<size_t> subsequences(t.size(), 0);
        for (char ch : s)
        {
            for (size_t rIndex = 0; rIndex < subsequences.size(); ++rIndex)
            {
                const size_t index = subsequences.size() - 1 - rIndex;
                if (index == (t.size() - 1))
                    continue;
                if (t[index + 1] == ch)
                    subsequences[index + 1] += subsequences[index];
            }
            if (t[0] == ch)
                subsequences[0] += 1;
        }
        return static_cast<int>(subsequences.back());
    }
};

}

namespace DistinctSubsequencesTask
{

TEST(DistinctSubsequencesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numDistinct("rabbbit", "rabbit"));
    ASSERT_EQ(5, solution.numDistinct("babgbag", "bag"));
}

}