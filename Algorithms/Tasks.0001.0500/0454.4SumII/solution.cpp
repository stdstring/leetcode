#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int fourSumCount(std::vector<int> const &nums1, std::vector<int> const &nums2, std::vector<int> const &nums3, std::vector<int> const &nums4) const
    {
        std::unordered_map<int, size_t> pairs12;
        for (const int num1 : nums1)
        {
            for (const int num2 : nums2)
                ++pairs12[num1 + num2];
        }
        std::unordered_map<int, size_t> pairs34;
        for (const int num3 : nums3)
        {
            for (const int num4 : nums4)
                ++pairs34[num3 + num4];
        }
        size_t tuplesCount = 0;
        for (auto [pair12, count12] : pairs12)
        {
            auto iterator = pairs34.find(-pair12);
            if (iterator != pairs34.end())
                tuplesCount += (count12 * iterator->second);
        }
        return static_cast<int>(tuplesCount);
    }
};

}

namespace FourSumIITask
{

TEST(FourSumIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.fourSumCount({1, 2}, {-2, -1}, {-1, 2}, {0, 2}));
    ASSERT_EQ(1, solution.fourSumCount({0}, {0}, {0}, {0}));
}

TEST(FourSumIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(6, solution.fourSumCount({-1, -1}, {-1, 1}, {-1, 1}, {1, -1}));
    ASSERT_EQ(17, solution.fourSumCount({0, 1, -1}, {-1, 1, 0}, {0, 0, 1}, {-1, 1, 1}));
    ASSERT_EQ(76, solution.fourSumCount({1, 1, -1, -1}, {-1, -1, 1, 1}, {1, -1, 0, -1}, {1, 1, -1, 1}));
}

}