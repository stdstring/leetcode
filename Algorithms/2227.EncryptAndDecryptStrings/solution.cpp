#include <algorithm>
#include <deque>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Encrypter
{
public:
    Encrypter(std::vector<char> const &keys, std::vector<std::string> const &values, std::vector<std::string> const &dictionary)
    {
        // encrypt map
        for (size_t index = 0; index < keys.size(); ++index)
        {
            _encryptMap.emplace(keys[index], values[index]);
            _decryptMap[values[index]].push_back(keys[index]);
        }
        for (std::string const &word : dictionary)
            generateTrieEntry(word);
    }

    std::string encrypt(std::string const &word1)
    {
        std::string result;
        result.reserve(2 * word1.size());
        for (char ch : word1)
        {
            auto iterator = _encryptMap.find(ch);
            result.append(iterator == _encryptMap.cend() ? "" : iterator->second);
        }
        return result;
    }

    int decrypt(std::string const &word2)
    {
        std::deque<int> nodes;
        nodes.push_back(0);
        for (size_t index = 0; index < word2.size(); index += 2)
        {
            std::string pair(word2.substr(index, 2));
            std::vector<char> const &chars(_decryptMap[pair]);
            const size_t portionSize = nodes.size();
            for (size_t portionIndex = 0; portionIndex < portionSize; ++portionIndex)
            {
                int node = nodes.front();
                nodes.pop_front();
                if (node == WordEnd)
                    continue;
                node = std::abs(node);
                for (const char ch : chars)
                {
                    const size_t charIndex = ch - AlphabetStart;
                    if (_trie[node][charIndex] != 0)
                        nodes.push_back(_trie[node][charIndex]);
                }
            }
        }
        return static_cast<int>(std::count_if(nodes.cbegin(), nodes.cend(), [](int node){ return node < 0; }));
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';
    static constexpr int WordEnd = INT_MIN;

    std::unordered_map<char, std::string> _encryptMap;
    std::unordered_map<std::string, std::vector<char>> _decryptMap;
    std::vector<std::vector<int>> _trie;

    void generateTrieEntry(std::string const &word)
    {
        size_t node = 0;
        // non last chars
        for (size_t index = 0; index < word.size() - 1; ++index)
        {
            if (node == _trie.size())
                _trie.emplace_back(AlphabetSize, 0);
            const size_t charIndex = word[index] - AlphabetStart;
            const int trieCellValue = _trie[node][charIndex];
            if ((trieCellValue == 0) || (trieCellValue == WordEnd))
            {
                _trie[node][charIndex] = (trieCellValue == 0 ? 1 : -1) * static_cast<int>(_trie.size());
                node = _trie.size();
            }
            else
                node = std::abs(trieCellValue);
        }
        // last char
        if (node == _trie.size())
            _trie.emplace_back(AlphabetSize, 0);
        const size_t charIndex = word.back() - AlphabetStart;
        const int trieCellValue = _trie[node][charIndex];
        if (trieCellValue == 0)
            _trie[node][charIndex] = WordEnd;
        if (trieCellValue > 0)
            _trie[node][charIndex] = -trieCellValue;
    }
};

}

namespace EncryptAndDecryptStringsTask
{

TEST(EncryptAndDecryptStringsTaskTests, Examples)
{
    Encrypter encrypter({'a', 'b', 'c', 'd'}, {"ei", "zf", "ei", "am"}, {"abcd", "acbd", "adbc", "badc", "dacb", "cadb", "cbda", "abad"});
    ASSERT_EQ("eizfeiam", encrypter.encrypt("abcd"));
    ASSERT_EQ(2, encrypter.decrypt("eizfeiam"));
}

TEST(EncryptAndDecryptStringsTaskTests, FromWrongAnswers)
{
    Encrypter encrypter({'a', 'b', 'c', 'z'}, {"aa", "bb", "cc", "zz"}, {"aa", "aaa", "aaaa", "aaaaa", "aaaaaaa"});
    ASSERT_EQ(1, encrypter.decrypt("aaaa"));
    ASSERT_EQ(0, encrypter.decrypt("aa"));
    ASSERT_EQ(1, encrypter.decrypt("aaaa"));
    ASSERT_EQ(1, encrypter.decrypt("aaaaaaaa"));
    ASSERT_EQ(1, encrypter.decrypt("aaaaaaaaaaaaaa"));
    ASSERT_EQ(0, encrypter.decrypt("aefagafvabfgshdthn"));
}

}
