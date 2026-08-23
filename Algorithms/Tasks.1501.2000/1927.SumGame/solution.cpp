#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool sumGame(std::string const &num) const
    {
        // Bob can always make the total sum of both sides equal in mod 9.
        // If the number of ?'s is odd, then Alice wins.
        // When it's even, assume sum(left half) >= sum(right half).
        // Let's call these sums S1 and S2.
        // Let's call q1 and q2 the number of ? 's in the corresponding halves.
        // If q1 > q2, Alice always wins.
        // If q1 = q2, the proof is pretty similar with a small border case.
        // If S1 = S2, then Bob keeps on cancelling Alice's move and wins.
        // Else (S1 > S2), Alice puts only 9's in the left half and 0's in the right half.
        // If q1 < q2
        // If 2 * (S1-S2) == 9 (q2 - q1), then Bob has a winning strategy irrespective of what Alice does.
        // Else, then Alice has a winning strategy irrespective of what Bob does.
        const size_t halfSize = num.size() / 2;
        int leftSum = 0;
        int leftQMarks = 0;
        int rightSum = 0;
        int rightQMarks = 0;
        for (size_t index = 0; index < halfSize; ++index)
        {
            if (num[index] == '?')
                ++leftQMarks;
            else
                leftSum += (num[index] - '0');
            if (num[index + halfSize] == '?')
                ++rightQMarks;
            else
                rightSum += (num[index + halfSize] - '0');
        }
        if (leftSum >= rightSum)
            return sumGame(leftSum, leftQMarks, rightSum, rightQMarks);
        // NOLINTNEXTLINE(readability-suspicious-call-argument)
        return sumGame(rightSum, rightQMarks, leftSum, leftQMarks);
    }

private:
    [[nodiscard]] bool sumGame(int leftSum, int leftQMarks, int rightSum, int rightQMarks) const
    {
        if (((leftQMarks + rightQMarks) % 2) != 0)
            return true;
        if (leftQMarks > rightQMarks)
            return true;
        if (leftQMarks == rightQMarks)
            return leftSum != rightSum;
        return 2 * (leftSum - rightSum) != 9 * (rightQMarks - leftQMarks);
    }
};

}

namespace SumGameTask
{

TEST(SumGameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.sumGame("5023"));
    ASSERT_EQ(true, solution.sumGame("25??"));
    ASSERT_EQ(false, solution.sumGame("?3295???"));
}

}