#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Node
{
    Node(size_t index) : Index(index)
    {
    }

    size_t Index;
    std::vector<size_t> Neighbors;
};

class Solution
{
public:
    int ladderLength(std::string const &beginWord, std::string const &endWord, std::vector<std::string> const &wordList) const
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
            return 0;
        if (beginWordPos == words.size())
            words.push_back(beginWord);
        const std::vector<Node> graph(createGraph(words));
        return static_cast<int>(findMinPath(graph, beginWordPos, endWordPos));
    }

private:
    static constexpr size_t NoPathValue = INT_MAX;

    std::vector<Node> createGraph(std::vector<std::string> const &wordList) const
    {
        std::vector<Node> nodes;
        std::unordered_map<std::string, std::vector<size_t>> connectedWordsMap;
        for (size_t index = 0; index < wordList.size(); ++index)
        {
            nodes.emplace_back(index);
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
                    nodes[entry.second[fromIndex]].Neighbors.push_back(entry.second[toIndex]);
                    nodes[entry.second[toIndex]].Neighbors.push_back(entry.second[fromIndex]);
                }
            }
        }
        return nodes;
    }

    size_t findMinPath(std::vector<Node> const &nodes, size_t beginNodePos, size_t endNodePos) const
    {
        // Dijkstra's algorithm
        std::vector<int> processed(nodes.size(), 0);
        std::vector<size_t> minPath(nodes.size(), NoPathValue);
        minPath[beginNodePos] = 0;
        auto cmp = [&minPath](Node const* left, Node const* right){ return minPath[left->Index] > minPath[right->Index]; };
        std::priority_queue<Node const*, std::vector<Node const*>, decltype(cmp)> queue(cmp);
        queue.push(&nodes[beginNodePos]);
        while (!queue.empty())
        {
            Node const* current = queue.top();
            queue.pop();
            if (processed[current->Index])
                continue;
            for (size_t neighbor : current->Neighbors)
            {
                if (processed[neighbor])
                    continue;
                minPath[neighbor] = std::min(minPath[neighbor], minPath[current->Index] + 1);
                queue.push(&nodes[neighbor]);
            }
            processed[current->Index] = true;
        }
        const size_t minPathValue = minPath[endNodePos];
        return minPathValue == NoPathValue ? 0 : minPathValue + 1;
    }
};

}

namespace WordLadderTask
{

TEST(WordLadderTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.ladderLength("hit", "cog", {"hot", "dot", "dog", "lot", "log", "cog"}));
    ASSERT_EQ(0, solution.ladderLength("hit", "cog", {"hot", "dot", "dog", "lot", "log"}));
}

TEST(WordLadderTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(5, solution.ladderLength("hit", "cog", {"hot", "hit", "cog", "dot", "dog"}));
}

}