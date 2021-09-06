#include <array>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string shortestCompletingWord(std::string const &licensePlate, std::vector<std::string> const &words) const
    {
        const std::array<size_t, AlphabetSize> sourceData(createLetterData(licensePlate));
        size_t bestCompletingWord = words.size();
        for (size_t index = 0; index < words.size(); ++index)
        {
            if (isCompletingWord(sourceData, words[index]) && (bestCompletingWord == words.size() || words[index].size() < words[bestCompletingWord].size()))
                bestCompletingWord = index;
        }
        return words[bestCompletingWord];
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    std::array<size_t, AlphabetSize> createLetterData(std::string const &source) const
    {
        std::array<size_t, AlphabetSize> letterData{};
        letterData.fill(0);
        for (char ch : source)
        {
            if (std::isalpha(ch))
                ++letterData[static_cast<size_t>(std::tolower(ch)) - AlphabetStart];
        }
        return letterData;
    }

    bool isCompletingWord(std::array<size_t, AlphabetSize> const &sourceData, std::string const &word) const
    {
        std::array<size_t, AlphabetSize> wordData(createLetterData(word));
        for (size_t index = 0; index < AlphabetSize; ++index)
        {
            if (sourceData[index] > wordData[index])
                return false;
        }
        return true;
    }
};

}

namespace ShortestCompletingWordTask
{

TEST(ShortestCompletingWordTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("steps", solution.shortestCompletingWord("1s3 PSt", {"step", "steps", "stripe", "stepple"}));
    ASSERT_EQ("pest", solution.shortestCompletingWord("1s3 456", {"looks", "pest", "stew", "show"}));
    ASSERT_EQ("husband", solution.shortestCompletingWord("Ah71752", {"suggest", "letter", "of", "husband", "easy", "education", "drug", "prevent", "writer", "old"}));
    ASSERT_EQ("enough", solution.shortestCompletingWord("OgEu755", {"enough", "these", "play", "wide", "wonder", "box", "arrive", "money", "tax", "thus"}));
    ASSERT_EQ("simple", solution.shortestCompletingWord("iMSlpe4", {"claim", "consumer", "student", "camera", "public", "never", "wonder", "simple", "thought", "use"}));
}

}
