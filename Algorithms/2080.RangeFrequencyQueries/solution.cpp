#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class RangeFreqQuery
{
public:
    RangeFreqQuery(std::vector<int> const &arr)
    {
        for (size_t index = 0; index < arr.size(); ++index)
            _numberIndicesMap[arr[index]].push_back(static_cast<int>(index));
    }

    [[nodiscard]] int query(int left, int right, int value) const
    {
        const auto iterator = _numberIndicesMap.find(value);
        if (iterator == _numberIndicesMap.cend())
            return 0;
        const std::pair<int, int> leftData(findIndicesLRPair(left, iterator->second));
        if (leftData.second == -1)
            return 0;
        const std::pair<int, int> rightData(findIndicesLRPair(right, iterator->second));
        if (rightData.first == -1)
            return 0;
        return rightData.first - leftData.second + 1;
    }

private:
    std::unordered_map<int, std::vector<int>> _numberIndicesMap;

    [[nodiscard]] std::pair<int, int> findIndicesLRPair(int source, std::vector<int> const &indices) const
    {
        const int lastIndex = static_cast<int>(indices.size() - 1);
        if (source < indices.front())
            return {-1, 0};
        if (source == indices.front())
            return {0, 0};
        if (source == indices.back())
            return {lastIndex, lastIndex};
        if (source > indices.back())
            return {lastIndex, -1};
        int left = 0;
        int right = lastIndex;
        while ((right - left) > 1)
        {
            int middle = (left + right) / 2;
            if (indices[middle] == source)
                return {middle, middle};
            (indices[middle] < source ? left : right) = middle;
        }
        return {left, right};
    }
};

}

namespace RangeFrequencyQueriesTask
{

TEST(RangeFrequencyQueriesTaskTests, Examples)
{
    const RangeFreqQuery rangeFreqQuery({12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56});
    ASSERT_EQ(1, rangeFreqQuery.query(1, 2, 4));
    ASSERT_EQ(2, rangeFreqQuery.query(0, 11, 33));
}

TEST(RangeFrequencyQueriesTaskTests, FromWrongAnswers)
{
    const RangeFreqQuery rangeFreqQuery({8, 4, 2, 5, 4, 5, 8, 6, 2, 3});
    ASSERT_EQ(1, rangeFreqQuery.query(0, 3, 5));
    ASSERT_EQ(0, rangeFreqQuery.query(5, 6, 2));
    ASSERT_EQ(0, rangeFreqQuery.query(6, 8, 4));
    ASSERT_EQ(0, rangeFreqQuery.query(2, 8, 3));
    ASSERT_EQ(0, rangeFreqQuery.query(4, 5, 1));
    ASSERT_EQ(1, rangeFreqQuery.query(2, 4, 2));
}

}