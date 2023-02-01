#include <queue>
#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int distinctIntegers(int n) const
    {
        std::unordered_set<int> knownNumbers;
        knownNumbers.insert(n);
        std::queue<int> queue;
        queue.push(n);
        while (!queue.empty())
        {
            const int current = queue.front();
            queue.pop();
            for (int number = 2; number < current; ++number)
            {
                if ((current % number == 1) && (knownNumbers.count(number) == 0))
                {
                    knownNumbers.insert(number);
                    queue.push(number);
                }
            }
        }
        return static_cast<int>(knownNumbers.size());
    }
};

}

namespace CountDistinctNumbersOnBoardTask
{

TEST(CountDistinctNumbersOnBoardTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.distinctIntegers(5));
    ASSERT_EQ(2, solution.distinctIntegers(3));
}

TEST(CountDistinctNumbersOnBoardTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.distinctIntegers(1));
}

}