#include <list>
#include <unordered_map>
#include <utility>

#include "gtest/gtest.h"

namespace
{

class LFUCache
{
public:
    LFUCache(int capacity) : _capacity(capacity)
    {
    }

    int get(int key)
    {
        if (_capacity == 0)
            return -1;
        if (_entriesMap.count(key) == 0)
            return -1;
        updateFreq(key);
        return _entriesMap[key]->Value;
    }

    void put(int key, int value)
    {
        if (_capacity == 0)
            return;
        if (_entriesMap.count(key) == 0)
        {
            if (_entries.size() == _capacity)
            {
                TEntryIterator headEntry = _entries.begin();
                TEntryIterator rangeLast = _freqRangeMap[headEntry->Freq].second;
                updateOldRange(rangeLast->Freq, rangeLast);
                _entriesMap.erase(rangeLast->Key);
                _entries.erase(rangeLast);
            }
            _entries.emplace_front(key, value, 1);
            _entriesMap[key] = _entries.begin();
            updateNewRange(1, _entries.begin());
        }
        else
        {
            _entriesMap[key]->Value = value;
            updateFreq(key);
        }
    }

private:
    struct Entry
    {
        Entry(int key, int value, int freq) : Key(key), Value(value), Freq(freq)
        {
        }

        int Key;
        int Value;
        int Freq;
    };

    size_t _capacity;
    std::list<Entry> _entries;
    typedef std::list<Entry>::iterator TEntryIterator;
    std::unordered_map<int, TEntryIterator> _entriesMap;
    std::unordered_map<int, std::pair<TEntryIterator, TEntryIterator>> _freqRangeMap;

    void updateNewRange(int freq, TEntryIterator entryIterator)
    {
        TEntryIterator nextEntryIterator = std::next(entryIterator, 1);
        if ((nextEntryIterator == _entries.end()) || (nextEntryIterator->Freq != freq))
            _freqRangeMap.emplace(freq, std::pair<TEntryIterator, TEntryIterator>(entryIterator, entryIterator));
        else
            _freqRangeMap[freq].first = entryIterator;
    }

    void updateOldRange(int freq, TEntryIterator entryIterator)
    {
        const auto rangeIterator = _freqRangeMap.find(freq);
        if (rangeIterator->second.first == rangeIterator->second.second)
            _freqRangeMap.erase(rangeIterator);
        else if (rangeIterator->second.first == entryIterator)
            rangeIterator->second.first = std::next(rangeIterator->second.first, 1);
        else if (rangeIterator->second.second == entryIterator)
            rangeIterator->second.second = std::prev(rangeIterator->second.second, 1);
    }

    void updateFreq(int key)
    {
        TEntryIterator entryIterator = _entriesMap[key];
        const int currentFreq = entryIterator->Freq;
        const int newFreq = currentFreq + 1;
        const std::pair<TEntryIterator, TEntryIterator> freqRange = _freqRangeMap[currentFreq];
        TEntryIterator newEntryIterator = _entries.emplace(std::next(freqRange.second, 1), key, entryIterator->Value, newFreq);
        _entriesMap[key] = newEntryIterator;
        updateNewRange(newFreq, newEntryIterator);
        updateOldRange(currentFreq, entryIterator);
        _entries.erase(entryIterator);
    }
};

}

namespace LFUCacheTask
{

TEST(LFUCacheTaskTests, Examples)
{
    LFUCache cache(2);
    ASSERT_NO_THROW(cache.put(1, 1));
    ASSERT_NO_THROW(cache.put(2, 2));
    ASSERT_EQ(1, cache.get(1));
    ASSERT_NO_THROW(cache.put(3, 3));
    ASSERT_EQ(-1, cache.get(2));
    ASSERT_EQ(3, cache.get(3));
    ASSERT_NO_THROW(cache.put(4, 4));
    ASSERT_EQ(-1, cache.get(1));
    ASSERT_EQ(3, cache.get(3));
    ASSERT_EQ(4, cache.get(4));
}

TEST(LFUCacheTaskTests, FromWrongAnswers)
{
    LFUCache cache(0);
    ASSERT_NO_THROW(cache.put(0, 0));
    ASSERT_EQ(-1, cache.get(0));
}

}