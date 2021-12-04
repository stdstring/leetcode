#include <vector>

#include "gtest/gtest.h"

namespace
{

class StreamChecker
{
public:
    StreamChecker(std::vector<std::string> const &words)
    {
        generateReversedTrie(words);
    }

    bool query(char letter)
    {
        _text.push_back(letter);
        return checkText();
    }

private:
    void generateReversedTrie(std::vector<std::string> const &words)
    {
        _trie.emplace_back(AlphabetSize, 0);
        for (std::string const &word : words)
        {
            size_t node = 0;
            for (size_t index = word.size() - 1; index > 0; --index)
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
            const size_t lastCharIndex = word.front() - AlphabetStart;
            if (_trie[node][lastCharIndex] == 0)
                _trie[node][lastCharIndex] = WordEnd;
            else if (_trie[node][lastCharIndex] > 0)
                _trie[node][lastCharIndex] = -_trie[node][lastCharIndex];
        }
    }

    bool checkText()
    {
        size_t node = 0;
        for (size_t index = 0; index < _text.size(); ++index)
        {
            const size_t charIndex = _text[_text.size() - 1 - index] - AlphabetStart;
            if (_trie[node][charIndex] == 0)
                return false;
            if (_trie[node][charIndex] < 0)
                return true;
            node = _trie[node][charIndex];
        }
        return false;
    }

    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';
    static constexpr int WordEnd = INT_MIN;
    std::vector<std::vector<int>> _trie;
    std::string _text;
};

}

namespace
{

void checkStreamChecker(std::vector<std::string> const &words, std::vector<char> const &letters, std::vector<bool> const &queryResults)
{
    StreamChecker checker(words);
    for (size_t index = 0; index < letters.size(); ++index)
        ASSERT_EQ(queryResults[index], checker.query(letters[index]));
}

}

namespace StreamOfCharactersTask
{

TEST(StreamOfCharactersTaskTests, Examples)
{
    checkStreamChecker({"cd", "f", "kl"},
                       {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'},
                       {false, false, false, true, false, true, false, false, false, false, false, true});
}

TEST(StreamOfCharactersTaskTests, FromWrongAnswers)
{
    checkStreamChecker({"ab", "ba", "aaab", "abab", "baa"},
                       {'a' ,'a', 'a', 'a', 'a', 'b', 'a', 'b', 'a', 'b', 'b', 'b', 'a', 'b', 'a', 'b', 'b', 'b', 'b', 'a', 'b', 'a', 'b', 'a', 'a', 'a', 'b', 'a', 'a', 'a'},
                       {false, false, false, false, false, true, true, true, true, true, false, false, true, true, true, true, false, false, false, true, true, true, true, true, true, false, true, true, true, false});
}


}