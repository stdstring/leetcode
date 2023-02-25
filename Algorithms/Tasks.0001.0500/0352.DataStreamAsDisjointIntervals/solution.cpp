#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class SummaryRanges
{
public:
    SummaryRanges() = default;

    void addNum(int value)
    {
        const auto currentIterator = _storage.lower_bound(value);
        if (currentIterator != _storage.begin())
        {
            const auto beforeIterator = std::prev(currentIterator, 1);
            if (beforeIterator->second[1] >= value)
                return;
            if ((beforeIterator->second[1] + 1) == value)
            {
                ++beforeIterator->second[1];
                if ((currentIterator != _storage.end()) && ((beforeIterator->second[1] + 1) == currentIterator->second[0]))
                {
                    beforeIterator->second[1] = currentIterator->second[1];
                    _storage.erase(currentIterator);
                }
                return;
            }
        }
        if ((currentIterator != _storage.end()) && (value == currentIterator->second[0]))
            return;
        if ((currentIterator != _storage.end()) && ((value + 1) == currentIterator->second[0]))
        {
            _storage.emplace(value, std::vector<int>({value, currentIterator->second[1]}));
            _storage.erase(currentIterator);
            return;
        }
        _storage.emplace(value, std::vector<int>({value, value}));
    }

    std::vector<std::vector<int>> getIntervals()
    {
        std::vector<std::vector<int>> intervals;
        for (auto const &[_, interval] : _storage)
            intervals.emplace_back(interval);
        return intervals;
    }

private:
    std::map<int, std::vector<int>> _storage;
};

}

namespace DataStreamAsDisjointIntervalsTask
{

TEST(DataStreamAsDisjointIntervalsTaskTests, Examples)
{
    SummaryRanges ranges;
    ASSERT_NO_THROW(ranges.addNum(1));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1}}), ranges.getIntervals());
    ASSERT_NO_THROW(ranges.addNum(1));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1}}), ranges.getIntervals());
    ASSERT_NO_THROW(ranges.addNum(3));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1}, {3, 3}}), ranges.getIntervals());
    ASSERT_NO_THROW(ranges.addNum(7));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1}, {3, 3}, {7, 7}}), ranges.getIntervals());
    ASSERT_NO_THROW(ranges.addNum(2));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 3}, {7, 7}}), ranges.getIntervals());
    ASSERT_NO_THROW(ranges.addNum(6));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 3}, {6, 7}}), ranges.getIntervals());
}

}