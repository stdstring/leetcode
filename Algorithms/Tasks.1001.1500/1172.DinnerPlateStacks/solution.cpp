#include <algorithm>
#include <set>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class DinnerPlates
{
public:
    explicit DinnerPlates(int capacity) : _capacity(capacity)
    {
        constexpr size_t maxCallCount = 200000;
        _stackStorage.reserve(maxCallCount);
    }

    void push(int val)
    {
        if (_availableForPush.empty())
        {
            size_t index = _stackStorage.size();
            _stackStorage.emplace_back(std::stack<int>({val}));
            if (_capacity > 1)
                _availableForPush.emplace(index);
            _availableForPop.emplace(index);
            return;
        }
        const auto indexIterator = _availableForPush.begin();
        _stackStorage[*indexIterator].push(val);
        _availableForPop.emplace(*indexIterator);
        if (_stackStorage[*indexIterator].size() == _capacity)
            _availableForPush.erase(indexIterator);
    }

    int pop()
    {
        if (_availableForPop.empty())
            return -1;
        const auto indexIterator = std::prev(_availableForPop.end(), 1);
        const int value = _stackStorage[*indexIterator].top();
        _stackStorage[*indexIterator].pop();
        _availableForPush.emplace(*indexIterator);
        if (_stackStorage[*indexIterator].empty())
            _availableForPop.erase(indexIterator);
        return value;
    }

    int popAtStack(int index)
    {
        if (static_cast<size_t>(index) >= _stackStorage.size())
            return -1;
        if (_stackStorage[index].empty())
            return -1;
        const int value = _stackStorage[index].top();
        _stackStorage[index].pop();
        _availableForPush.emplace(index);
        if (_stackStorage[index].empty())
            _availableForPop.erase(index);
        return value;
    }

private:
    size_t _capacity;
    std::vector<std::stack<int>> _stackStorage;
    std::set<size_t> _availableForPush;
    std::set<size_t> _availableForPop;
};

}

namespace DinnerPlateStacksTask
{

TEST(DinnerPlateStacksTaskTests, Examples)
{
    DinnerPlates dinnerPlates(2);
    ASSERT_NO_THROW(dinnerPlates.push(1));
    ASSERT_NO_THROW(dinnerPlates.push(2));
    ASSERT_NO_THROW(dinnerPlates.push(3));
    ASSERT_NO_THROW(dinnerPlates.push(4));
    ASSERT_NO_THROW(dinnerPlates.push(5));
    ASSERT_EQ(2, dinnerPlates.popAtStack(0));
    ASSERT_NO_THROW(dinnerPlates.push(20));
    ASSERT_NO_THROW(dinnerPlates.push(21));
    ASSERT_EQ(20, dinnerPlates.popAtStack(0));
    ASSERT_EQ(21, dinnerPlates.popAtStack(2));
    ASSERT_EQ(5, dinnerPlates.pop());
    ASSERT_EQ(4, dinnerPlates.pop());
    ASSERT_EQ(3, dinnerPlates.pop());
    ASSERT_EQ(1, dinnerPlates.pop());
    ASSERT_EQ(-1, dinnerPlates.pop());
}

}