#include <array>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countVowelStrings(int n) const
    {
        const size_t vowelCount = 5;
        const size_t vowelA = 0;
        const size_t vowelE = 1;
        const size_t vowelI = 2;
        const size_t vowelO = 3;
        const size_t vowelU = 4;
        std::array<size_t, vowelCount> countData{};
        countData.fill(1);
        for (size_t length = 1; length < static_cast<size_t>(n); ++length)
        {
            // a -> aa, ae, ai, ao, au
            // e -> ee, ei, eo, eu
            // i -> ii, io, iu
            // o -> oo, ou
            // u -> uu
            countData[vowelU] = countData[vowelA] + countData[vowelE] + countData[vowelI] + countData[vowelO] + countData[vowelU];
            countData[vowelO] = countData[vowelA] + countData[vowelE] + countData[vowelI] + countData[vowelO];
            countData[vowelI] = countData[vowelA] + countData[vowelE] + countData[vowelI];
            countData[vowelE] = countData[vowelA] + countData[vowelE];
        }
        return static_cast<int>(countData[vowelA] + countData[vowelE] + countData[vowelI] + countData[vowelO] + countData[vowelU]);
    }
};

}

namespace CountSortedVowelStringsTask
{

TEST(CountSortedVowelStringsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.countVowelStrings(1));
    ASSERT_EQ(15, solution.countVowelStrings(2));
    ASSERT_EQ(66045, solution.countVowelStrings(33));
}

}