#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int hIndex(std::vector<int> const &citations) const
    {
        // calc data
        std::vector<size_t> citationsCountData(citations.size(), 0);
        size_t bigCitationsCount = 0;
        for (int citation : citations)
        {
            if (citation > static_cast<int>(citations.size()))
                ++bigCitationsCount;
            else if (citation > 0)
                ++citationsCountData[citation - 1];
        }
        // calc hIndex
        int citationsCount = bigCitationsCount;
        int hIndex = citationsCountData.size();
        for (size_t index = citationsCountData.size(); index > 0; --index)
        {
            const int count = citationsCountData[index - 1];
            if ((hIndex >= citationsCount) && (hIndex <= (citationsCount + count)))
                return hIndex;
            citationsCount += count;
            --hIndex;
        }
        return 0;
    }
};

}

namespace HIndexTask
{

TEST(HIndexTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.hIndex({3, 0, 6, 1, 5}));
}

TEST(HIndexTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1, solution.hIndex({1, 1}));
}

}