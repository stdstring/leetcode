#include <algorithm>
#include <list>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class MyHashMap
{
public:
    MyHashMap() : _buckets(InitSize)
    {
    }

    void put(int key, int value)
    {
        std::list<std::pair<int, int>> &bucket(_buckets[hash(key) % _buckets.size()]);
        auto const iterator = find(bucket, key);
        if (iterator == bucket.end())
            bucket.emplace_back(key, value);
        else
            iterator->second = value;
        if (bucket.size() > BucketSize)
            split();
    }

    int get(int key)
    {
        std::list<std::pair<int, int>> const &bucket(_buckets[hash(key) % _buckets.size()]);
        auto const iterator = find(bucket, key);
        return iterator == bucket.cend() ? -1 : iterator->second;
    }

    void remove(int key)
    {
        std::list<std::pair<int, int>> &bucket(_buckets[hash(key) % _buckets.size()]);
        auto const iterator = find(bucket, key);
        if (iterator != bucket.end())
            bucket.erase(iterator);
    }

private:
    static constexpr size_t InitSize = 8;
    static constexpr size_t BucketSize = 8;
    std::vector<std::list<std::pair<int, int>>> _buckets;

    std::list<std::pair<int, int>>::iterator find(std::list<std::pair<int, int>> &bucket, int key) const
    {
        return std::find_if(bucket.begin(), bucket.end(), [key](std::pair<int, int> const &entry){ return entry.first == key; });
    }

    [[nodiscard]] std::list<std::pair<int, int>>::const_iterator find(std::list<std::pair<int, int>> const &bucket, int key) const
    {
        return std::find_if(bucket.cbegin(), bucket.cend(), [key](std::pair<int, int> const &entry){ return entry.first == key; });
    }

    [[nodiscard]] int hash(int key) const
    {
        return key;
    }

    void split()
    {
        const size_t bucketsSize = _buckets.size();
        for (size_t index = 0; index < bucketsSize; ++index)
            _buckets.emplace_back();
        for (size_t index = 0; index < _buckets.size(); ++index)
        {
            const int bucketKey = static_cast<int>(index);
            for (auto iterator = _buckets[index].begin(); iterator != _buckets[index].end();)
            {
                const int currentKey = static_cast<int>(iterator->first % _buckets.size());
                if (currentKey != bucketKey)
                {
                    _buckets[currentKey].emplace_back(iterator->first, iterator->second);
                    iterator = _buckets[index].erase(iterator);
                }
                else
                    ++iterator;
            }
        }
    }
};

}

namespace DesignHashMapTask
{

TEST(DesignHashSetTaskTests, Examples)
{
    MyHashMap hashMap;
    ASSERT_NO_THROW(hashMap.put(1, 1));
    ASSERT_NO_THROW(hashMap.put(2, 2));
    ASSERT_EQ(1, hashMap.get(1));
    ASSERT_EQ(-1, hashMap.get(3));
    ASSERT_NO_THROW(hashMap.put(2, 1));
    ASSERT_EQ(1, hashMap.get(2));
    ASSERT_NO_THROW(hashMap.remove(2));
    ASSERT_EQ(-1, hashMap.get(2));
}

}