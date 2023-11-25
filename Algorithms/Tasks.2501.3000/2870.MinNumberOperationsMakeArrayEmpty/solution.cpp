#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minOperations(std::vector<int> const &nums) const
    {
        std::unordered_map<int, size_t> numberMap;
        for (int number : nums)
            ++numberMap[number];
        size_t operationCount = 0;
        for (auto const &[_, count] : numberMap)
        {
            if (count == 1)
                return -1;
            switch (count % 3)
            {
                case 0:
                    operationCount += (count / 3);
                    break;
                case 1:
                    operationCount += (count / 3 - 1 + 2);
                    break;
                case 2:
                    operationCount += (count / 3 + 1);
                    break;
            default:
                throw std::logic_error("Unexpected control flow");
            }
        }
        return static_cast<int>(operationCount);
    }
};

}

namespace MinNumberOperationsMakeArrayEmptyTask
{

TEST(MinNumberOperationsMakeArrayEmptyTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minOperations({2, 3, 3, 2, 2, 4, 2, 3, 4}));
    ASSERT_EQ(-1, solution.minOperations({2, 1, 2, 2, 3, 3}));
}

}