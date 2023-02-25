#include <algorithm>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class RandomizedCollection
{
public:
    RandomizedCollection() : _generator(std::random_device()())
    {
    }

    bool insert(int val)
    {
        const bool isUnique = _numberIndexMap.count(val) == 0;
        _numbers.emplace_back(val);
        _numberIndexMap[val].insert(_numbers.size() - 1);
        return isUnique;
    }

    bool remove(int val)
    {
        const auto valueIterator = _numberIndexMap.find(val);
        if (valueIterator == _numberIndexMap.end())
            return false;
        const size_t valueIndex = *valueIterator->second.begin();
        valueIterator->second.erase(valueIndex);
        if (valueIterator->second.empty())
            _numberIndexMap.erase(valueIterator);
        if (valueIndex < (_numbers.size() - 1))
        {
            const int lastValue = _numbers.back();
            const size_t lastIndex = _numbers.size() - 1;
            const auto lastValueIterator = _numberIndexMap.find(lastValue);
            lastValueIterator->second.erase(lastIndex);
            lastValueIterator->second.insert(valueIndex);
            _numbers[valueIndex] = lastValue;
        }
        _numbers.pop_back();
        return true;
    }

    int getRandom()
    {
        std::uniform_int_distribution<> distribution(0, static_cast<int>(_numbers.size()) - 1);
        return _numbers[distribution(_generator)];
    }

private:
    std::mt19937 _generator;
    std::unordered_map<int, std::unordered_set<size_t>> _numberIndexMap;
    std::vector<int> _numbers;
};

}

namespace
{

bool contains(std::vector<int> const &sourceValues, int value)
{
    return std::find(sourceValues.cbegin(), sourceValues.cend(), value) != sourceValues.cend();
}

}

namespace InsertDeleteGetRandomO1DuplicatesTask
{

TEST(InsertDeleteGetRandomO1DuplicatesTaskTests, Examples)
{
    // TODO (std_string) : think about check for uniform distribution
    RandomizedCollection randomizedCollection;
    ASSERT_EQ(true, randomizedCollection.insert(1));
    ASSERT_EQ(false, randomizedCollection.insert(1));
    ASSERT_EQ(true, randomizedCollection.insert(2));
    ASSERT_TRUE(contains({1, 2}, randomizedCollection.getRandom()));
    ASSERT_EQ(true, randomizedCollection.remove(1));
    ASSERT_TRUE(contains({1, 2}, randomizedCollection.getRandom()));
}

}
