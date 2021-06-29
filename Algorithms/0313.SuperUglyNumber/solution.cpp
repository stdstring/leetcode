#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int nthSuperUglyNumber(int n, std::vector<int> const &primes) const
    {
        std::priority_queue<int, std::vector<int>, std::greater<>> sequence;
        sequence.push(1);
        for (size_t current = 1; current < static_cast<size_t>(n); ++current)
        {
            for (int prime : primes)
            {
                const long long product = static_cast<long long>(prime) * sequence.top();
                if (product > INT_MAX)
                    break;
                sequence.push(static_cast<int>(product));
            }
            const int prevNumber = sequence.top();
            while (sequence.top() == prevNumber)
                sequence.pop();
        }
        return sequence.top();
    }
};

}

namespace SuperUglyNumberTask
{

TEST(SuperUglyNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(32, solution.nthSuperUglyNumber(12, {2, 7, 13, 19}));
    ASSERT_EQ(1, solution.nthSuperUglyNumber(1, {2, 3, 5}));
}

TEST(SuperUglyNumberTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1092889481, solution.nthSuperUglyNumber(100000, {7, 19, 29, 37, 41, 47, 53, 59, 61, 79, 83, 89, 101, 103, 109, 127, 131, 137, 139, 157, 167, 179, 181, 199, 211, 229, 233, 239, 241, 251}));
}


}