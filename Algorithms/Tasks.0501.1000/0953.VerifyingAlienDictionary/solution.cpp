#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isAlienSorted(std::vector<std::string> const &words, std::string const &order) const
    {
        const std::array<char, AlphabetSize> transformTable(generateTransformTable(order));
        std::string previous;
        for (std::string const &word : words)
        {
            std::string current(transformWord(word, transformTable));
            if (current < previous)
                return false;
            previous = current;
        }
        return true;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    [[nodiscard]] std::array<char, AlphabetSize> generateTransformTable(std::string const &order) const
    {
        std::array<char, AlphabetSize> transformTable{};
        for (size_t index = 0; index < order.size(); ++index)
            transformTable[order[index] - AlphabetStart] = static_cast<char>(AlphabetStart + index);
        return transformTable;
    }

    [[nodiscard]] std::string transformWord(std::string const &word, std::array<char, AlphabetSize> const &transformTable) const
    {
        std::string dest(word.size(), ' ');
        for (size_t index = 0; index < word.size(); ++index)
            dest[index] = transformTable[word[index] - AlphabetStart];
        return dest;
    }
};

}

namespace VerifyingAlienDictionaryTask
{

TEST(VerifyingAlienDictionaryTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isAlienSorted({"hello", "leetcode"}, "hlabcdefgijkmnopqrstuvwxyz"));
    ASSERT_EQ(false, solution.isAlienSorted({"word", "world", "row"}, "worldabcefghijkmnpqstuvxyz"));
    ASSERT_EQ(false, solution.isAlienSorted({"apple", "app"}, "abcdefghijklmnopqrstuvwxyz"));
}

}