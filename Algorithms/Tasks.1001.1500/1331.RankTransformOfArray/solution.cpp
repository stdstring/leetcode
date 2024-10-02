#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> arrayRankTransform(std::vector<int> const& arr) const
    {
        std::vector<size_t> indices(arr.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::ranges::sort(indices, [&arr](size_t left, size_t right){ return arr[left] < arr[right]; });
        int rank = 1;
        std::vector<int> result(arr.size(), 0);
        for (size_t index = 0; index < indices.size(); ++index)
        {
            if ((index > 0) && (arr[indices[index]] != arr[indices[index - 1]]))
                ++rank;
            result[indices[index]] = rank;
        }
        return result;
    }
};

}

namespace RankTransformOfArrayTask
{

TEST(RankTransformOfArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({4, 1, 2, 3}), solution.arrayRankTransform({40, 10, 20, 30}));
    ASSERT_EQ(std::vector<int>({1, 1, 1}), solution.arrayRankTransform({100, 100, 100}));
    ASSERT_EQ(std::vector<int>({5, 3, 4, 2, 8, 6, 7, 1, 3}), solution.arrayRankTransform({37, 12, 28, 9, 100, 56, 80, 5, 12}));
}

}