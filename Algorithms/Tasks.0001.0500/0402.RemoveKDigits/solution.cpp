#include <queue>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string removeKdigits(std::string const &num, int k) const
    {
        std::vector<std::queue<size_t>> digitPositions(10);
        for (size_t index = 0; index < num.size(); ++index)
        {
            const size_t digit = static_cast<size_t>(num[index]) - '0';
            digitPositions[digit].push(index);
        }
        size_t resultRestSize = num.size() - k;
        std::string result;
        size_t currentIndex = 0;
        while (resultRestSize > 0)
        {
            for (size_t digit = 0; digit < 10; ++digit)
            {
                while (!digitPositions[digit].empty() && digitPositions[digit].front() < currentIndex)
                    digitPositions[digit].pop();
                if (digitPositions[digit].empty())
                    continue;
                const size_t restSize = num.size() - digitPositions[digit].front();
                if (restSize < resultRestSize)
                    continue;
                if (digit != 0 || !result.empty())
                    result.push_back(static_cast<char>('0' + digit));
                currentIndex = digitPositions[digit].front();
                digitPositions[digit].pop();
                break;
            }
            --resultRestSize;
        }
        return result.empty() ? "0" : result;
    }
};

}

namespace RemoveKDigitsTask
{

TEST(RemoveKDigitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("1219", solution.removeKdigits("1432219", 3));
    ASSERT_EQ("200", solution.removeKdigits("10200", 1));
    ASSERT_EQ("0", solution.removeKdigits("10", 2));
}

}