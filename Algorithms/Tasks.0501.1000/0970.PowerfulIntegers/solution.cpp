#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> powerfulIntegers(int x, int y, int bound) const
    {
        std::vector<int> xPows(generatePowers(x, bound));
        std::vector<int> yPows(generatePowers(y, bound));
        std::unordered_set<int> knownResults;
        std::vector<int> result;
        for (int xPow : xPows)
        {
            for (int yPow : yPows)
            {
                int sum = xPow + yPow;
                if (sum > bound)
                    break;
                if (knownResults.count(sum) == 0)
                {
                    result.push_back(sum);
                    knownResults.insert(sum);
                }
            }
        }
        return result;
    }

private:
    std::vector<int> generatePowers(int number, int bound) const
    {
        if (number == 1)
            return {1};
        std::vector<int> powers;
        int power = 1;
        while (power <= bound)
        {
            powers.push_back(power);
            power *= number;
        }
        return powers;
    }
};

}

namespace PowerfulIntegersTask
{

TEST(PowerfulIntegersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 4, 10, 3, 5, 7, 9}), solution.powerfulIntegers(2, 3, 10));
    ASSERT_EQ(std::vector<int>({2, 6, 4, 8, 10, 14}), solution.powerfulIntegers(3, 5, 15));
}

}