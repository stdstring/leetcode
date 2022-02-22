#include <list>

#include "gtest/gtest.h"

namespace
{

class FrontMiddleBackQueue
{
public:
    FrontMiddleBackQueue()
    {
    }

    void pushFront(int val)
    {
        _firstHalf.push_front(val);
        balance();
    }

    void pushMiddle(int val)
    {
        _secondHalf.push_front(val);
        balance();
    }

    void pushBack(int val)
    {
        _secondHalf.push_back(val);
        balance();
    }

    int popFront()
    {
        if (empty())
            return -1;
        const int value = _firstHalf.empty() ? _secondHalf.front() : _firstHalf.front();
        _firstHalf.empty() ? _secondHalf.pop_front() : _firstHalf.pop_front();
        balance();
        return value;
    }

    int popMiddle()
    {
        if (empty())
            return -1;
        const int value = _firstHalf.size() == _secondHalf.size() ? _firstHalf.back() : _secondHalf.front();
        _firstHalf.size() == _secondHalf.size() ? _firstHalf.pop_back() : _secondHalf.pop_front();
        balance();
        return value;
    }

    int popBack()
    {
        if (empty())
            return -1;
        const int value = _secondHalf.back();
        _secondHalf.pop_back();
        balance();
        return value;
    }

private:
    std::list<int> _firstHalf;
    std::list<int> _secondHalf;

    void balance()
    {
        if (_firstHalf.size() > _secondHalf.size())
        {
            _secondHalf.push_front(_firstHalf.back());
            _firstHalf.pop_back();
        }
        if ((_firstHalf.size() + 2) == _secondHalf.size())
        {
            _firstHalf.push_back(_secondHalf.front());
            _secondHalf.pop_front();
        }
    }

    bool empty()
    {
        return _firstHalf.empty() && _secondHalf.empty();
    }
};

}

namespace DesignFrontMiddleBackQueueTask
{

TEST(DesignFrontMiddleBackQueueTaskTests, Examples)
{
    FrontMiddleBackQueue queue;
    ASSERT_NO_THROW(queue.pushFront(1));
    ASSERT_NO_THROW(queue.pushBack(2));
    ASSERT_NO_THROW(queue.pushMiddle(3));
    ASSERT_NO_THROW(queue.pushMiddle(4));
    ASSERT_EQ(1, queue.popFront());
    ASSERT_EQ(3, queue.popMiddle());
    ASSERT_EQ(4, queue.popMiddle());
    ASSERT_EQ(2, queue.popBack());
    ASSERT_EQ(-1, queue.popFront());
}

}