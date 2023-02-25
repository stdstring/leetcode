#include <algorithm>
#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{


class Solution
{
public:
    std::vector<std::string> commonChars(std::vector<std::string> const &words) const
    {
        // init
        std::array<size_t, AlphabetSize> commonCharData(createCharData(words[0]));
        // process other
        for (size_t index = 1; index < words.size(); ++index)
            intersectCharData(commonCharData, createCharData(words[index]));
        // create result
        std::vector<std::string> result;
        for (size_t index = 0; index < commonCharData.size(); ++index)
        {
            if (commonCharData[index] > 0)
                addLetter(result, std::string(1, static_cast<char>(AlphabetStart + index)), commonCharData[index]);
        }
        return result;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    std::array<size_t, AlphabetSize> createCharData(std::string const &source) const
    {
        std::array<size_t, AlphabetSize> charData{};
        charData.fill(0);
        for (char ch : source)
            ++charData[ch - AlphabetStart];
        return charData;
    }

    void intersectCharData(std::array<size_t, AlphabetSize> &dest, std::array<size_t, AlphabetSize> const &other) const
    {
        for (size_t index = 0; index < dest.size(); ++index)
            dest[index] = std::min(dest[index], other[index]);
    }

    void addLetter(std::vector<std::string> &result, std::string const &letter, size_t count) const
    {
        for (size_t index = 0; index < count; ++index)
            result.push_back(letter);
    }
};

}

namespace FindCommonCharactersTask
{

TEST(FindCommonCharactersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"e", "l", "l"}), solution.commonChars({"bella", "label", "roller"}));
    ASSERT_EQ(std::vector<std::string>({"c", "o"}), solution.commonChars({"cool", "lock", "cook"}));
}

}