#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class FindSumPairs
{
public:
    FindSumPairs(std::vector<int> const &nums1, std::vector<int> const &nums2) : _nums1(nums1), _nums2(nums2)
    {
        for (int number : nums2)
            ++_nums2Map[number];
    }

    void add(int index, int val)
    {
        const auto iterator = _nums2Map.find(_nums2[index]);
        _nums2[index] += val;
        ++_nums2Map[_nums2[index]];
        if (iterator->second == 1)
            _nums2Map.erase(iterator);
        else
            --iterator->second;
    }

    int count(int tot)
    {
        size_t result = 0;
        for (const int number : _nums1)
        {
            auto iterator = _nums2Map.find(tot - number);
            result += (iterator == _nums2Map.cend() ? 0 : iterator->second);
        }
        return static_cast<int>(result);
    }

private:
    std::vector<int> _nums1;
    std::vector<int> _nums2;
    std::unordered_map<int, size_t> _nums2Map;
};

}

namespace FindingPairsWithCertainSumTask
{

TEST(FindingPairsWithCertainSumTaskTests, Examples)
{
    FindSumPairs findSumPairs({1, 1, 2, 2, 2, 3}, {1, 4, 5, 2, 5, 4});
    ASSERT_EQ(8, findSumPairs.count(7));
    ASSERT_NO_THROW(findSumPairs.add(3, 2));
    ASSERT_EQ(2, findSumPairs.count(8));
    ASSERT_EQ(1, findSumPairs.count(4));
    ASSERT_NO_THROW(findSumPairs.add(0, 1));
    ASSERT_NO_THROW(findSumPairs.add(1, 1));
    ASSERT_EQ(11, findSumPairs.count(7));
}

}