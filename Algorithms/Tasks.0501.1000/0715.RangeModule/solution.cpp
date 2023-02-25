#include <algorithm>
#include <iterator>
#include <map>

#include "gtest/gtest.h"

namespace
{

class RangeModule
{
public:
    RangeModule() = default;

    void addRange(int left, int right)
    {
        auto iterator = _rangeMap.upper_bound(left);
        if (iterator != _rangeMap.cbegin())
        {
            const auto prevIterator = std::prev(iterator, 1);
            if (right < prevIterator->second)
                return;
            if (left <= prevIterator->second)
            {
                left = prevIterator->first;
                _rangeMap.erase(prevIterator);
            }
        }
        while ((iterator != _rangeMap.cend()) && (iterator->first <= right))
        {
            right = std::max(right, iterator->second);
            const auto nextIterator = std::next(iterator, 1);
            _rangeMap.erase(iterator);
            iterator = nextIterator;
        }
        _rangeMap.emplace(left, right);
    }

    bool queryRange(int left, int right)
    {
        auto iterator = _rangeMap.upper_bound(left);
        if (iterator == _rangeMap.cbegin())
            return false;
        iterator = std::prev(iterator, 1);
        return (iterator->first <= left) && (right <= iterator->second);
    }

    void removeRange(int left, int right)
    {
        auto iterator = _rangeMap.upper_bound(left);
        if (iterator != _rangeMap.cbegin())
        {
            const auto prevIterator = std::prev(iterator, 1);
            const int prevRangeLeft = prevIterator->first;
            const int prevRangeRight = prevIterator->second;
            if (prevRangeRight > left)
            {
                if (prevRangeLeft < left)
                    prevIterator->second = left;
                if (prevRangeLeft == left)
                    _rangeMap.erase(prevIterator);
                if (right < prevRangeRight)
                    _rangeMap.emplace(right, prevRangeRight);
            }
        }
        while ((iterator != _rangeMap.cend()) && (iterator->first < right))
        {
            const int rangeRight = iterator->second;
            const auto nextIterator = std::next(iterator, 1);
            _rangeMap.erase(iterator);
            iterator = nextIterator;
            if (right < rangeRight)
                _rangeMap.emplace(right, rangeRight);
        }
    }

private:
    std::map<int, int> _rangeMap;
};

}

namespace RangeModuleTask
{

TEST(RangeModuleTaskTests, Examples)
{
    RangeModule rangeModule;
    ASSERT_NO_THROW(rangeModule.addRange(10, 20));
    ASSERT_NO_THROW(rangeModule.removeRange(14, 16));
    ASSERT_EQ(true, rangeModule.queryRange(10, 14));
    ASSERT_EQ(false, rangeModule.queryRange(13, 15));
    ASSERT_EQ(true, rangeModule.queryRange(16, 17));
}

TEST(RangeModuleTaskTests, FromWrongAnswers)
{
    RangeModule rangeModule;
    ASSERT_NO_THROW(rangeModule.addRange(48, 91));
    ASSERT_NO_THROW(rangeModule.removeRange(21, 88));
    ASSERT_NO_THROW(rangeModule.addRange(89, 97));
    ASSERT_NO_THROW(rangeModule.removeRange(56, 72));
    ASSERT_NO_THROW(rangeModule.removeRange(16, 75));
    ASSERT_NO_THROW(rangeModule.removeRange(46, 60));
    ASSERT_NO_THROW(rangeModule.removeRange(20, 62));
    ASSERT_NO_THROW(rangeModule.addRange(5, 78));
    ASSERT_NO_THROW(rangeModule.addRange(58, 61));
    ASSERT_NO_THROW(rangeModule.removeRange(38, 70));
    ASSERT_EQ(false, rangeModule.queryRange(72, 96));
}

}