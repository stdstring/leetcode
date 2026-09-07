#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int distinctSubseqII(std::string const &s) const
    {
        // Array count contains the number of combinations for now ending with each character.
        // When we traverse one character in the string, the total number of combinations that ending with it,
        // will be 1(empty) + count[0] + count[1] + count[2] +...+ count[25].
        // Because we can choose empty, and every kind of endings from last round.
        // We also keep a variable sum as we go, it is the sum of all count array from count[0] to count[25];
        // After the current round, we will rewrite the total into count[c-'a'], to replace the old count[c-'a'],
        // this is the key step to resolve the duplicate letter problem.
        // Finally, we return sum.
        constexpr int modValue = 1000000007;
        constexpr size_t alphabetStart = 'a';
        constexpr size_t alphabetSize = 26;
        std::vector<int> count(alphabetSize, 0);
        int result = 0;
        for (const char ch : s)
        {
            const size_t letter = ch - alphabetStart;
            const int totalSum = (1 + result) % modValue;
            int currentSum = totalSum - count[letter];
            if (currentSum < 0)
                currentSum += modValue;
            result = (result + currentSum) % modValue;
            count[letter] = totalSum;
        }
        return result;
    }
};

}

namespace DistinctSubsequences2Task
{

TEST(DistinctSubsequences2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.distinctSubseqII("abc"));
    ASSERT_EQ(6, solution.distinctSubseqII("aba"));
    ASSERT_EQ(3, solution.distinctSubseqII("aaa"));
}

}