#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class MapSum
{
public:
    MapSum() : _trie(1, std::vector<size_t>(AlphabetSize, 0))
    {
    }

    void insert(std::string const &key, int val)
    {
        size_t currentNode = 0;
        for (char ch : key)
        {
            if (_trie[currentNode][ch - AlphabetStart] == 0)
            {
                _trie[currentNode][ch - AlphabetStart] = _trie.size();
                _trie.emplace_back(AlphabetSize, 0);
            }
            currentNode = _trie[currentNode][ch - AlphabetStart];
        }
        _nodeValueMap[currentNode] = val;
    }

    int sum(std::string const &prefix)
    {
        size_t currentNode = 0;
        for (char ch : prefix)
        {
            currentNode = _trie[currentNode][ch - AlphabetStart];
            if (currentNode == 0)
                return 0;
        }
        int value = 0;
        std::queue<size_t> nodeQueue;
        nodeQueue.push(currentNode);
        while (!nodeQueue.empty())
        {
            if (_nodeValueMap.count(nodeQueue.front()) == 1)
                value += _nodeValueMap[nodeQueue.front()];
            for (size_t nextNode : _trie[nodeQueue.front()])
            {
                if (nextNode != 0)
                   nodeQueue.push(nextNode);
            }
            nodeQueue.pop();
        }
        return value;
    }

private:
    static constexpr size_t AlphabetSize = 26;
    static constexpr size_t AlphabetStart = 'a';

    std::vector<std::vector<size_t>> _trie;
    std::unordered_map<size_t, int> _nodeValueMap;
};

}

namespace MapSumPairsTask
{

TEST(MapSumPairsTaskTests, Examples)
{
    MapSum mapSum;
    ASSERT_NO_THROW(mapSum.insert("apple", 3));
    ASSERT_EQ(3, mapSum.sum("ap"));
    ASSERT_NO_THROW(mapSum.insert("app", 2));
    ASSERT_EQ(5, mapSum.sum("ap"));
}

}
