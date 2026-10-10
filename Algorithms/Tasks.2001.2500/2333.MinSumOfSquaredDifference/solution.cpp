#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    long long minSumSquareDiff(std::vector<int> const &nums1, std::vector<int> const &nums2, int k1, int k2) const
    {
        long long k = static_cast<long long>(k1) + k2;
        std::vector<int> differences(nums1.size() + 1, 0);
        long long totalDifferencesSum = 0;
        for (size_t index = 0; index < nums1.size(); ++index)
        {
            int difference = std::abs(nums1[index] - nums2[index]);
            differences[index] = difference;
            totalDifferencesSum += difference;
        }
        if (totalDifferencesSum <= k)
            return 0;
        std::ranges::sort(differences, std::greater<int>());
        size_t start = 1;
        for (; start < differences.size(); ++start)
        {
            const long long cost = static_cast<long long>((differences[start - 1] - differences[start]) * start);
            if (cost > k)
                break;
            k -= cost;
        }
        const long long q = static_cast<long long>(k / start);
        const long long r = static_cast<long long>(k % start);
        const long long finalDiff = differences[start - 1] - q;
        long long answer = static_cast<long long>((finalDiff - 1) * (finalDiff - 1) * r + finalDiff * finalDiff * (start - r));
        for (size_t index = start; index < differences.size(); ++index)
            answer += static_cast<long long>(differences[index]) * differences[index];
        return answer;
    }
};

}

namespace MinSumOfSquaredDifferenceTask
{

TEST(MinSumOfSquaredDifferenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(579, solution.minSumSquareDiff({1, 2, 3, 4}, {2, 10, 20, 19}, 0, 0));
    ASSERT_EQ(43, solution.minSumSquareDiff({ 1, 4, 10, 12 }, {5, 8, 6, 9}, 1, 1));
}

TEST(MinSumOfSquaredDifferenceTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minSumSquareDiff({0, 12, 17, 16, 8, 0, 3, 15, 12, 9}, {7, 5, 10, 9, 15, 7, 10, 8, 19, 2}, 32, 65));
}

}