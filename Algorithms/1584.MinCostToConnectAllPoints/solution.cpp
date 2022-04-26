#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Segment
{
    Segment(int start, int end, int length) : Start(start), End(end), Length(length)
    {
    }

    int Start;
    int End;
    int Length;
};

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
    [[nodiscard]] int minCostConnectPoints(std::vector<std::vector<int>> const &points) const
    {
        auto comparer = [](Segment const &l, Segment const &r){ return l.Length > r.Length; };
        std::priority_queue<Segment, std::vector<Segment>, decltype(comparer)> queue(comparer);
        for (size_t startPoint = 0; startPoint < points.size() - 1; ++startPoint)
        {
            for (size_t endPoint = startPoint + 1; endPoint < points.size(); ++endPoint)
            {
                int length = std::abs(points[endPoint][0] - points[startPoint][0]) + std::abs(points[endPoint][1] - points[startPoint][1]);
                queue.emplace(startPoint, endPoint, length);
            }
        }
        std::vector<Subset> subsets;
        subsets.reserve(points.size());
        for (int point = 0; point < static_cast<int>(points.size()); ++point)
            subsets.emplace_back(point, 1);
        int minCost = 0;
        size_t edgesCount = 0;
        while (edgesCount < points.size() - 1)
        {
            const int rootStart = findParent(subsets, queue.top().Start);
            const int rootEnd = findParent(subsets, queue.top().End);
            if (rootStart != rootEnd)
            {
                unionSubsets(subsets, rootStart, rootEnd);
                minCost += queue.top().Length;
                ++edgesCount;
            }
            queue.pop();
        }
        return minCost;
    }

private:
    int findParent(std::vector<Subset> &subsets, int point) const
    {
        if (subsets[point].Parent != point)
            subsets[point].Parent = findParent(subsets, subsets[point].Parent);
        return subsets[point].Parent;
    }

    void unionSubsets(std::vector<Subset> &subsets, int point1, int point2) const
    {
        const int root1 = findParent(subsets, point1);
        const int root2 = findParent(subsets, point2);
        if (subsets[root1].Rank > subsets[root2].Rank)
        {
            subsets[root2].Parent = root1;
            subsets[root1].Rank += subsets[root2].Rank;
        }
        else
        {
            subsets[root1].Parent = root2;
            subsets[root2].Rank += subsets[root1].Rank;
        }
    }
};

}

namespace MinCostToConnectAllPointsTask
{

TEST(MinCostToConnectAllPointsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(20, solution.minCostConnectPoints({{0, 0}, {2, 2}, {3, 10}, {5, 2}, {7, 0}}));
    ASSERT_EQ(18, solution.minCostConnectPoints({{3, 12}, {-2, 5}, {-4, 1}}));
}

}