#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSubarraysWithSum(std::vector<int> const &nums, int goal) const
    {
        if (goal == 0)
            return numSubarraysFor0(nums);
        std::vector<size_t> prefixData;
        prefixData.emplace_back(1);
        for (const int number : nums)
        {
            if (number == 0)
                ++prefixData.back();
            else
                prefixData.emplace_back(1);
        }
        int result = 0;
        for (size_t start = 0, end = goal; end < prefixData.size(); ++start, ++end)
            result += static_cast<int>(prefixData[start] * prefixData[end]);
        return result;
    }

private:
    [[nodiscard]] int numSubarraysFor0(std::vector<int> const& nums) const
    {
        int result = 0;
        int zeroSegmentSize = 0;
        for (const int number : nums)
        {
            if (number == 0)
                ++zeroSegmentSize;
            else
            {
                result += calcArithProgressionSum(zeroSegmentSize);
                zeroSegmentSize = 0;
            }
        }
        return result + calcArithProgressionSum(zeroSegmentSize);
    }

    [[nodiscard]] int calcArithProgressionSum(int n) const
    {
        return (1 + n) * n / 2;
    }
};

}

namespace BinarySubarraysWithSumTask
{

TEST(BinarySubarraysWithSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.numSubarraysWithSum({1, 0, 1, 0, 1}, 2));
    ASSERT_EQ(15, solution.numSubarraysWithSum({0, 0, 0, 0, 0}, 0));
}

TEST(BinarySubarraysWithSumTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numSubarraysWithSum({1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0}, 7));
    ASSERT_EQ(10, solution.numSubarraysWithSum({1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 1));
}

}