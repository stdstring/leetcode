#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int arrayPairSum(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        int result = 0;
        for (size_t index = 0; index < numbers.size(); index += 2)
            result += numbers[index];
        return result;
    }
};

}

namespace ArrayPartitionITask
{

TEST(ArrayPartitionITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.arrayPairSum({1, 4, 3, 2}));
}


}