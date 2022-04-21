#include <algorithm>
#include <list>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class MyHashSet
{
public:
    MyHashSet() : _buckets(InitSize)
    {
    }

    void add(int key)
    {
        std::list<int> &bucket(_buckets[hash(key) % _buckets.size()]);
        if (std::find(bucket.cbegin(), bucket.cend(), key) == bucket.cend())
            bucket.push_back(key);
        if (bucket.size() > BucketSize)
            split();
    }

    void remove(int key)
    {
        std::list<int> &bucket(_buckets[hash(key) % _buckets.size()]);
        bucket.remove(key);
    }

    bool contains(int key)
    {
        std::list<int> const &bucket(_buckets[hash(key) % _buckets.size()]);
        return std::find(bucket.cbegin(), bucket.cend(), key) != bucket.cend();
    }

private:
    static constexpr size_t InitSize = 8;
    static constexpr size_t BucketSize = 8;
    std::vector<std::list<int>> _buckets;

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
                int value = *iterator;
                const int currentKey = static_cast<int>(hash(value) % _buckets.size());
                if (currentKey != bucketKey)
                {
                    iterator = _buckets[index].erase(iterator);
                    _buckets[currentKey].push_back(value);
                }
                else
                    ++iterator;
            }
        }
    }

    [[nodiscard]] int hash(int value) const
    {
        return value;
    }
};

}

namespace DesignHashSetTask
{

TEST(DesignHashSetTaskTests, Examples)
{
    MyHashSet myHashSet;
    ASSERT_NO_THROW(myHashSet.add(1));
    ASSERT_NO_THROW(myHashSet.add(2));
    ASSERT_EQ(true, myHashSet.contains(1));
    ASSERT_EQ(false, myHashSet.contains(3));
    ASSERT_NO_THROW(myHashSet.add(2));
    ASSERT_EQ(true, myHashSet.contains(2));
    ASSERT_NO_THROW(myHashSet.remove(2));
    ASSERT_EQ(false, myHashSet.contains(2));
}

}