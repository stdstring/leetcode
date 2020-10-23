#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Trie
{
public:
    /* Initialize your data structure here. */
    Trie()
    {
        _prefixTree.emplace_back(alphabetSize + 1, unknownValue);
    }

    /* Inserts a word into the trie. */
    void insert(std::string const &word)
    {
        size_t node = 0;
        for (char ch : word)
        {
            const size_t charIndex = ch - 'a' + 1;
            if (_prefixTree[node][charIndex] == unknownValue)
            {
                _prefixTree.emplace_back(alphabetSize + 1, unknownValue);
                _prefixTree[node][charIndex] = static_cast<int>(_prefixTree.size() - 1);
                node = _prefixTree.size() - 1;
            }
            else
                node = _prefixTree[node][charIndex];
        }
        _prefixTree[node][0] = 0;
    }

    /* Returns if the word is in the trie. */
    bool search(std::string const &word)
    {
        size_t node = 0;
        if (!searchPrefix(word, node))
            return false;
        return _prefixTree[node][0] == 0;
    }

    /* Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(std::string const &prefix)
    {
        size_t node = 0;
        return searchPrefix(prefix, node);
    }

private:
    constexpr static size_t alphabetSize = 26;
    constexpr static int unknownValue = -1;
    std::vector<std::vector<int>> _prefixTree;

    bool searchPrefix(std::string const &prefix, size_t &node)
    {
        node = 0;
        for (char ch : prefix)
        {
            const size_t charIndex = ch - 'a' + 1;
            if (_prefixTree[node][charIndex] == unknownValue)
                return false;
            node = _prefixTree[node][charIndex];
        }
        return true;
    }
};

}

namespace ImplementTrieTask
{

TEST(ImplementTrieTaskTests, Examples)
{
    Trie trie;
    trie.insert("apple");
    ASSERT_TRUE(trie.search("apple"));
    ASSERT_FALSE(trie.search("app"));
    ASSERT_TRUE(trie.startsWith("app"));
    trie.insert("app");
    ASSERT_TRUE(trie.search("app"));
}

}