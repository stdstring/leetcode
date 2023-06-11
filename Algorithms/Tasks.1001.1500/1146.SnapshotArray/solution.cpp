#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class SnapshotArray
{
public:
    SnapshotArray(int length) : _data(length, std::vector<HistoryItem>())
    {
    }

    void set(int index, int val)
    {
        if (_data[index].empty())
            _data[index].emplace_back(0, 0);
        if (_data[index].back().SnapId == currentSnapId)
            _data[index].back().Value = val;
        else
            _data[index].emplace_back(currentSnapId, val);
    }

    int snap()
    {
        return currentSnapId++;
    }

    int get(int index, int snapId)
    {
        if (_data[index].empty())
            return 0;
        if (snapId == 0)
            return _data[index].front().Value;
        if (_data[index].back().SnapId <= snapId)
            return _data[index].back().Value;
        auto comp = [](HistoryItem const& item, int snap) { return item.SnapId < snap; };
        const auto iterator = std::lower_bound(_data[index].cbegin(), _data[index].cend(), snapId, comp);
        if (iterator->SnapId == snapId)
            return iterator->Value;
        return std::prev(iterator, 1)->Value;
    }

private:
    struct HistoryItem
    {
        HistoryItem(int snapId, int value) : SnapId(snapId), Value(value)
        {
        }

        int SnapId;
        int Value;
    };

    std::vector<std::vector<HistoryItem>> _data;
    int currentSnapId = 0;
};

}

namespace SnapshotArrayTask
{

TEST(SnapshotArrayTaskTests, Examples)
{
    SnapshotArray snapshotArray(3);
    ASSERT_NO_THROW(snapshotArray.set(0, 5));
    ASSERT_EQ(0, snapshotArray.snap());
    ASSERT_NO_THROW(snapshotArray.set(0, 6));
    ASSERT_EQ(5, snapshotArray.get(0, 0));
}

TEST(SnapshotArrayTaskTests, FromWrongAnswers)
{
    SnapshotArray snapshotArray(3);
    ASSERT_NO_THROW(snapshotArray.set(1, 6));
    ASSERT_EQ(0, snapshotArray.snap());
    ASSERT_EQ(1, snapshotArray.snap());
    ASSERT_NO_THROW(snapshotArray.set(1, 19));
    ASSERT_NO_THROW(snapshotArray.set(0, 4));
    ASSERT_EQ(0, snapshotArray.get(2, 1));
    ASSERT_EQ(0, snapshotArray.get(2, 0));
    ASSERT_EQ(0, snapshotArray.get(0, 1));
}

}