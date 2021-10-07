#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countCharacters(std::vector<std::string> const &words, std::string const &chars) const
    {
        size_t totalSize = 0;
        const std::array<size_t, AlphabetSize> charsData(createLetterData(chars));
        for (std::string const &word : words)
        {
            if (isSubset(charsData, createLetterData(word)))
                totalSize += word.size();
        }
        return static_cast<int>(totalSize);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    std::array<size_t, AlphabetSize> createLetterData(std::string const &str) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (const char ch : str)
            ++letterData[ch - AlphabetStart];
        return letterData;
    }

    bool isSubset(std::array<size_t, AlphabetSize> const &sourceSet, std::array<size_t, AlphabetSize> const &checkedSet) const
    {
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (sourceSet[index] < checkedSet[index])
                return false;
        }
        return true;
    }
};

}

namespace FindWordsThatCanBeFormedByCharsTask
{

TEST(FindWordsThatCanBeFormedByCharsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.countCharacters({"cat", "bt", "hat", "tree"}, "atach"));
    ASSERT_EQ(10, solution.countCharacters({"hello", "world", "leetcode"}, "welldonehoneyr"));
}

}