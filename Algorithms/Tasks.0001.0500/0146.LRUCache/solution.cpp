#include <list>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class LRUCache
{
public:
    LRUCache(int capacity) : _capacity(capacity)
    {
    }

    int get(int key)
    {
        const auto iterator = _keys.find(key);
        if (iterator == _keys.cend())
            return -1;
        const TEntry entry(*iterator->second);
        _entries.erase(iterator->second);
        _entries.push_front(entry);
        iterator->second = _entries.cbegin();
        return entry.second;
    }

    void put(int key, int value)
    {
        const auto iterator = _keys.find(key);
        if (iterator == _keys.cend())
        {
            _entries.emplace_front(key, value);
            _keys.emplace(key, _entries.cbegin());
        }
        else
        {
            const TEntry entry(key, value);
            _entries.erase(iterator->second);
            _entries.push_front(entry);
            iterator->second = _entries.cbegin();
        }
        if (_entries.size() > _capacity)
        {
            const TEntry lastEntry(_entries.back());
            _entries.pop_back();
            _keys.erase(lastEntry.first);
        }
    }

private:
    typedef std::pair<int, int> TEntry;
    size_t _capacity;
    std::unordered_map<int, std::list<TEntry>::const_iterator> _keys;
    std::list<TEntry> _entries;
};

}

namespace LRUCacheTask
{

TEST(LRUCacheTaskTests, Examples)
{
    LRUCache lruCache(2);
    // cache is {1=1}
    lruCache.put(1, 1);
    // cache is {1=1, 2=2}
    lruCache.put(2, 2);
    ASSERT_EQ(1, lruCache.get(1));
    // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    lruCache.put(3, 3);
    ASSERT_EQ(-1, lruCache.get(2));
    // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    lruCache.put(4, 4);
    ASSERT_EQ(-1, lruCache.get(1));
    ASSERT_EQ(3, lruCache.get(3));
    ASSERT_EQ(4, lruCache.get(4));
}

TEST(LRUCacheTaskTests, FromWrongAnswers)
{
    LRUCache lruCache(2);
    lruCache.put(2, 1);
    ASSERT_EQ(1, lruCache.get(2));
    lruCache.put(2, 2);
    ASSERT_EQ(2, lruCache.get(2));
    lruCache.put(1, 1);
    lruCache.put(4, 1);
    ASSERT_EQ(-1, lruCache.get(2));
}

}