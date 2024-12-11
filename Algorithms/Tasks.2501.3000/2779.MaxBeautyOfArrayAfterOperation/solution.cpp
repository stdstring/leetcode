#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumBeauty(std::vector<int> const &nums, int k) const
    {
        int delta = 2 * k;
        // init
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        size_t end = 0;
        for (;(end < numbers.size()) && ((numbers[end] - numbers[0]) <= delta); ++end){}
        size_t maxBeautySize = end;
        // move
        for (size_t start = 0; end < numbers.size(); ++end)
        {
            for(; (numbers[end] - numbers[start]) > delta; ++start){}
            maxBeautySize = std::max(maxBeautySize, end - start + 1);
        }
        return static_cast<int>(maxBeautySize);
    }
};

}

namespace MaxBeautyOfArrayAfterOperationTask
{

TEST(MaxBeautyOfArrayAfterOperationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumBeauty({4, 6, 1, 2}, 2));
    ASSERT_EQ(4, solution.maximumBeauty({1, 1, 1, 1}, 10));
}

}