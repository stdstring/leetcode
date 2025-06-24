#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDeletions(std::string const& word, int k) const
    {
        const size_t maxDelta = k;
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<size_t> frequencies(alphabetSize, 0);
        for (const char ch : word)
            ++frequencies[ch - alphabetStart];
        size_t minDelete = word.size();
        for (size_t current = 0; current < alphabetSize; ++current)
        {
            if (frequencies[current] == 0)
                continue;
            size_t currentDelete = 0;
            for (size_t other = 0; other < alphabetSize; ++other)
            {
                if (frequencies[other] < frequencies[current])
                    currentDelete += frequencies[other];
                if (frequencies[other] > (frequencies[current] + maxDelta))
                    currentDelete += (frequencies[other] - frequencies[current] - maxDelta);
            }
            minDelete = std::min(minDelete, currentDelete);
        }
        return static_cast<int>(minDelete);
    }
};

}

namespace MinDeletionsMakeStringKSpecialTask
{

TEST(MinDeletionsMakeStringKSpecialTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumDeletions("aabcaba", 0));
    ASSERT_EQ(2, solution.minimumDeletions("dabdcbdcdcd", 2));
    ASSERT_EQ(1, solution.minimumDeletions("aaabaaa", 2));
}

TEST(MinDeletionsMakeStringKSpecialTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumDeletions("ddwddddwdddw", 1));
    ASSERT_EQ(3, solution.minimumDeletions("klllurlrrul", 1));
    ASSERT_EQ(3, solution.minimumDeletions("zzfzzzzppfp", 1));
    ASSERT_EQ(0, solution.minimumDeletions("k", 100000));
    ASSERT_EQ(2, solution.minimumDeletions("ahahnhahhah", 1));
    ASSERT_EQ(0, solution.minimumDeletions("xaaxxxaaax", 3));
    ASSERT_EQ(1, solution.minimumDeletions("vvnowvov", 2));
}

}