#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> flipAndInvertImage(std::vector<std::vector<int>> const &image) const
    {
        std::vector<std::vector<int>> dest;
        for (std::vector<int> const &sourceRow : image)
        {
            std::vector<int> destRow;
            std::transform(sourceRow.cbegin(), sourceRow.cend(), std::back_inserter(destRow), [](int value) { return value == 0 ? 1 : 0; });
            std::reverse(destRow.begin(), destRow.end());
            dest.push_back(destRow);
        }
        return dest;
    }
};

}

namespace FlippingImageTask
{

TEST(FlippingImageTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 0, 0}, {0, 1, 0}, {1, 1, 1}}), solution.flipAndInvertImage({{1, 1, 0}, {1, 0, 1}, {0, 0, 0}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 1}, {1, 0, 1, 0}}), solution.flipAndInvertImage({{1, 1, 0, 0}, {1, 0, 0, 1}, {0, 1, 1, 1}, {1, 0, 1, 0}}));
}

}