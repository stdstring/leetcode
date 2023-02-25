#include <map>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class TimeMap
{
public:
    TimeMap() = default;

    void set(std::string const &key, std::string const &value, int timestamp)
    {
        auto iterator = _storage.find(key);
        if (iterator == _storage.end())
            iterator = _storage.emplace(key, std::map<int, std::string>()).first;
        iterator->second.emplace(timestamp, value);
    }

    std::string get(std::string const &key, int timestamp)
    {
        const auto outerIterator = _storage.find(key);
        if (outerIterator == _storage.cend())
            return "";
        auto innerIterator = outerIterator->second.upper_bound(timestamp);
        if (innerIterator == outerIterator->second.cbegin())
            return "";
        --innerIterator;
        return innerIterator->second;
    }

private:
    std::unordered_map<std::string, std::map<int, std::string>> _storage;
};

}

namespace TimeBasedKeyValueStoreTask
{

TEST(TimeBasedKeyValueStoreTaskTests, Examples)
{
    TimeMap timeMap;
    ASSERT_NO_THROW(timeMap.set("foo", "bar", 1));
    ASSERT_EQ("bar", timeMap.get("foo", 1));
    ASSERT_EQ("bar", timeMap.get("foo", 3));
    ASSERT_NO_THROW(timeMap.set("foo", "bar2", 4));
    ASSERT_EQ("bar2", timeMap.get("foo", 4));
    ASSERT_EQ("bar2", timeMap.get("foo", 5));
}

}