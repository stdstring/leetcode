#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<std::string>> findLadders(std::string const &beginWord, std::string const &endWord, std::vector<std::string> const &wordList) const
    {
        std::vector<std::string> words(wordList);
        size_t beginWordPos = words.size();
        size_t endWordPos = words.size();
        for (size_t index = 0; index < words.size(); ++index)
        {
            if (words[index] == beginWord)
                beginWordPos = index;
            if (words[index] == endWord)
                endWordPos = index;
        }
        if (endWordPos == words.size())
            return {};
        if (beginWordPos == words.size())
            words.push_back(beginWord);
        const std::vector<std::vector<size_t>> graph(createGraph(words));
        std::vector<size_t> minPath(calcMinPath(graph, beginWordPos));
        if (minPath[endWordPos] == NoPathValue)
            return {};
        std::vector<std::vector<std::string>> dest;
        std::vector<std::string> sequence;
        createSequences(words, graph, minPath, dest, sequence, endWordPos);
        return dest;
    }

private:
    static constexpr size_t NoPathValue = INT_MAX;

    std::vector<std::vector<size_t>> createGraph(std::vector<std::string> const &wordList) const
    {
        std::vector<std::vector<size_t>> nodes(wordList.size());
        std::unordered_map<std::string, std::vector<size_t>> connectedWordsMap;
        for (size_t index = 0; index < wordList.size(); ++index)
        {
            std::string key(wordList[index]);
            for (size_t charIndex = 0; charIndex < key.size(); ++charIndex)
            {
                const char current = key[charIndex];
                key[charIndex] = '*';
                connectedWordsMap[key].push_back(index);
                key[charIndex] = current;
            }
        }
        for (const auto &entry : connectedWordsMap)
        {
            for (size_t fromIndex = 0; fromIndex < entry.second.size(); ++fromIndex)
            {
                for (size_t toIndex = fromIndex + 1; toIndex < entry.second.size(); ++toIndex)
                {
                    nodes[entry.second[fromIndex]].push_back(entry.second[toIndex]);
                    nodes[entry.second[toIndex]].push_back(entry.second[fromIndex]);
                }
            }
        }
        return nodes;
    }

    std::vector<size_t> calcMinPath(std::vector<std::vector<size_t>> const &nodes, size_t beginNodePos) const
    {
        // BFS
        std::queue<size_t> queue;
        std::vector<size_t> distances(nodes.size(), NoPathValue);
        queue.push(beginNodePos);
        distances[beginNodePos] = 0;
        while (!queue.empty())
        {
            for (size_t link : nodes[queue.front()])
            {
                if (distances[link] == NoPathValue)
                {
                    distances[link] = distances[queue.front()] + 1;
                    queue.push(link);
                }
            }
            queue.pop();
        }
        return distances;
    }

    void createSequences(std::vector<std::string> const &wordList,
                         std::vector<std::vector<size_t>> const &graph,
                         std::vector<size_t> const &minPath,
                         std::vector<std::vector<std::string>> &dest,
                         std::vector<std::string> &sequence,
                         size_t current) const
    {
        sequence.push_back(wordList[current]);
        const size_t currentPathValue = minPath[current];
        if (currentPathValue == 0)
        {
            std::vector<std::string> result(sequence);
            std::reverse(result.begin(), result.end());
            dest.push_back(result);
        }
        else
        {
            for (size_t neighbor : graph[current])
            {
                if (minPath[neighbor] + 1 == currentPathValue)
                    createSequences(wordList, graph, minPath, dest, sequence, neighbor);
            }
        }
        sequence.pop_back();
    }
};

}

namespace WordLadderIITask
{

TEST(WordLadderIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"hit", "hot", "dot", "dog", "cog"}, {"hit", "hot", "lot", "log", "cog"}}),
              solution.findLadders("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}));
    ASSERT_EQ(std::vector<std::vector<std::string>>({}), solution.findLadders("hit", "cog", {"hot", "dot", "dog", "lot", "log"}));
}

}