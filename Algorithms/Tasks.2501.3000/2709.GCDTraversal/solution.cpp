#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canTraverseAllPairs(std::vector<int> const &nums) const
    {
        std::unordered_map<int, std::vector<size_t>> numbersClasses(divideNumbersOnClasses(nums));
        std::vector<std::unordered_set<size_t>> graph(nums.size());
        for (auto const &[_, indices] : numbersClasses)
        {
            for (size_t index = 0; index < indices.size() - 1; ++index)
            {
                graph[indices[index]].emplace(indices[index + 1]);
                graph[indices[index + 1]].emplace(indices[index]);
            }
        }
        std::vector<bool> visited(nums.size(), false);
        std::queue<size_t> bfsQueue;
        bfsQueue.emplace(0);
        visited[0] = true;
        while (!bfsQueue.empty())
        {
            const size_t current = bfsQueue.front();
            bfsQueue.pop();
            for (const size_t neighbor : graph[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    bfsQueue.emplace(neighbor);
                }
            }
        }
        return std::ranges::all_of(visited, [](bool value) { return value; });
    }

private:
    [[nodiscard]] int extractPrimeFactor(int number, int factor) const
    {
        while ((number % factor) == 0)
            number /= factor;
        return number;
    }

    [[nodiscard]] std::unordered_map<int, std::vector<size_t>> divideNumbersOnClasses(std::vector<int> const &nums) const
    {
        std::unordered_map<int, std::vector<size_t>> numbersClasses;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            int number = nums[index];
            if ((number % 2) == 0)
            {
                numbersClasses[2].emplace_back(index);
                number = extractPrimeFactor(number, 2);
            }
            for (int factor = 3; factor * factor <= number; ++factor)
            {
                if ((number % factor) == 0)
                {
                    numbersClasses[factor].emplace_back(index);
                    number = extractPrimeFactor(number, factor);
                }
            }
            if (number > 1)
                numbersClasses[number].emplace_back(index);
        }
        return numbersClasses;
    }
};

}

namespace GCDTraversalTask
{

TEST(GCDTraversalTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canTraverseAllPairs({2, 3, 6}));
    ASSERT_EQ(false, solution.canTraverseAllPairs({3, 9, 5}));
    ASSERT_EQ(true, solution.canTraverseAllPairs({4, 3, 12, 8}));
}

TEST(GCDTraversalTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canTraverseAllPairs({1}));
    ASSERT_EQ(false, solution.canTraverseAllPairs({1, 2}));
}

}