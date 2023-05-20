#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getSubarrayBeauty(std::vector<int> const &nums, int k, int x) const
    {
        const size_t subarraySize = k;
        const size_t leftPartSize = x;
        std::multiset<int> leftPart;
        std::multiset<int> rightPart;
        // init
        for (size_t index  = 0; index < subarraySize; ++index)
        {
            leftPart.emplace(nums[index]);
            balanceParts(leftPart, rightPart, leftPartSize);
        }
        std::vector<int> result;
        result.emplace_back(*leftPart.crbegin() >= 0 ? 0 : *leftPart.crbegin());
        // use sliding window
        for (size_t index = 1; index <= nums.size() - subarraySize; ++index)
        {
            int removedValue = nums[index - 1];
            int addedValue = nums[index + subarraySize - 1];
            const auto removedValueIterator = (removedValue <= *leftPart.crbegin() ? leftPart : rightPart).find(removedValue);
            (removedValue <= *leftPart.crbegin() ? leftPart : rightPart).erase(removedValueIterator);
            (!leftPart.empty() && (addedValue <= *leftPart.crbegin()) ? leftPart : rightPart).emplace(addedValue);
            balanceParts(leftPart, rightPart, leftPartSize);
            result.emplace_back(*leftPart.crbegin() >= 0 ? 0 : *leftPart.crbegin());
        }
        return result;
    }

private:
    void balanceParts(std::multiset<int> &leftPart, std::multiset<int> &rightPart, size_t leftPartSize) const
    {
        if (leftPart.size() > leftPartSize)
        {
            int lastValue = *leftPart.crbegin();
            leftPart.erase(std::prev(leftPart.cend(), 1));
            rightPart.emplace(lastValue);
        }
        if (!rightPart.empty() && (leftPart.size() < leftPartSize))
        {
            int firstValue = *rightPart.cbegin();
            rightPart.erase(rightPart.cbegin());
            leftPart.emplace(firstValue);
        }
    }
};

}

namespace SlidingSubarrayBeautyTask
{

TEST(SlidingSubarrayBeautyTaskTests, Examples2)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({-1, -2, -2}), solution.getSubarrayBeauty({1, -1, -3, -2, 3}, 3, 2));
    ASSERT_EQ(std::vector<int>({-1, -2, -3, -4}), solution.getSubarrayBeauty({-1, -2, -3, -4, -5}, 2, 2));
    ASSERT_EQ(std::vector<int>({-3, 0, -3, -3, -3}), solution.getSubarrayBeauty({-3, 1, 2, -3, 0, -3}, 2, 1));
}

}