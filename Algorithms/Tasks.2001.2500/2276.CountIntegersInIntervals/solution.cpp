#include <iterator>
#include <map>

#include "gtest/gtest.h"

namespace
{

class CountIntervals
{
public:
    CountIntervals() = default;

    void add(int left, int right)
    {
        auto currentIterator = _rangesMap.lower_bound(left);
        if ((currentIterator != _rangesMap.cend()) && (currentIterator->first == left) && (right <= currentIterator->second))
            return;
        if (currentIterator != _rangesMap.cbegin())
        {
            const auto prevIterator = std::prev(currentIterator, 1);
            if ((prevIterator->first < left) && (right <= prevIterator->second))
                return;
            if (prevIterator->second >= left)
            {
               _numbersCount -= (1 + prevIterator->second - prevIterator->first);
               left = prevIterator->first;
               _rangesMap.erase(prevIterator);
            }
        }
        while ((currentIterator != _rangesMap.cend()) && (currentIterator->first <= right))
        {
            const auto nextIterator = std::next(currentIterator, 1);
            _numbersCount -= (1 + currentIterator->second - currentIterator->first);
            right = std::max(right, currentIterator->second);
            _rangesMap.erase(currentIterator);
            currentIterator = nextIterator;
        }
        _rangesMap.emplace(left, right);
        _numbersCount += (1 + right - left);
    }

    [[nodiscard]] int count() const
    {
        return static_cast<int>(_numbersCount);
    }

private:
    std::map<int, int> _rangesMap;
    size_t _numbersCount = 0;
};

}

namespace CountIntegersInIntervalsTask
{

TEST(CountIntegersInIntervalsTaskTests, Examples)
{
    CountIntervals countIntervals;
    ASSERT_NO_THROW(countIntervals.add(2, 3));
    ASSERT_NO_THROW(countIntervals.add(7, 10));
    ASSERT_EQ(6, countIntervals.count());
    ASSERT_NO_THROW(countIntervals.add(5, 8));
    ASSERT_EQ(8, countIntervals.count());
}

TEST(CountIntegersInIntervalsTaskTests, FromWrongAnswers)
{
    CountIntervals countIntervals;
    ASSERT_EQ(0, countIntervals.count());
    ASSERT_NO_THROW(countIntervals.add(8, 43));
    ASSERT_NO_THROW(countIntervals.add(13, 16));
    ASSERT_NO_THROW(countIntervals.add(26, 33));
    ASSERT_NO_THROW(countIntervals.add(28, 36));
    ASSERT_NO_THROW(countIntervals.add(29, 37));
    ASSERT_EQ(36, countIntervals.count());
    ASSERT_NO_THROW(countIntervals.add(34, 46));
    ASSERT_NO_THROW(countIntervals.add(10, 23));
}

}