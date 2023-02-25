#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string pushDominoes(std::string const &dominoes) const
    {
        std::string result(dominoes.size(), '.');
        size_t index = 0;
        while (index < dominoes.size())
        {
            if (dominoes[index] == 'L')
            {
                result[index++] = 'L';
                continue;
            }
            size_t nextIndex = index + 1;
            while ((nextIndex < dominoes.size()) && (dominoes[nextIndex] == '.'))
                ++nextIndex;
            if (nextIndex == dominoes.size())
            {
                if (dominoes[index] == 'R')
                    fill(result, index, dominoes.size() - 1, 'R');
                index = nextIndex;
            }
            else
            {
                if (dominoes[nextIndex] == 'R')
                {
                    if (dominoes[index] == 'R')
                        fill(result, index, nextIndex - 1, 'R');
                    index = nextIndex;
                    continue;
                }
                if ((dominoes[index] == '.') && (dominoes[nextIndex] == 'L'))
                    fill(result, index, nextIndex, 'L');
                if ((dominoes[index] == 'R') && (dominoes[nextIndex] == 'L'))
                {
                    const size_t size = nextIndex - index + 1;
                    fill(result, index, index + (size / 2) - 1, 'R');
                    fill(result, nextIndex - (size / 2) + 1, nextIndex, 'L');
                }
                index = nextIndex + 1;
            }
        }
        return result;
    }

private:
    void fill(std::string &result, size_t fromIndex, size_t toIndex, char fillChar) const
    {
        for (size_t index = fromIndex; index <= toIndex; ++index)
            result[index] = fillChar;
    }
};

}

namespace PushDominoesTask
{

TEST(PushDominoesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("LL.RR.LLRRLL..", solution.pushDominoes(".L.R...LR..L.."));
    ASSERT_EQ("RR.L", solution.pushDominoes("RR.L"));
}

}