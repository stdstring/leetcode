#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumPrimeDifference(std::vector<int> const &nums) const
    {
        size_t first = 0;
        for (; !isPrime(nums[first]); ++first) {}
        size_t last = nums.size() - 1;
        for (; !isPrime(nums[last]); --last) {}
        return static_cast<int>(last - first);
    }

private:
    [[nodiscard]] bool isPrime(int number) const
    {
        if (number == 1)
            return false;
        if (number == 2)
            return true;
        if ((number % 2) == 0)
            return false;
        for (int factor = 3; (factor * factor) <= number; factor += 2)
        {
            if ((number % factor) == 0)
                return false;
        }
        return true;
    }
};

}

namespace MaxPrimeDifferenceTask
{

TEST(MaxPrimeDifferenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumPrimeDifference({4, 2, 9, 5, 3}));
    ASSERT_EQ(0, solution.maximumPrimeDifference({4, 8, 2, 8}));
}

}