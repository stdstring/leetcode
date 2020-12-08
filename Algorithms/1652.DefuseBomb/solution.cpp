#include <cstdlib>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> decrypt(std::vector<int> const &code, int k) const
    {
        std::vector<int> result(code.size(), 0);
        if (k == 0)
            return result;
        const size_t shiftSize = std::abs(k);
        const int direction = k > 0 ? 1 : -1;
        for (size_t index = 0; index < code.size(); ++index)
            result[index] = sumKElements(code, index, shiftSize, direction);
        return result;
    }

private:
    int sumKElements(std::vector<int> const &code, size_t index, size_t shiftSize, int direction) const
    {
        int sum = 0;
        for (size_t shift = 1; shift <= shiftSize; ++shift)
            sum += code[(code.size() + index + shift * direction) % code.size()];
        return sum;
    }
};

}

namespace DefuseBombTask
{

TEST(DefuseBombTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({12, 10, 16, 13}), solution.decrypt({5, 7, 1, 4}, 3));
    ASSERT_EQ(std::vector<int>({0, 0, 0, 0}), solution.decrypt({1, 2, 3, 4}, 0));
    ASSERT_EQ(std::vector<int>({12, 5, 6, 13}), solution.decrypt({2, 4, 9, 3}, -2));
}

}