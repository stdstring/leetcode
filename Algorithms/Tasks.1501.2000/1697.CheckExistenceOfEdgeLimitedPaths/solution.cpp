#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<bool> distanceLimitedPathsExist(int n, std::vector<std::vector<int>> const &edgeList, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<std::vector<int>> edges(edgeList);
        std::sort(edges.begin(), edges.end(), [](std::vector<int> const &l, std::vector<int> const &r) { return l[2] < r[2]; });
        std::vector<size_t> indices(queries.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&queries](size_t l, size_t r) { return queries[l][2] < queries[r][2]; });
        std::vector<bool> answers(queries.size(), true);
        std::vector<NodeData> data;
        data.reserve(n);
        for (int node = 0; node < n; ++node)
            data.emplace_back(node);
        for (size_t queryIndex = 0, edgeIndex = 0; (queryIndex < indices.size()) && (edgeIndex < edges.size());)
        {
            if (edges[edgeIndex][2] < queries[indices[queryIndex]][2])
            {
                const size_t root1 = getRoot(data, edges[edgeIndex][0]);
                const size_t root2 = getRoot(data, edges[edgeIndex][1]);
                if (root1 != root2)
                    merge(data, root1, root2);
                ++edgeIndex;
            }
            else
            {
                const size_t root1 = getRoot(data, queries[indices[queryIndex]][0]);
                const size_t root2 = getRoot(data, queries[indices[queryIndex]][1]);
                answers[indices[queryIndex]] = root1 == root2;
                ++queryIndex;
            }
        }
        return answers;
    }

private:
    struct NodeData
    {
        NodeData(size_t node) : Parent(node), Size(1)
        {
        }
        size_t Parent;
        size_t Size;
    };

    [[nodiscard]] size_t getRoot(std::vector<NodeData> const &data, size_t current) const
    {
        while (data[current].Parent != current)
            current = data[current].Parent;
        return current;
    }

    void merge(std::vector<NodeData> &data, size_t root1, size_t root2) const
    {
        if (data[root1].Size >= data[root2].Size)
        {
            data[root2].Parent = static_cast<int>(root1);
            data[root1].Size += data[root2].Size;
        }
        else
        {
            data[root1].Parent = static_cast<int>(root2);
            data[root2].Size += data[root1].Size;
        }
    }
};

}

namespace CheckExistenceOfEdgeLimitedPathsTask
{

TEST(CheckExistenceOfEdgeLimitedPathsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<bool>({false, true}),
              solution.distanceLimitedPathsExist(3, {{0, 1, 2}, {1, 2, 4}, {2, 0, 8}, {1, 0, 16}}, {{0, 1, 2}, {0, 2, 5}}));
    ASSERT_EQ(std::vector<bool>({true, false}),
              solution.distanceLimitedPathsExist(5, {{0, 1, 10}, {1, 2, 5}, {2, 3, 9}, {3, 4, 13}}, {{0, 4, 14}, {1, 4, 13}}));
}

}