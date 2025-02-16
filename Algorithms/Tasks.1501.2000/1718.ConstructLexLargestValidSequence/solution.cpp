#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> constructDistancedSequence(int n) const
    {
        std::vector<int> result(2 * n - 1, 0);
        if (fillSequence(n, (1 << (n + 1)) - 1, 0, result))
            return result;
        throw std::logic_error("Unexpected control flow");
    }

private:
    bool fillSequence(int n, int mask, size_t index, std::vector<int> &result) const
    {
        if (index == result.size())
            return true;
        if (result[index] != 0)
            return fillSequence(n, mask, index + 1, result);
        for (int number = n; number > 0; --number)
        {
            const int numberMask = 1 << number;
            if ((mask & numberMask) == 0)
                continue;
            size_t delta = (number > 1) ? number : 0;
            if ((index + delta) >= result.size() || (result[index + delta] != 0))
                continue;
            result[index] = result[index + delta] = number;
            if (fillSequence(n, mask & ~numberMask, index + 1, result))
                return true;
            result[index] = result[index + delta] = 0;
        }
        return false;
    }
};

}

namespace ConstructLexLargestValidSequenceTask
{

TEST(ConstructLexLargestValidSequenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 1, 2, 3, 2}), solution.constructDistancedSequence(3));
    ASSERT_EQ(std::vector<int>({5, 3, 1, 4, 3, 5, 2, 4, 2}), solution.constructDistancedSequence(5));
}

}