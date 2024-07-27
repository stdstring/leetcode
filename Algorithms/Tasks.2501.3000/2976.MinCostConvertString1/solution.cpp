#include <queue>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minimumCost(std::string const &source,
                                        std::string const &target,
                                        std::vector<char> const &original,
                                        std::vector<char> const &changed,
                                        std::vector<int> const &cost) const
    {
        std::vector<std::vector<Link>> graph(AlphabetSize);
        for (size_t index = 0; index < cost.size(); ++index)
        {
            const size_t fromLetter = original[index] - AlphabetStart;
            const size_t toLetter = changed[index] - AlphabetStart;
            graph[fromLetter].emplace_back(toLetter, cost[index]);
        }
        std::vector<std::vector<long long>> letterCosts;
        letterCosts.reserve(AlphabetSize);
        for (size_t letter = 0; letter < AlphabetSize; ++letter)
            letterCosts.emplace_back(calcCosts(graph, letter));
        long long totalCost = 0;
        for (size_t index = 0; index < source.size(); ++index)
        {
            const size_t sourceLetter = source[index] - AlphabetStart;
            const size_t targetLetter = target[index] - AlphabetStart;
            const long long transformCost = letterCosts[sourceLetter][targetLetter];
            if (transformCost == -1)
                return -1;
            totalCost += transformCost;
        }
        return totalCost;
    }

private:
    static constexpr size_t AlphabetStart = 'a';
    static constexpr size_t AlphabetSize = 26;

    struct Link
    {
        Link(size_t letter, int cost) : Letter(letter), Cost(cost)
        {
        }
        size_t Letter;
        int Cost;
    };

    struct Path
    {
        Path(size_t letter, long long cost) : Letter(letter), Cost(cost)
        {
        }
        size_t Letter;
        long long Cost;
    };

    [[nodiscard]] std::vector<long long> calcCosts(std::vector<std::vector<Link>> const &graph, size_t start) const
    {
        std::vector<long long> costs(AlphabetSize, -1);
        std::vector<bool> processed(AlphabetSize, false);
        costs[start] = 0;
        auto cmp = [](Path const &left, Path const &right) { return left.Cost > right.Cost; };
        std::priority_queue<Path, std::vector<Path>, decltype(cmp)> queue(cmp);
        queue.emplace(start, 0);
        while (!queue.empty())
        {
            const Path current(queue.top());
            queue.pop();
            if (processed[current.Letter])
                continue;
            processed[current.Letter] = true;
            for (Link const &link : graph[current.Letter])
            {
                if (processed[link.Letter])
                    continue;
                if ((costs[link.Letter] == -1) || ((current.Cost + link.Cost) < costs[link.Letter]))
                {
                    costs[link.Letter] = current.Cost + link.Cost;
                    queue.emplace(link.Letter, costs[link.Letter]);
                }
            }
        }
        return costs;
    }
};

}

namespace MinCostConvertString1Task
{

TEST(MinCostConvertString1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(28, solution.minimumCost("abcd", "acbe", {'a', 'b', 'c', 'c', 'e', 'd'}, {'b', 'c', 'b', 'e', 'b', 'e'}, {2, 5, 5, 1, 2, 20}));
    ASSERT_EQ(12, solution.minimumCost("aaaa", "bbbb", {'a', 'c'}, {'c', 'b'}, {1, 2}));
    ASSERT_EQ(-1, solution.minimumCost("abcd", "abce", {'a'}, {'e'}, {10000}));
}

}