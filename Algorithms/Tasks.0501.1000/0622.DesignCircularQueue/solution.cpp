#include <vector>

#include "gtest/gtest.h"

namespace
{

class MyCircularQueue
{
public:
    /* Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) : _data(std::vector<int>(k, 0)), _start(0), _size(0)
    {
    }

    /* Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value)
    {
        if (isFull())
            return false;
        ++_size;
        _data[(_start + _size - 1) % _data.size()] = value;
        return true;
    }

    /* Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue()
    {
        if (isEmpty())
            return false;
        _start = (_start + 1) % _data.size();
        --_size;
        return true;
    }

    /* Get the front item from the queue. */
    int Front()
    {
        return isEmpty() ? -1 : _data[_start];
    }

    /* Get the last item from the queue. */
    int Rear()
    {
        return isEmpty() ? -1 : _data[(_start + _size - 1) % _data.size()];
    }

    /* Checks whether the circular queue is empty or not. */
    bool isEmpty() const
    {
        return _size == 0;
    }

    /* Checks whether the circular queue is full or not. */
    bool isFull() const
    {
        return _size == _data.size();
    }

private:
    std::vector<int> _data;
    size_t _start;
    size_t _size;
};

}

namespace DesignCircularQueueTask
{

TEST(DesignCircularQueueTaskTests, Examples)
{
    MyCircularQueue circularQueue(3);
    ASSERT_TRUE(circularQueue.enQueue(1));
    ASSERT_TRUE(circularQueue.enQueue(2));
    ASSERT_TRUE(circularQueue.enQueue(3));
    ASSERT_FALSE(circularQueue.enQueue(4));
    ASSERT_EQ(3, circularQueue.Rear());
    ASSERT_TRUE(circularQueue.isFull());
    ASSERT_TRUE(circularQueue.deQueue());
    ASSERT_TRUE(circularQueue.enQueue(4));
    ASSERT_EQ(4, circularQueue.Rear());
}

TEST(DesignCircularQueueTaskTests, FromWrongAnswers)
{
    MyCircularQueue circularQueue(6);
    ASSERT_TRUE(circularQueue.enQueue(6));
    ASSERT_EQ(6, circularQueue.Rear());
    ASSERT_EQ(6, circularQueue.Rear());
    ASSERT_TRUE(circularQueue.deQueue());
    ASSERT_TRUE(circularQueue.enQueue(5));
    ASSERT_EQ(5, circularQueue.Rear());
    ASSERT_TRUE(circularQueue.deQueue());
    ASSERT_EQ(-1, circularQueue.Front());
    ASSERT_FALSE(circularQueue.deQueue());
    ASSERT_FALSE(circularQueue.deQueue());
    ASSERT_FALSE(circularQueue.deQueue());
}

}