#include <queue>

#include "gtest/gtest.h"

namespace
{

class MyStack
{
public:
    /* Initialize your data structure here. */
    MyStack() = default;

    /* Push element x onto stack. */
    void push(int x)
    {
        _queue.push(x);
        for (size_t op = _queue.size(); op > 1; --op)
        {
            _queue.push(_queue.front());
            _queue.pop();
        }
    }

    /* Removes the element on top of the stack and returns that element. */
    int pop()
    {
        const int value = top();
        _queue.pop();
        return value;
    }

    /* Get the top element. */
    int top()
    {
        return _queue.front();
    }

    /* Returns whether the stack is empty. */
    bool empty() const
    {
        return _queue.empty();
    }

private:
    std::queue<int> _queue;
};

}


namespace ImplementStackUsingQueuesTask
{

TEST(ImplementStackUsingQueuesTaskTests, Examples)
{
    MyStack myStack;
    myStack.push(1);
    myStack.push(2);
    ASSERT_EQ(2, myStack.top());
    ASSERT_EQ(2, myStack.pop());
    ASSERT_FALSE(myStack.empty());
}

}