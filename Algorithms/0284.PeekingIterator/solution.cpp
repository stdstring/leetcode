#include <vector>

#include "gtest/gtest.h"

namespace
{

class Iterator
{
public:
    Iterator(std::vector<int> const &nums) : _numbers(nums), _nextPos(0)
    {
    }

    virtual ~Iterator() = default;

    // Returns the next element in the iteration.
    virtual int next()
    {
        return _numbers.at(_nextPos++);
    }

    // Returns true if the iteration has more elements.
    virtual bool hasNext() const
    {
        return _nextPos < _numbers.size();
    }

private:
    std::vector<int> _numbers;
    size_t _nextPos;
 };

class PeekingIterator : public Iterator
{
public:
    PeekingIterator(std::vector<int> const &nums) : Iterator(nums), _hasPeekValue(false), _peekValue(0)
    {
        // Initialize any member here.
        // **DO NOT** save a copy of nums and manipulate it directly.
        // You should only use the Iterator interface methods.
    }

    // Returns the next element in the iteration without advancing the iterator.
    int peek()
    {
        if (!_hasPeekValue)
        {
            _hasPeekValue = true;
            _peekValue = Iterator::next();
        }
        return _peekValue;
    }

    // Returns the next element in the iteration.
    int next() override
    {
        if (_hasPeekValue)
        {
            _hasPeekValue = false;
            return _peekValue;
        }
        return Iterator::next();
    }

    // Returns true if the iteration has more elements.
    bool hasNext() const override
    {
        return _hasPeekValue ? true : Iterator::hasNext();
    }

private:
    bool _hasPeekValue;
    int _peekValue;
};

}

namespace PeekingIteratorTask
{

TEST(TwoSumTaskTests, Examples)
{
    PeekingIterator iterator({1, 2, 3});
    ASSERT_EQ(1, iterator.next());
    ASSERT_EQ(2, iterator.peek());
    ASSERT_EQ(2, iterator.next());
    ASSERT_EQ(3, iterator.next());
    ASSERT_FALSE(iterator.hasNext());
}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    PeekingIterator iterator({1, 2, 3, 4});
    ASSERT_TRUE(iterator.hasNext());
    ASSERT_EQ(1, iterator.peek());
    ASSERT_EQ(1, iterator.peek());
    ASSERT_EQ(1, iterator.next());
    ASSERT_EQ(2, iterator.next());
    ASSERT_EQ(3, iterator.peek());
    ASSERT_EQ(3, iterator.peek());
    ASSERT_EQ(3, iterator.next());
    ASSERT_TRUE(iterator.hasNext());
    ASSERT_EQ(4, iterator.peek());
    ASSERT_TRUE(iterator.hasNext());
    ASSERT_EQ(4, iterator.next());
    ASSERT_FALSE(iterator.hasNext());
}

}