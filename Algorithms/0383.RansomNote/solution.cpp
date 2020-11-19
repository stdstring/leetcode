#include <array>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool canConstruct(std::string const &ransomNote, std::string const &magazine) const
    {
        std::array<size_t, AlphabetSize> ransomNoteData = createUsedLettersData(ransomNote);
        std::array<size_t, AlphabetSize> magazineData = createUsedLettersData(magazine);
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (ransomNoteData[index] > magazineData[index])
                return false;
        }
        return true;
    }

private:
    static constexpr size_t AlphabetSize = 26;

    std::array<size_t, AlphabetSize> createUsedLettersData(std::string const &source) const
    {
        std::array<size_t, AlphabetSize> usedLettersData{};
        usedLettersData.fill(0);
        for (char ch : source)
            ++usedLettersData[ch - 'a'];
        return usedLettersData;
    }
};

}

namespace RansomNoteTask
{

TEST(RansomNoteTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.canConstruct("a", "b"));
    ASSERT_EQ(false, solution.canConstruct("aa", "ab"));
    ASSERT_EQ(true, solution.canConstruct("aa", "aab"));
}

}
