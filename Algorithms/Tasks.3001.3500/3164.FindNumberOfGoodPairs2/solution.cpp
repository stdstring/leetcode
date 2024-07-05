#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long numberOfPairs(std::vector<int> const &nums1, std::vector<int> const &nums2, int k) const
    {
        auto [minIterator, maxIterator] = std::ranges::minmax_element(nums2);
        const int minNumber = *minIterator;
        const int maxNumber = *maxIterator;
        std::vector<long long> numbers2(maxNumber - minNumber + 1, 0);
        for (const int number : nums2)
            ++numbers2[number - minNumber];
        long long result = 0;
        for (int number : nums1)
        {
            if ((number % k) != 0)
                continue;
            number /= k;
            for (int factor = 1; (factor * factor <= number) && (factor <= maxNumber) ; ++factor)
            {
                if ((number % factor) != 0)
                    continue;
                const int factor2 = number / factor;
                if (factor >= minNumber)
                    result += numbers2[factor - minNumber];
                if ((factor2 >= minNumber) && (factor2 <= maxNumber) && (factor != factor2))
                    result += numbers2[factor2 - minNumber];
            }
        }
        return result;
    }
};

}

namespace FindNumberOfGoodPairs2Task
{

TEST(FindNumberOfGoodPairs2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.numberOfPairs({1, 3, 4}, {1, 3, 4}, 1));
    ASSERT_EQ(2, solution.numberOfPairs({1, 2, 4, 12}, {2, 4}, 3));
}

}