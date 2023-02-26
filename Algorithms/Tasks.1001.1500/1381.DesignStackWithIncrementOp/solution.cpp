#include <vector>

#include "gtest/gtest.h"

namespace
{

class CustomStack
{
public:
    CustomStack(int maxSize) : _maxSize(maxSize)
    {
    }

    void push(int x)
    {
        if (_storage.size() < _maxSize)
            _storage.push_back(x);
    }

    int pop()
    {
        if (_storage.empty())
            return -1;
        const int top = _storage.back();
        _storage.pop_back();
        return top;
    }

    void increment(int k, int val)
    {
        const size_t updateSize = k;
        for (size_t index = 0; index < std::min(updateSize, _storage.size()); ++index)
            _storage[index] += val;
    }

private:
    size_t _maxSize;
    std::vector<int> _storage;
};

}

namespace DesignStackWithIncrementOpTask
{

TEST(DesignStackWithIncrementOpTaskTests, Examples)
{
    CustomStack customStack(3);
    ASSERT_NO_THROW(customStack.push(1));
    ASSERT_NO_THROW(customStack.push(2));
    ASSERT_EQ(2, customStack.pop());
    ASSERT_NO_THROW(customStack.push(2));
    ASSERT_NO_THROW(customStack.push(3));
    ASSERT_NO_THROW(customStack.push(4));
    ASSERT_NO_THROW(customStack.increment(5, 100));
    ASSERT_NO_THROW(customStack.increment(2, 100));
    ASSERT_EQ(103, customStack.pop());
    ASSERT_EQ(202, customStack.pop());
    ASSERT_EQ(201, customStack.pop());
    ASSERT_EQ(-1, customStack.pop());
}

}