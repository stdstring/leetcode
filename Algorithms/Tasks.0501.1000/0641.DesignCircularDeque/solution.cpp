#include <vector>

#include "gtest/gtest.h"

namespace
{

class MyCircularDeque
{
public:
    MyCircularDeque(int k) : _storage(std::vector<int>(k, 0)), _currentSize(0), _frontPos(0), _rearPos(0)
    {
    }

    // Adds an item at the front of Deque. Return true if the operation is successful.
    bool insertFront(int value)
    {
        if (isFull())
            return false;
        if (!isEmpty())
            _frontPos = (_storage.size() + _frontPos - 1) % _storage.size();
        ++_currentSize;
        _storage[_frontPos] = value;
        return true;
    }

    // Adds an item at the rear of Deque. Return true if the operation is successful.
    bool insertLast(int value)
    {
        if (isFull())
            return false;
        if (!isEmpty())
            _rearPos = (_rearPos + 1) % _storage.size();
        ++_currentSize;
        _storage[_rearPos] = value;
        return true;
    }

    // Deletes an item from the front of Deque. Return true if the operation is successful.
    bool deleteFront()
    {
        if (isEmpty())
            return false;
        if (_currentSize > 1)
            _frontPos = (_frontPos + 1) % _storage.size();
        --_currentSize;
        return true;
    }

    // Deletes an item from the rear of Deque. Return true if the operation is successful.
    bool deleteLast()
    {
        if (isEmpty())
            return false;
        if (_currentSize > 1)
            _rearPos = (_storage.size() + _rearPos - 1) % _storage.size();
        --_currentSize;
        return true;
    }

    // Get the front item from the deque.
    int getFront()
    {
        return isEmpty() ? -1 : _storage[_frontPos];
    }

    // Get the last item from the deque.
    int getRear()
    {
        return isEmpty() ? -1 : _storage[_rearPos];
    }

    // Checks whether the circular deque is empty or not.
    bool isEmpty() const
    {
        return _currentSize == 0;
    }

    // Checks whether the circular deque is full or not.
    bool isFull() const
    {
        return _currentSize == _storage.size();
    }

private:
    std::vector<int> _storage;
    size_t _currentSize;
    size_t _frontPos;
    size_t _rearPos;
};

}

namespace DesignCircularDequeTask
{

TEST(DesignCircularDequeTaskTests, Examples)
{
    MyCircularDeque circularDeque(3);
    ASSERT_TRUE(circularDeque.insertLast(1));
    ASSERT_TRUE(circularDeque.insertLast(2));
    ASSERT_TRUE(circularDeque.insertFront(3));
    ASSERT_FALSE(circularDeque.insertFront(4));
    ASSERT_EQ(2, circularDeque.getRear());
    ASSERT_TRUE(circularDeque.isFull());
    ASSERT_TRUE(circularDeque.deleteLast());
    ASSERT_TRUE(circularDeque.insertFront(4));
    ASSERT_EQ(4, circularDeque.getFront());
}

TEST(DesignCircularDequeTaskTests, FromWrongAnswers)
{
    MyCircularDeque circularDeque(2);
    ASSERT_TRUE(circularDeque.insertFront(7));
    ASSERT_TRUE(circularDeque.deleteLast());
    ASSERT_EQ(-1, circularDeque.getFront());
    ASSERT_TRUE(circularDeque.insertLast(5));
    ASSERT_TRUE(circularDeque.insertFront(0));
    ASSERT_EQ(0, circularDeque.getFront());
    ASSERT_EQ(5, circularDeque.getRear());
    ASSERT_EQ(0, circularDeque.getFront());
    ASSERT_EQ(0, circularDeque.getFront());
    ASSERT_EQ(5, circularDeque.getRear());
    ASSERT_FALSE(circularDeque.insertLast(0));
}

}
