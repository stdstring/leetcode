#include <algorithm>
#include <ranges>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestUniqueSubarray(std::vector<int> const &nums) const
    {
        // polynomial rolling hash
        std::vector<long long> h(nums.size() + 1, 0);
        std::vector<long long> p(nums.size() + 1, 0);
        p[0] = 1;
        for (size_t i = 0; i < nums.size(); ++i)
        {
            h[i + 1] = (h[i] * base + nums[i]) % mod;
            p[i + 1] = p[i] * base % mod;
        }
        size_t left = 1;
        size_t right = nums.size();
        while (left < right)
        {
            const size_t middle = (left + right) / 2;
            if (checkSubarrays(nums, middle, h, p))
                right = middle;
            else
                left = middle + 1;
        }
        return static_cast<int>(left);
    }

private:
    static constexpr long long mod = 1000000007LL;
    static constexpr long long base = 911382323LL;

    [[nodiscard]] bool checkSubarrays(std::vector<int> const &nums, size_t length, std::vector<long long> const &h, std::vector<long long> const &p) const
    {
        std::unordered_map<long long, size_t> knownHashes;
        for (size_t left = 0; left + length <= nums.size(); ++left)
        {
            const size_t right = left + length;
            const long long hash = (h[right] - h[left] * p[length] % mod + mod) % mod;
            ++knownHashes[hash];
        }
        return std::ranges::any_of(knownHashes | std::views::values, [](size_t count) { return count == 1; });
    }
};

}

namespace SmallestUniqueSubarrayTask
{

TEST(SmallestUniqueSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.smallestUniqueSubarray({3, 3, 3}));
    ASSERT_EQ(1, solution.smallestUniqueSubarray({2, 1, 2, 3, 3}));
    ASSERT_EQ(2, solution.smallestUniqueSubarray({1, 1, 2, 2, 1}));
}

}
