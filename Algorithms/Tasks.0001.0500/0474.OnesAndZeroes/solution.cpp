#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findMaxForm(std::vector<std::string> const &strs, int m, int n) const
    {
        const size_t total0 = m;
        const size_t total1 = n;
        std::vector<std::vector<size_t>> subsetSizeData(total0 + 1, std::vector<size_t>(total1 + 1, 0));
        size_t maxSize = 0;
        for (std::string const &str : strs)
        {
            size_t count0 = 0;
            size_t count1 = 0;
            calcStrMetrics(str, count0, count1);
            if (count0 > total0 || count1 > total1)
                continue;
            for (size_t rowDelta = 0; rowDelta <= total0 - count0; ++rowDelta)
            {
                const size_t row = total0 - count0 - rowDelta;
                for (size_t columnDelta = 0; columnDelta <= total1 - count1; ++columnDelta)
                {
                    const size_t column = total1 - count1 - columnDelta;
                    subsetSizeData[row + count0][column + count1] = std::max(subsetSizeData[row + count0][column + count1], subsetSizeData[row][column] + 1);
                    maxSize = std::max(maxSize, subsetSizeData[row + count0][column + count1]);
                }
            }
            subsetSizeData[count0][count1] = std::max(subsetSizeData[count0][count1], static_cast<size_t>(1));
            maxSize = std::max(maxSize, subsetSizeData[count0][count1]);
        }
        return static_cast<int>(maxSize);
    }

private:
    void calcStrMetrics(std::string const &str, size_t &count0, size_t &count1) const
    {
        for (char ch : str)
        {
            if (ch == '0')
                ++count0;
            if (ch == '1')
                ++count1;
        }
    }
};

}

namespace OnesAndZeroesTask
{

TEST(OnesAndZeroesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.findMaxForm({"10", "0001", "111001", "1", "0"}, 5, 3));
    ASSERT_EQ(2, solution.findMaxForm({"10", "0", "1"}, 1, 1));
}

}