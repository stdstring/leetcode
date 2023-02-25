#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> threeEqualParts(std::vector<int> const &arr) const
    {
        // 1
        const size_t totalOnesCount = std::accumulate(arr.cbegin(), arr.cend(), 0);
        if (totalOnesCount == 0)
            return {0, static_cast<int>(arr.size() - 1)};
        if (totalOnesCount % 3 != 0)
            return {-1, -1};
        // 2
        const size_t partOnesCount = totalOnesCount / 3;
        size_t firstStartOnes = npos;
        size_t secondStartOnes = npos;
        size_t thirdStartOnes = npos;
        size_t index = 0;
        if (!processPart(arr, partOnesCount, index, firstStartOnes))
            return {-1, -1};
        const size_t firstFinishOnes = index - 1;
        if (!processPart(arr, partOnesCount, index, secondStartOnes, firstStartOnes))
            return {-1, -1};
        const size_t secondFinishOnes = index - 1;
        if (!processPart(arr, partOnesCount, index, thirdStartOnes, firstStartOnes))
            return {-1, -1};
        const size_t thirdFinishOnes = index - 1;
        const size_t zerosSuffixSize = arr.size() - thirdFinishOnes;
        if ((thirdStartOnes - secondFinishOnes < zerosSuffixSize) || (secondStartOnes - firstFinishOnes < zerosSuffixSize))
            return {-1, -1};
        return {static_cast<int>(secondStartOnes - (secondStartOnes - firstFinishOnes - zerosSuffixSize) - 1), static_cast<int>(thirdStartOnes - (thirdStartOnes - secondFinishOnes - zerosSuffixSize))};
    }

private:
    static constexpr size_t npos = -1;

    bool processPart(std::vector<int> const &arr, size_t partOnesCount, size_t &index, size_t &startOnes, size_t firstStartOnes = npos) const
    {
        size_t onesCount = 0;
        while (onesCount < partOnesCount)
        {
            if (arr[index] == 1)
            {
                if (startOnes == npos)
                    startOnes = index;
                ++onesCount;
            }
            if (firstStartOnes != npos && startOnes != npos && arr[firstStartOnes + (index - startOnes)] != arr[index])
                return false;
            ++index;
        }
        return true;
    }
};

}

namespace ThreeEqualPartsTask
{

TEST(ThreeEqualPartsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 3}), solution.threeEqualParts({1, 0, 1, 0, 1}));
    ASSERT_EQ(std::vector<int>({-1, -1}), solution.threeEqualParts({1, 1, 0, 1, 1}));
    ASSERT_EQ(std::vector<int>({0, 2}), solution.threeEqualParts({1, 1, 0, 0, 1}));
}

TEST(ThreeEqualPartsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({15, 32}), solution.threeEqualParts({1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0}));
}

}