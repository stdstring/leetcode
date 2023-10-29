#include <map>
#include <set>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class AllOne
{
public:
    AllOne() = default;

    void inc(std::string const &key)
    {
        const auto keyIterator = _keyMap.find(key);
        if (keyIterator == _keyMap.end())
        {
            _keyMap.emplace(key, 1);
            _countMap[1].emplace(key);
            return;
        }
        const auto countIterator = _countMap.find(keyIterator->second);
        eraseKeyFromCountMap(countIterator, key);
        ++keyIterator->second;
        _countMap[keyIterator->second].emplace(key);
    }

    void dec(std::string const &key)
    {
        const auto keyIterator = _keyMap.find(key);
        const auto countIterator = _countMap.find(keyIterator->second);
        eraseKeyFromCountMap(countIterator, key);
        --keyIterator->second;
        if (keyIterator->second == 0)
            _keyMap.erase(keyIterator);
        else
            _countMap[keyIterator->second].emplace(key);
    }

    std::string getMaxKey() const
    {
        if (_countMap.empty())
            return "";
        return *_countMap.crbegin()->second.cbegin();
    }

    std::string getMinKey() const
    {
        if (_countMap.empty())
            return "";
        return *_countMap.cbegin()->second.cbegin();
    }

private:
    std::unordered_map<std::string, int> _keyMap;
    std::map<int, std::set<std::string>> _countMap;

    void eraseKeyFromCountMap(std::map<int, std::set<std::string>>::iterator const &iterator, std::string const &key)
    {
        iterator->second.erase(key);
        if (iterator->second.empty())
            _countMap.erase(iterator);
    }
};

}

namespace AllOneDataStructureTask
{

TEST(AllOneDataStructureTaskTests, Examples)
{
    AllOne allOne;
    ASSERT_NO_THROW(allOne.inc("hello"));
    ASSERT_NO_THROW(allOne.inc("hello"));
    ASSERT_EQ("hello", allOne.getMaxKey());
    ASSERT_EQ("hello", allOne.getMinKey());
    ASSERT_NO_THROW(allOne.inc("leet"));
    ASSERT_EQ("hello", allOne.getMaxKey());
    ASSERT_EQ("leet", allOne.getMinKey());
    ASSERT_NO_THROW(allOne.dec("leet"));
    ASSERT_EQ("hello", allOne.getMaxKey());
    ASSERT_EQ("hello", allOne.getMinKey());
}

}