#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> getStrongest(std::vector<int> const &arr, int k) const
    {
        std::vector<size_t> indices(arr.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        const auto median = std::next(indices.begin(), static_cast<int>((indices.size() - 1) / 2));
        std::ranges::nth_element(indices, median, [&arr](size_t l, size_t r) { return arr[l] < arr[r]; });
        int medianValue = arr[*median];
        auto comp = [&arr, medianValue](size_t l, size_t r)
        {
            const int leftDelta = std::abs(arr[l] - medianValue);
            const int rightDelta = std::abs(arr[r] - medianValue);
            if (leftDelta != rightDelta)
                return leftDelta > rightDelta;
            if (arr[l] != arr[r])
                return arr[l] > arr[r];
            return l > r;
        };
        std::ranges::partial_sort(indices, std::next(indices.begin(), k), comp);
        std::vector<int> result(k, 0);
        for (size_t index = 0; index < result.size(); ++index)
            result[index] = arr[indices[index]];
        return result;
    }
};

}

namespace KStrongestValuesInArrayTask
{

TEST(KStrongestValuesInArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({5, 1}), solution.getStrongest({1, 2, 3, 4, 5}, 2));
    ASSERT_EQ(std::vector<int>({5, 5}), solution.getStrongest({1, 1, 3, 5, 5}, 2));
    ASSERT_EQ(std::vector<int>({11, 8, 6, 6, 7}), solution.getStrongest({6, 7, 11, 7, 6, 8}, 5));
}

}