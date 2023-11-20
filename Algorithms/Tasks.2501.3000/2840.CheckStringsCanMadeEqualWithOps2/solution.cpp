#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkStrings(std::string const &s1, std::string const &s2) const
    {
        return compareLetterData(generateLetterData(s1, 0), generateLetterData(s2, 0)) &&
               compareLetterData(generateLetterData(s1, 1), generateLetterData(s2, 1));
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    [[nodiscard]] std::vector<size_t> generateLetterData(std::string const &source, size_t start) const
    {
        std::vector<size_t> letterData(AlphabetSize, 0);
        for (size_t index = start; index < source.size(); index += 2)
            ++letterData[source[index] - AlphabetStart];
        return letterData;
    }

    [[nodiscard]] bool compareLetterData(std::vector<size_t> const &left, std::vector<size_t> const &right) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (left[index] != right[index])
                return false;
        }
        return true;
    }
};

}

namespace CheckStringsCanMadeEqualWithOps2Task
{

TEST(CheckStringsCanMadeEqualWithOps2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkStrings("abcdba", "cabdab"));
    ASSERT_EQ(false, solution.checkStrings("abe", "bea"));
}

}