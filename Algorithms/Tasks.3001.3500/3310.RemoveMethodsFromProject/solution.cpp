#include <queue>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> remainingMethods(int n, int k, std::vector<std::vector<int>> const &invocations) const
    {
        std::vector<std::vector<int>> methods(n);
        for (std::vector<int> const &invocation : invocations)
        {
            const int from = invocation[0];
            const int to = invocation[1];
            methods[from].emplace_back(to);
        }
        const std::unordered_set<int> suspiciousMethods(findSuspiciousMethods(methods, k));
        const bool isolated = isIsolated(n, methods, suspiciousMethods);
        std::vector<int> result;
        result.reserve(n);
        for (int current = 0; current < n; ++current)
        {
            if (isolated && suspiciousMethods.contains(current))
                continue;
            result.emplace_back(current);
        }
        return result;
    }

private:
    [[nodiscard]] std::unordered_set<int> findSuspiciousMethods(std::vector<std::vector<int>> const &methods, int start) const
    {
        std::unordered_set<int> suspiciousMethods;
        suspiciousMethods.emplace(start);
        std::queue<int> suspiciousQueue;
        suspiciousQueue.push(start);
        while (!suspiciousQueue.empty())
        {
            const int current = suspiciousQueue.front();
            suspiciousQueue.pop();
            for (int child : methods[current])
            {
                if (!suspiciousMethods.contains(child))
                {
                    suspiciousMethods.emplace(child);
                    suspiciousQueue.push(child);
                }
            }
        }
        return suspiciousMethods;
    }

    [[nodiscard]] bool isIsolated(const int n, std::vector<std::vector<int>> const &methods, std::unordered_set<int> const &suspiciousMethods) const
    {
        for (int current = 0; current < n; ++current)
        {
            if (suspiciousMethods.contains(current))
                continue;
            for (int child : methods[current])
            {
                if (suspiciousMethods.contains(child))
                    return false;
            }
        }
        return true;
    }
};

}

namespace RemoveMethodsFromProjectTask
{

TEST(RemoveMethodsFromProjectTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3}), solution.remainingMethods(4, 1, {{1, 2}, {0, 1}, {3, 2}}));
    ASSERT_EQ(std::vector<int>({3, 4}), solution.remainingMethods(5, 0, {{1, 2}, {0, 2}, {0, 1}, {3, 4}}));
    ASSERT_EQ(std::vector<int>(), solution.remainingMethods(3, 2, {{1, 2}, {0, 1}, {2, 0}}));
}

TEST(RemoveMethodsFromProjectTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 2}), solution.remainingMethods(3, 1, {{0, 1}, {2, 1}}));
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3}), solution.remainingMethods(4, 1, {{0, 1}, {2, 1}}));
}

}
