#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> lexicalOrder(int n) const
    {
        std::vector<int> dest;
        dest.reserve(n);
        generate(dest, 1, std::min(9, n), n);
        return dest;
    }

private:
    void generate(std::vector<int> &dest, int startNumber, int endNumber, int maxNumber) const
    {
        for (int number = startNumber; number <= endNumber; ++number)
        {
            dest.push_back(number);
            if (10 * number <= maxNumber)
                generate(dest, 10 * number, std::min(10 * number + 9, maxNumber), maxNumber);
        }
    }
};

}

namespace LexicographicalNumbersTask
{

TEST(LexicographicalNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9}), solution.lexicalOrder(13));
    ASSERT_EQ(std::vector<int>({1, 2}), solution.lexicalOrder(2));
}

}