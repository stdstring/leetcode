#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class WordDictionary
{
public:
    // Initialize your data structure here.
    WordDictionary() : _trie(1, std::vector<int>(AlphabetSize, 0))
    {
    }

    // Adds a word into the data structure.
    void addWord(std::string const &word)
    {
        size_t node = 0;
        for (size_t index = 0; index < word.size() - 1; ++index)
        {
            const size_t charIndex = word[index] - AlphabetStart;
            if (_trie[node][charIndex] == 0)
            {
                _trie[node][charIndex] = static_cast<int>(_trie.size());
                node = _trie.size();
                _trie.emplace_back(AlphabetSize, 0);
            }
            else if (_trie[node][charIndex] == WordEnd)
            {
                _trie[node][charIndex] = -static_cast<int>(_trie.size());
                node = _trie.size();
                _trie.emplace_back(AlphabetSize, 0);
            }
            else
                node = std::abs(_trie[node][charIndex]);
        }
        const size_t lastCharIndex = word.back() - AlphabetStart;
        if (_trie[node][lastCharIndex] == 0)
            _trie[node][lastCharIndex] = WordEnd;
        else if (_trie[node][lastCharIndex] > 0)
            _trie[node][lastCharIndex] = -_trie[node][lastCharIndex];
        else
            /* do nothing */;
    }

    // Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter.
    bool search(std::string const &word) const
    {
        return search(word, 0, 0);
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';
    static constexpr int WordEnd = INT_MIN;
    static constexpr char AnyChar = '.';
    std::vector<std::vector<int>> _trie;

    bool search(std::string const &word, size_t index, size_t node) const
    {
        if (index == word.size() - 1)
            return searchLastChar(word, node);
        if (word[index] == AnyChar)
        {
            auto predicate = [this, &word, index](int value) { return value != 0 && value != WordEnd && search(word, index + 1, std::abs(value)); };
            return std::any_of(_trie[node].cbegin(), _trie[node].cend(), predicate);
        }
        const size_t charIndex = word[index] - AlphabetStart;
        return _trie[node][charIndex] != 0 && _trie[node][charIndex] != WordEnd && search(word, index + 1, std::abs(_trie[node][charIndex]));
    }

    bool searchLastChar(std::string const &word, size_t node) const
    {
        if (word.back() == AnyChar)
            return std::any_of(_trie[node].cbegin(), _trie[node].cend(), [](int value) { return value < 0; });
        return _trie[node][word.back() - AlphabetStart] < 0;
    }
};

}

namespace DesignAddSearchWordsDataStructureTask
{

TEST(DesignAddSearchWordsDataStructureTaskTests, Examples)
{
    WordDictionary wordDictionary;
    ASSERT_NO_THROW(wordDictionary.addWord("bad"));
    ASSERT_NO_THROW(wordDictionary.addWord("dad"));
    ASSERT_NO_THROW(wordDictionary.addWord("mad"));
    ASSERT_FALSE(wordDictionary.search("pad"));
    ASSERT_TRUE(wordDictionary.search("bad"));
    ASSERT_TRUE(wordDictionary.search(".ad"));
    ASSERT_TRUE(wordDictionary.search("b.."));
}

TEST(DesignAddSearchWordsDataStructureTaskTests, FromWrongAnswers)
{
    WordDictionary wordDictionary;
    ASSERT_NO_THROW(wordDictionary.addWord("a"));
    ASSERT_NO_THROW(wordDictionary.addWord("ab"));
    ASSERT_TRUE(wordDictionary.search("a"));
    ASSERT_TRUE(wordDictionary.search("a."));
    ASSERT_TRUE(wordDictionary.search("ab"));
    ASSERT_FALSE(wordDictionary.search(".a"));
    ASSERT_TRUE(wordDictionary.search(".b"));
    ASSERT_FALSE(wordDictionary.search("ab."));
    ASSERT_TRUE(wordDictionary.search("."));
    ASSERT_TRUE(wordDictionary.search(".."));
}

}
