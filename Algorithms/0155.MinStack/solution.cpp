#include <stack>

#include "gtest/gtest.h"

namespace
{

struct Item
{
    Item(int val, int minVal) : value(val), minValue(minVal)
    {
    }

    int value;
    int minValue;
};

class MinStack
{
public:
    MinStack() = default;

    void push(int x)
    {
        int minValue = mData.empty() || x < mData.top().minValue ? x : mData.top().minValue;
        mData.emplace(x, minValue);
    }

    void pop()
    {
        mData.pop();
    }

    int top()
    {
        return mData.top().value;
    }

    int getMin()
    {
        return mData.top().minValue;
    }

private:
    std::stack<Item> mData;
};

}


namespace MinStackTask
{

TEST(MinStackTaskTests, Examples)
{
    MinStack minStack;
    ASSERT_NO_THROW(minStack.push(-2));
    ASSERT_NO_THROW(minStack.push(0));
    ASSERT_NO_THROW(minStack.push(-3));
    ASSERT_EQ(-3, minStack.getMin());
    ASSERT_NO_THROW(minStack.pop());
    ASSERT_EQ(0, minStack.top());
    ASSERT_EQ(-2, minStack.getMin());
}

}