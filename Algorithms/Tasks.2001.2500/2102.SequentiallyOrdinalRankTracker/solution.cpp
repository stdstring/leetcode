#include <set>
#include <string>
#include <utility>

#include "gtest/gtest.h"

namespace
{

class SORTracker
{
public:
    SORTracker() : _current(_locations.cbegin())
    {
    }

    void add(std::string const &name, int score)
    {
        TEntry newEntry(score, name);
        _locations.emplace(newEntry);
        if ((_current == _locations.cend()) || _locations.key_comp()(newEntry, *_current))
            --_current;
    }

    std::string get()
    {
        std::string location(_current->second);
        ++_current;
        return location;
    }

private:
    typedef std::pair<int, std::string> TEntry;

    struct EntryComp
    {
        bool operator()(TEntry const &left, TEntry const &right) const
        {
            return (left.first > right.first) || ((left.first == right.first) && (left.second < right.second));
        }
    };

    std::set<TEntry, EntryComp> _locations;
    std::set<TEntry, EntryComp>::iterator _current;
};

}

namespace SequentiallyOrdinalRankTrackerTask
{

TEST(SequentiallyOrdinalRankTrackerTaskTests, Examples)
{
    SORTracker tracker;
    ASSERT_NO_THROW(tracker.add("bradford", 2));
    ASSERT_NO_THROW(tracker.add("branford", 3));
    ASSERT_EQ("branford", tracker.get());
    ASSERT_NO_THROW(tracker.add("alps", 2));
    ASSERT_EQ("alps", tracker.get());
    ASSERT_NO_THROW(tracker.add("orland", 2));
    ASSERT_EQ("bradford", tracker.get());
    ASSERT_NO_THROW(tracker.add("orlando", 3));
    ASSERT_EQ("bradford", tracker.get());
    ASSERT_NO_THROW(tracker.add("alpine", 2));
    ASSERT_EQ("bradford", tracker.get());
    ASSERT_EQ("orland", tracker.get());
}

}