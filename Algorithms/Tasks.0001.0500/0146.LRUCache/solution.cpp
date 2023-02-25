#include <array>
#include <memory>

#include "gtest/gtest.h"

namespace
{

class LRUCacheItem
{
public:
    LRUCacheItem(int key, int value) : key(key), value(value), prev(nullptr), next(nullptr)
    {
    }

    int key;
    int value;
    std::shared_ptr<LRUCacheItem> prev;
    std::shared_ptr<LRUCacheItem> next;
};

class LRUCache {
public:
    LRUCache(int capacity) : _storage({}), _queueHead(nullptr), _queueTail(nullptr), _capacity(capacity), _size(0)
    {
        _storage.fill(nullptr);
    }

    int get(int key)
    {
        if (_storage[key - MinKeyValue] == nullptr)
            return -1;
        useItem(_storage[key - MinKeyValue]);
        return _storage[key - MinKeyValue]->value;
    }

    void put(int key, int value)
    {
        if (_storage[key - MinKeyValue] == nullptr)
        {
            std::shared_ptr<LRUCacheItem> item = std::make_shared<LRUCacheItem>(key, value);
            _storage[key - MinKeyValue] = item;
            // add to head
            if (_size == 0)
                _queueHead = _queueTail = item;
            else
            {
                item->next = _queueHead;
                _queueHead->prev = item;
                _queueHead = item;
            }
            // remove tail if needed
            if (_size == _capacity)
            {
                std::shared_ptr<LRUCacheItem> tail = _queueTail;
                _queueTail = tail->prev;
                _queueTail->next = nullptr;
                _storage[tail->key - MinKeyValue] = nullptr;
                tail.reset();
            }
            else
                ++_size;
        }
        else
        {
            _storage[key - MinKeyValue]->value = value;
            useItem(_storage[key - MinKeyValue]);
        }
    }

private:
    static constexpr int MinKeyValue = 0;
    static constexpr int MaxKeyValue = 3000;

    void useItem(std::shared_ptr<LRUCacheItem> const &item)
    {
        if (_size == 1)
            return;
        if (item->prev == nullptr)
            return;
        if (item->next == nullptr)
        {
            _queueTail = item->prev;
            _queueTail->next = nullptr;
        }
        else
        {
            item->prev->next = item->next;
            item->next->prev = item->prev;
        }
        _queueHead->prev = item;
        item->prev = nullptr;
        item->next = _queueHead;
        _queueHead = item;
    }

    std::array<std::shared_ptr<LRUCacheItem>, MaxKeyValue - MinKeyValue + 1> _storage;
    std::shared_ptr<LRUCacheItem> _queueHead;
    std::shared_ptr<LRUCacheItem> _queueTail;
    size_t _capacity;
    size_t _size;
};

}

namespace LRUCacheTask
{

TEST(LRUCacheTaskTests, Examples)
{
    LRUCache lruCache(2);
    lruCache.put(1, 1); // cache is {1=1}
    lruCache.put(2, 2); // cache is {1=1, 2=2}
    ASSERT_EQ(1, lruCache.get(1));
    lruCache.put(3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    ASSERT_EQ(-1, lruCache.get(2));
    lruCache.put(4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
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