#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> circularPermutation(int n, int start) const
    {
        // we use Gray codes here
        // Let's look at the bits of number n and the bits of number G(n) (Gray code on position n).
        // Notice that i-th bit of G(n) equals 1 only when i-th bit of n equals 1 and (i + 1)-th bit equals 0
        // or the other way around (i-th bit equals 0 and (i + 1)-th bit equals 1). Thus, G(n) = n ^ (n >> 1):
        const int grayCodesCount = 1 << n;
        std::vector<int> grayCodes(grayCodesCount, 0);
        for (int n = 0; n < grayCodesCount; ++n)
            grayCodes[n] = n ^ (n >> 1);
        std::vector<int> result;
        result.reserve(grayCodesCount);
        auto iterator = grayCodes.cbegin();
        while (*iterator != start)
            ++iterator;
        std::copy(iterator, grayCodes.cend(), std::back_inserter(result));
        std::copy(grayCodes.cbegin(), iterator, std::back_inserter(result));
        return result;
    }
};

}

namespace CircularPermutationInBinaryReprTask
{

TEST(CircularPermutationInBinaryReprTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 2, 0, 1}), solution.circularPermutation(2, 3));
    ASSERT_EQ(std::vector<int>({2, 6, 7, 5, 4, 0, 1, 3}), solution.circularPermutation(3, 2));
}

}