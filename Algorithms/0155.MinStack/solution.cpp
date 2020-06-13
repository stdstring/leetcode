#include <stack>

#include "gtest/gtest.h"

namespace
{

class MinStack
{
public:
    MinStack() = default;

    void push(int x)
    {
        mElements.push(x);
        if (mElementsMin.empty() || x < mElementsMin.top())
            mElementsMin.push(x);
        else
            mElementsMin.push(mElementsMin.top());
    }

    void pop()
    {
        mElements.pop();
        mElementsMin.pop();
    }

    int top()
    {
        return mElements.top();
    }

    int getMin()
    {
        return mElementsMin.top();
    }

private:
    std::stack<int> mElements;
    std::stack<int> mElementsMin;
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