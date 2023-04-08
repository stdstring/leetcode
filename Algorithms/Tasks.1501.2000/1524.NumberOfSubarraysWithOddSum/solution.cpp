#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfSubarrays(std::vector<int> const &arr) const
    {
        constexpr int modValue = 1000000007;
        std::vector<size_t> oddSumIndices;
        std::vector<size_t> evenSumIndices;
        std::vector<bool> isPrevOddValues(arr.size(), false);
        int prefixSum = 0;
        for (size_t index = 0; index < arr.size(); ++index)
        {
            isPrevOddValues[index] = (prefixSum % 2 == 1);
            prefixSum += arr[index];
            (prefixSum % 2 == 0 ? evenSumIndices : oddSumIndices).emplace_back(index);
        }
        int result = 0;
        for (size_t index = 0, oddSumIndex = 0, evenSumIndex = 0; index < arr.size(); ++index)
        {
            if (isPrevOddValues[index])
            {
                while ((evenSumIndex < evenSumIndices.size()) && (evenSumIndices[evenSumIndex] < index))
                    ++evenSumIndex;
                result = (result + static_cast<int>(evenSumIndices.size() - evenSumIndex)) % modValue;
            }
            else
            {
                while ((oddSumIndex < oddSumIndices.size()) && (oddSumIndices[oddSumIndex] < index))
                    ++oddSumIndex;
                result = (result + static_cast<int>(oddSumIndices.size() - oddSumIndex)) % modValue;
            }
        }
        return result;
    }
};

}

namespace NumberOfSubarraysWithOddSumTask
{

TEST(NumberOfSubarraysWithOddSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numOfSubarrays({1, 3, 5}));
    ASSERT_EQ(0, solution.numOfSubarrays({2, 4, 6}));
    ASSERT_EQ(16, solution.numOfSubarrays({1, 2, 3, 4, 5, 6, 7}));
}

}