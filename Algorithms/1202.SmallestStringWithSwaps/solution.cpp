#include <algorithm>
#include <iterator>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Subset
{
    Subset(int parent, int rank) : Parent(parent), Rank(rank)
    {
    }

    int Parent;
    int Rank;
};

class Solution
{
public:
    [[nodiscard]] std::string smallestStringWithSwaps(std::string const &s, std::vector<std::vector<int>> const &pairs) const
    {
        std::vector<Subset> subsets;
        subsets.reserve(s.size());
        for (int index = 0; index < static_cast<int>(s.size()); ++index)
            subsets.emplace_back(index, 1);
        std::unordered_map<int, std::vector<int>> chains;
        for (std::vector<int> const &pair : pairs)
        {
            const int root1 = findParent(subsets, pair[0]);
            const int root2 = findParent(subsets, pair[1]);
            if (root1 != root2)
                unionSubsets(subsets, root1, root2, chains);
        }
        std::string result(s);
        for (auto &entry : chains)
        {
            std::string chain(entry.second.size(), 'a');
            std::sort(entry.second.begin(), entry.second.end());
            for (size_t index = 0; index < entry.second.size(); ++index)
                chain[index] = result[entry.second[index]];
            std::sort(chain.begin(), chain.end());
            for (size_t index = 0; index < entry.second.size(); ++index)
                result[entry.second[index]] = chain[index];
        }
        return result;
    }

private:
    int findParent(std::vector<Subset> &subsets, int current) const
    {
        if (subsets[current].Parent != current)
            subsets[current].Parent = findParent(subsets, subsets[current].Parent);
        return subsets[current].Parent;
    }

    void unionSubsets(std::vector<Subset> &subsets, int root1, int root2, std::unordered_map<int, std::vector<int>> &chains) const
    {
        if (subsets[root1].Rank >= subsets[root2].Rank)
        {
            unionChains(chains, root1, subsets[root1].Rank, root2, subsets[root2].Rank);
            subsets[root2].Parent = root1;
            subsets[root1].Rank += subsets[root2].Rank;
        }
        else
        {
            unionChains(chains, root2, subsets[root2].Rank, root1, subsets[root1].Rank);
            subsets[root1].Parent = root2;
            subsets[root2].Rank += subsets[root1].Rank;
        }
    }

    void unionChains(std::unordered_map<int, std::vector<int>> &chains, int root1, int rank1, int root2, int rank2) const
    {
        if (rank1 == 1)
            chains.emplace(root1, std::vector<int>({root1}));
        if (rank2 == 1)
            chains[root1].push_back(root2);
        else
            std::copy(chains[root2].cbegin(), chains[root2].cend(), std::back_inserter(chains[root1]));
        if (rank2 > 1)
            chains.erase(root2);
    }
};

}

namespace SmallestStringWithSwapsTask
{

TEST(SmallestStringWithSwapsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("bacd", solution.smallestStringWithSwaps("dcab", {{0, 3}, {1, 2}}));
    ASSERT_EQ("abcd", solution.smallestStringWithSwaps("dcab", {{0, 3}, {1, 2}, {0, 2}}));
    ASSERT_EQ("abc", solution.smallestStringWithSwaps("cba", {{0, 1}, {1, 2}}));
}

}