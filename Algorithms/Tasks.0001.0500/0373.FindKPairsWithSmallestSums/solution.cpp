#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct PairData
{
    PairData(int first, int second, int sum) : First(first), Second(second), Sum(sum)
    {
    }

    int First;
    int Second;
    int Sum;
};

class Solution
{
public:
    std::vector<std::vector<int>> kSmallestPairs(std::vector<int> const &nums1, std::vector<int> const &nums2, int k) const
    {
        const size_t pairsCount = k;
        auto comparer = [](PairData const &left, PairData const &right){ return left.Sum < right.Sum; };
        std::priority_queue<PairData, std::vector<PairData>, decltype(comparer)> pairsQueue(comparer);
        for (int number1 : nums1)
        {
            const int startSum = number1 + nums2[0];
            if (pairsQueue.size() == pairsCount && startSum > pairsQueue.top().Sum)
                break;
            for (int number2 : nums2)
            {
                const int sum = number1 + number2;
                if (pairsQueue.size() == pairsCount && sum > pairsQueue.top().Sum)
                    break;
                pairsQueue.emplace(number1, number2, number1 + number2);
                if (pairsQueue.size() > pairsCount)
                    pairsQueue.pop();
            }
        }
        std::vector<std::vector<int>> result;
        while (!pairsQueue.empty())
        {
            result.push_back({pairsQueue.top().First, pairsQueue.top().Second});
            pairsQueue.pop();
        }
        return result;
    }
};

}

namespace FindKPairsWithSmallestSumsTask
{

TEST(FindKPairsWithSmallestSumsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 6}, {1, 4}, {1, 2}}), solution.kSmallestPairs({1, 7, 11}, {2, 4, 6}, 3));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1}, {1, 1}}), solution.kSmallestPairs({1, 1, 2}, {1, 2, 3}, 2));
    ASSERT_EQ(std::vector<std::vector<int>>({{2, 3}, {1, 3}}), solution.kSmallestPairs({1, 2}, {3}, 3));
}

}