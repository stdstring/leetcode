#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfSubarrays(std::vector<int> const &nums, int k) const
    {
        const size_t expectedOddCount = k;
        // [start, end)
        size_t start = 0;
        size_t firstOddPos = calcFirstOddPos(nums, 0);
        size_t oddCount = 0;
        size_t lastOddPos = firstOddPos;
        if (firstOddPos == nums.size())
            return 0;
        for (; (lastOddPos < nums.size()) && (oddCount < expectedOddCount); ++lastOddPos)
        {
            if ((nums[lastOddPos] % 2) == 1)
                ++oddCount;
        }
        --lastOddPos;
        size_t end = calcEndPos(nums, lastOddPos + 1);
        if (oddCount < expectedOddCount)
            return 0;
        if (end == nums.size())
            return static_cast<int>((firstOddPos - start + 1) * (end - lastOddPos));
        size_t count = (firstOddPos - start + 1) * (end - lastOddPos);
        while (end < nums.size())
        {
            --oddCount;
            start = firstOddPos + 1;
            firstOddPos = calcFirstOddPos(nums, start);
            if (firstOddPos == nums.size())
                break;
            lastOddPos = end;
            end = calcEndPos(nums, lastOddPos + 1);
            count += (firstOddPos - start + 1) * (end - lastOddPos);
        }
        if (oddCount == expectedOddCount)
            count += (firstOddPos - start + 1) * (end - lastOddPos);
        return static_cast<int>(count);
    }

private:
    [[nodiscard]] size_t calcFirstOddPos(std::vector<int> const &nums, size_t initPos) const
    {
        size_t firstOddPos = initPos;
        for (; (firstOddPos < nums.size()) && ((nums[firstOddPos] % 2) == 0); ++firstOddPos){}
        return firstOddPos;
    }

    [[nodiscard]] size_t calcEndPos(std::vector<int> const &nums, size_t initPos) const
    {
        size_t endPos = initPos;
        for (; (endPos < nums.size()) && ((nums[endPos] % 2) == 0); ++endPos) {}
        return endPos;
    }
};

}

namespace CountNumberOfNiceSubarraysTask
{

TEST(CountNumberOfNiceSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.numberOfSubarrays({1, 1, 2, 1, 1}, 3));
    ASSERT_EQ(0, solution.numberOfSubarrays({2, 4, 6}, 1));
    ASSERT_EQ(16, solution.numberOfSubarrays({2, 2, 2, 1, 2, 2, 1, 2, 2, 2}, 2));
}

}