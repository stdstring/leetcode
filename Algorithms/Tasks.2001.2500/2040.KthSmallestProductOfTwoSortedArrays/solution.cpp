#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long kthSmallestProduct(std::vector<int> const &nums1, std::vector<int> const &nums2, long long k) const
    {
        long long left = std::min({1LL * nums1.front() * nums2.front(),
                                   1LL * nums1.front() * nums2.back(),
                                   1LL * nums1.back() * nums2.front(),
                                   1LL * nums1.back() * nums2.back()});
        long long right = std::max({1LL * nums1.front() * nums2.front(),
                                    1LL * nums1.front() * nums2.back(),
                                    1LL * nums1.back() * nums2.front(),
                                    1LL * nums1.back() * nums2.back()});
        while (left < right)
        {
            const long long middle = left + (right - left) / 2;
            if (countProducts(nums1, nums2, middle) < k)
                left = middle + 1;
            else
                right = middle;
        }
        return left;
    }

private:
    [[nodiscard]] long long countProducts(std::vector<int> const &nums1, std::vector<int> const &nums2, long long target) const
    {
        size_t count = 0;
        for (const int num1 : nums1)
        {
            if (num1 == 0)
            {
                if (target >= 0)
                    count += nums2.size();
                continue;
            }
            size_t left = 0;
            size_t right = nums2.size();
            while (left < right)
            {
                size_t middle = (left + right) / 2;
                long long prod = 1LL * num1 * nums2[middle];
                if (prod <= target)
                {
                    if (num1 > 0)
                        left = middle + 1;
                    else
                        right = middle;
                }
                else {
                    if (num1 > 0)
                        right = middle;
                    else
                        left = middle + 1;
                }
            }
            count += (num1 > 0) ? left : (nums2.size() - left);
        }
        return static_cast<long long>(count);
    }
};

}

namespace KthSmallestProductOfTwoSortedArraysTask
{

TEST(KthSmallestProductOfTwoSortedArraysTaskTests, Examples3)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.kthSmallestProduct({2, 5}, {3, 4}, 2));
    ASSERT_EQ(0, solution.kthSmallestProduct({-4, -2, 0, 3}, {2, 4}, 6));
    ASSERT_EQ(-6, solution.kthSmallestProduct({-2, -1, 0, 1, 2}, {-3, -1, 2, 4, 5}, 3));
}

TEST(KthSmallestProductOfTwoSortedArraysTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(-10000000000, solution.kthSmallestProduct({-100000, 100000}, {-100000, 100000}, 1));
}

}