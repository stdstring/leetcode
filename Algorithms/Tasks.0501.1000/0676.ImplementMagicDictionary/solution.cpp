#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class MagicDictionary
{
public:
    MagicDictionary() = default;

    void buildDict(std::vector<std::string> const &dictionary)
    {
        for (std::string const& word : dictionary)
            _words[word.size()].push_back(word);
    }

    [[nodiscard]] bool search(std::string const &searchWord) const
    {
        if (_words.count(searchWord.size()) == 0)
            return false;
        for (std::string const& word : _words.at(searchWord.size()))
        {
            if (calcDiff(searchWord, word) == 1)
                return true;
        }
        return false;
    }

private:
    [[nodiscard]] size_t calcDiff(std::string const& left, std::string const &right) const
    {
        size_t diff = 0;
        for (size_t index = 0; index < left.size(); ++index)
        {
            if (left[index] != right[index])
                ++diff;
        }
        return diff;
    }

    std::unordered_map<size_t, std::vector<std::string>> _words;
};

}

namespace
{

void checkMagicDictionary(std::vector<std::string> const &dictionary, std::vector<std::string> const &searchWords, std::vector<bool> const &expectedResults)
{
    MagicDictionary magicDictionary;
    ASSERT_NO_THROW(magicDictionary.buildDict(dictionary));
    for (size_t index = 0; index < searchWords.size(); ++index)
        ASSERT_EQ(expectedResults[index], magicDictionary.search(searchWords[index]));
}

}

namespace ImplementMagicDictionaryTask
{

TEST(ImplementMagicDictionaryTaskTests, Examples)
{
    checkMagicDictionary({"hello", "leetcode"}, {"hello", "hhllo", "hell", "leetcoded"}, {false, true, false, false});
}

TEST(ImplementMagicDictionaryTaskTests, FromWrongAnswers)
{
    checkMagicDictionary({"hello", "hallo", "leetcode"}, {"hello", "hhllo", "hell", "leetcoded"}, {true, true, false, false});
}

}