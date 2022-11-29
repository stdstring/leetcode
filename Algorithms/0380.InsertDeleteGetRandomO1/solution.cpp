#include <random>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class RandomizedSet
{
public:
    RandomizedSet() : _generator(std::random_device()())
    {
    }

    bool insert(int val)
    {
        if (_numberIndexMap.count(val) > 0)
            return false;
        _numbers.emplace_back(val);
        _numberIndexMap.emplace(val, _numbers.size() - 1);
        return true;
    }

    bool remove(int val)
    {
        const auto iterator = _numberIndexMap.find(val);
        if (iterator == _numberIndexMap.cend())
            return false;
        const size_t index = iterator->second;
        if (index < (_numbers.size() - 1))
        {
            _numbers[index] = _numbers.back();
            _numberIndexMap[_numbers.back()] = index;
        }
        _numbers.pop_back();
        _numberIndexMap.erase(iterator);
        return true;
    }

    int getRandom()
    {
        std::uniform_int_distribution<> distribution(0, static_cast<int>(_numbers.size() - 1));
        return _numbers[distribution(_generator)];
    }

private:
    std::mt19937 _generator;
    std::unordered_map<int, size_t> _numberIndexMap;
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

namespace InsertDeleteGetRandomO1Task
{

TEST(InsertDeleteGetRandomO1TaskTests, Examples)
{
    // TODO (std_string) : think about check for uniform distribution
    RandomizedSet randomizedSet;
    ASSERT_EQ(true, randomizedSet.insert(1));
    ASSERT_EQ(false, randomizedSet.remove(2));
    ASSERT_EQ(true, randomizedSet.insert(2));
    ASSERT_TRUE(contains({1, 2}, randomizedSet.getRandom()));
    ASSERT_EQ(true, randomizedSet.remove(1));
    ASSERT_EQ(false, randomizedSet.insert(2));
    ASSERT_TRUE(contains({2}, randomizedSet.getRandom()));
}

}