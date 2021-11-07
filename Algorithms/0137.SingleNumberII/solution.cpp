#include <array>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int singleNumber(std::vector<int> const &nums) const
    {
        constexpr size_t bitsCount = 8 * sizeof(int);
        std::array<int, bitsCount> bitMasks{};
        bitMasks[0] = 1;
        for (size_t index = 1; index < bitsCount; ++index)
            bitMasks[index] = bitMasks[index - 1] << 1;
        // we calculate count of bits which is one for each position in 32-bit number
        std::array<size_t, bitsCount> bitCountData{};
        bitCountData.fill(0);
        for (int number : nums)
        {
            for (size_t index = 0; index < bitsCount; ++index)
            {
                if ((number & bitMasks[index]) != 0)
                    ++bitCountData[index];
            }
        }
        // if count of one bits equal 3 * N + 1 for some position, then this bit equals one for single number
        int result = 0;
        for (size_t index = 0; index < bitsCount; ++index)
        {
            if ((bitCountData[index] % 3) != 0)
                result += bitMasks[index];
        }
        return result;
    }
};

}

namespace SingleNumberIITask
{

TEST(SingleNumberIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.singleNumber({2, 2, 3, 2}));
    ASSERT_EQ(99, solution.singleNumber({0, 1, 0, 1, 0, 1, 99}));
}

}