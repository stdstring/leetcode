#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minDistance(std::string const &word1, std::string const &word2) const
    {
        std::vector<std::vector<int>> editDistance(word1.size() + 1, std::vector<int>(word2.size() + 1, 0));
        for (size_t index = 1; index <= word1.size(); ++index)
            editDistance[index][0] = editDistance[index - 1][0] + 1;
        for (size_t index = 1; index <= word2.size(); ++index)
            editDistance[0][index] = editDistance[0][index - 1] + 1;
        for (size_t index1 = 1; index1 <= word1.size(); ++index1)
        {
            for (size_t index2 = 1; index2 <= word2.size(); ++index2)
            {
                if (word1[index1 - 1] == word2[index2 - 1])
                    editDistance[index1][index2] = editDistance[index1-1][index2-1];
                else
                    editDistance[index1][index2] = min(editDistance[index1 - 1][index2], editDistance[index1][index2 - 1], editDistance[index1 - 1][index2 - 1]) + 1;
            }
        }
        return editDistance.back().back();
    }

private:
    int min(int a, int b, int c) const
    {
        return a <= b && a <= c ? a : (b <= c ? b : c);
    }
};

}

namespace EditDistanceTask
{

TEST(EditDistanceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.minDistance("horse", "ros"));
    ASSERT_EQ(5, solution.minDistance("intention", "execution"));
}

}