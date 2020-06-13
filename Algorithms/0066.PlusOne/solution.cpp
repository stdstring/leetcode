#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> plusOne(std::vector<int>& digits)
    {
        for (std::vector<int>::reverse_iterator it = digits.rbegin(); it != digits.rend(); ++it)
        {
            const int oldValue = *it;
            const int newValue = oldValue + 1;
            *it = newValue % 10;
            if (newValue < 10)
                return digits;
        }
        digits.insert(digits.begin(), 1);
        return digits;
    }
};

}

namespace PlusOneTask
{

TEST(PlusOneTaskTests, Examples)
{
    Solution solution;
    std::vector<int> digits1({1, 2, 3});
    ASSERT_EQ(std::vector<int>({1, 2, 4}), solution.plusOne(digits1));
    std::vector<int> digits2({4, 3, 2, 1});
    ASSERT_EQ(std::vector<int>({4, 3, 2, 2}), solution.plusOne(digits2));
}

}