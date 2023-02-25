#include <stack>

#include "gtest/gtest.h"

namespace
{

class MyQueue
{
public:
    /* Initialize your data structure here. */
    MyQueue() = default;

    /* Push element x to the back of queue. */
    void push(int x)
    {
        std::stack<int> helper;
        shiftElements(_stack, helper);
        helper.push(x);
        shiftElements(helper, _stack);
    }

    /* Removes the element from in front of queue and returns that element. */
    int pop()
    {
        int value = _stack.top();
        _stack.pop();
        return value;
    }

    /* Get the front element. */
    int peek()
    {
        return _stack.top();
    }

    /* Returns whether the queue is empty. */
    bool empty() const
    {
        return _stack.empty();
    }

private:
    std::stack<int> _stack;

    void shiftElements(std::stack<int> &fromStack, std::stack<int> &toStack)
    {
        while (!fromStack.empty())
        {
            toStack.push(fromStack.top());
            fromStack.pop();
        }
    }
};

}

namespace ImplementQueueUsingStacksTask
{

TEST(ImplementQueueUsingStacksTaskTests, Examples)
{
    MyQueue myQueue;
    myQueue.push(1);
    myQueue.push(2);
    ASSERT_EQ(1, myQueue.peek());
    ASSERT_EQ(1, myQueue.pop());
    ASSERT_FALSE(myQueue.empty());
}

}