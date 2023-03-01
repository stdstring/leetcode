#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> sortArray(std::vector<int> const &nums) const
    {
        std::vector<int> result(nums);
        mergeSort(result, 0, result.size());
        return result;
    }

private:
    void mergeSort(std::vector<int> &data, size_t index, size_t size) const
    {
        if (size == 1)
            return;
        if (size == 2)
        {
            if (data[index] > data[index + 1])
                std::swap(data[index], data[index + 1]);
            return;
        }
        const size_t leftSize = size / 2;
        const size_t rightSize = size - leftSize;
        mergeSort(data, index, leftSize);
        mergeSort(data, index + leftSize, rightSize);
        std::vector<int> buffer(size, 0);
        size_t leftIndex = 0;
        size_t rightIndex = 0;
        size_t bufferIndex = 0;
        while ((leftIndex < leftSize) && (rightIndex < rightSize))
        {
            if (data[index + leftIndex] < data[index + leftSize + rightIndex])
            {
                buffer[bufferIndex] = data[index + leftIndex];
                ++leftIndex;
            }
            else
            {
                buffer[bufferIndex] = data[index + leftSize + rightIndex];
                ++rightIndex;
            }
            ++bufferIndex;
        }
        if (leftIndex < leftSize)
            std::copy(std::next(data.cbegin(), static_cast<int>(index + leftIndex)),
                      std::next(data.cbegin(), static_cast<int>(index + leftSize)),
                      std::next(buffer.begin(), static_cast<int>(bufferIndex)));
        if (rightIndex < rightSize)
            std::copy(std::next(data.cbegin(), static_cast<int>(index + leftSize + rightIndex)),
                      std::next(data.cbegin(), static_cast<int>(index + size)),
                      std::next(buffer.begin(), static_cast<int>(bufferIndex)));
        std::copy(buffer.cbegin(), buffer.cend(), std::next(data.begin(), static_cast<int>(index)));
    }
};

}

namespace SortArrayTask
{

TEST(SortArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3, 5}), solution.sortArray({5, 2, 3, 1}));
    ASSERT_EQ(std::vector<int>({0, 0, 1, 1, 2, 5}), solution.sortArray({5, 1, 1, 2, 0, 0}));
}

}