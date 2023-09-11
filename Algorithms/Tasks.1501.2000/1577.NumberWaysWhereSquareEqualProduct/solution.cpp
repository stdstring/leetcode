#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numTriplets(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        const std::unordered_map<uint64_t, size_t> nums1Pairs(calcPairs(nums1));
        const std::unordered_map<uint64_t, size_t> nums2Pairs(calcPairs(nums2));
        return static_cast<int>(calcTriplets(nums1, nums2Pairs) + calcTriplets(nums2, nums1Pairs));
    }

private:
    [[nodiscard]] std::unordered_map<uint64_t, size_t> calcPairs(std::vector<int> const &numbers) const
    {
        std::unordered_map<uint64_t, size_t> pairMap;
        for (size_t index1 = 0; index1 < numbers.size(); ++index1)
        {
            for (size_t index2 = index1 + 1; index2 < numbers.size(); ++index2)
                ++pairMap[1ULL * numbers[index1] * numbers[index2]];
        }
        return pairMap;
    }

    [[nodiscard]] size_t calcTriplets(std::vector<int> const &numbers, std::unordered_map<uint64_t, size_t> const &pairMap) const
    {
        size_t tripletCount = 0;
        for (const int number : numbers)
        {
            auto iterator = pairMap.find(1ULL * number * number);
            if (iterator != pairMap.cend())
                tripletCount += iterator->second;
        }
        return tripletCount;
    }
};

}

namespace NumberWaysWhereSquareEqualProductTask
{

TEST(NumberWaysWhereSquareEqualProductTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numTriplets({7, 4}, {5, 2, 8, 9}));
    ASSERT_EQ(9, solution.numTriplets({1, 1}, {1, 1, 1}));
    ASSERT_EQ(2, solution.numTriplets({7, 7, 8, 3}, {1, 2, 9, 7}));
}

TEST(NumberWaysWhereSquareEqualProductTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.numTriplets({43024, 99908}, {1864}));
}

}