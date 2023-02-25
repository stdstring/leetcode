#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int hIndex(std::vector<int> const &citations) const
    {
        if (citations.empty())
            return 0;
        if (citations.size() == 1)
            return citations[0] > 0 ? 1 : 0;
        const int size = static_cast<int>(citations.size());
        int left = 0;
        int right = size - 1;
        while ((right - left) > 1)
        {
            const int middle = (left + right) / 2;
            const int count = size - middle;
            if (count <= citations[middle] && count >= citations[middle - 1])
                return count;
            if (count > citations[middle])
                left = middle;
            else
                right = middle;
        }
        const int leftCount = size - left;
        const int rightCount = size - right;
        if (citations[left] == citations[right])
            return std::min(citations[left], std::max(leftCount, rightCount));
        if (leftCount <= citations[left])
            return leftCount;
        if (rightCount <= citations[right])
            return rightCount;
        return 0;
    }
};

}

namespace HIndexIITask
{

TEST(HIndexIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.hIndex({0, 1, 3, 5, 6}));
}

TEST(HIndexIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.hIndex({}));
    ASSERT_EQ(1, solution.hIndex({0, 1}));
}

}