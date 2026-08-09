#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> validSequence(std::string const &word1, std::string const &word2) const
    {
        const int size1 = static_cast<int>(word1.size());
        const int size2 = static_cast<int>(word2.size());
        std::vector<int> lastWord2(word2.size(), -1);
        for (int index1 = size1 - 1, index2 = size2 - 1; (index1 >= 0) && (index2 >= 0); --index1)
        {
            if (word1[index1] == word2[index2])
            {
                lastWord2[index2] = index1;
                --index2;
            }
        }
        std::vector<int> result;
        bool canSkip = true;
        const int lastIndex2 = size2 - 1;
        for (int index1 = 0, index2 = 0; (index1 < size1) && (index2 < size2); ++index1)
        {
            if (word1[index1] == word2[index2])
            {
                result.emplace_back(index1);
                ++index2;
            }
            else if (canSkip && ((index2 == lastIndex2) || (index1 < lastWord2[index2 + 1])))
            {
                canSkip = false;
                result.emplace_back(index1);
                ++index2;
            }
        }
        if (result.size() != word2.size())
            return {};
        return std::vector<int>(std::move(result));
    }
};

}

namespace FindLexSmallestValidSequenceTask
{

TEST(FindLexSmallestValidSequenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 2}), solution.validSequence("vbcca", "abc"));
    ASSERT_EQ(std::vector<int>({1, 2, 4}), solution.validSequence("bacdc", "abc"));
    ASSERT_EQ(std::vector<int>(), solution.validSequence("aaaaaa", "aaabc"));
    ASSERT_EQ(std::vector<int>({0, 1}), solution.validSequence("abc", "ab"));
}

TEST(FindLexSmallestValidSequenceTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1}), solution.validSequence("cbbccc", "bb"));
    ASSERT_EQ(std::vector<int>({0, 2, 4}), solution.validSequence("cdbbcdddddbdddbcdbdbbbccbbc", "dbc"));
}

}