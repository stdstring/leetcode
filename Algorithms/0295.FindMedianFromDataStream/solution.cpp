#include <queue>

#include "gtest/gtest.h"

namespace
{

class MedianFinder
{
public:
    MedianFinder() = default;

    void addNum(int num)
    {
        if (_lessMedian.empty())
        {
            _lessMedian.push(num);
            return;
        }
        if (num <= _lessMedian.top())
            _lessMedian.push(num);
        else
            _greaterMedian.push(num);
        if (_lessMedian.size() < _greaterMedian.size())
         {
            _lessMedian.push(_greaterMedian.top());
            _greaterMedian.pop();
        }
        if ((_lessMedian.size() - _greaterMedian.size()) == 2)
        {
            _greaterMedian.push(_lessMedian.top());
            _lessMedian.pop();
        }
    }

    double findMedian() const
    {
        return _lessMedian.size() == _greaterMedian.size() ? (_lessMedian.top() + _greaterMedian.top()) / 2.0 : _lessMedian.top();
    }

private:
    std::priority_queue<int> _lessMedian;
    std::priority_queue<int, std::vector<int>, std::greater<>> _greaterMedian;
};

}

namespace FindMedianFromDataStreamTask
{

TEST(FindMedianFromDataStreamTaskTests, Examples)
{
    MedianFinder medianFinder;
    ASSERT_NO_THROW(medianFinder.addNum(1));
    ASSERT_NO_THROW(medianFinder.addNum(2));
    ASSERT_DOUBLE_EQ(1.50000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(3));
    ASSERT_DOUBLE_EQ(2.00000, medianFinder.findMedian());
}

TEST(FindMedianFromDataStreamTaskTests, FromWrongAnswers)
{
    MedianFinder medianFinder;
    ASSERT_NO_THROW(medianFinder.addNum(6));
    ASSERT_DOUBLE_EQ(6.00000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(10));
    ASSERT_DOUBLE_EQ(8.00000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(2));
    ASSERT_DOUBLE_EQ(6.00000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(6));
    ASSERT_DOUBLE_EQ(6.00000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(5));
    ASSERT_DOUBLE_EQ(6.00000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(0));
    ASSERT_DOUBLE_EQ(5.50000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(6));
    ASSERT_DOUBLE_EQ(6.00000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(3));
    ASSERT_DOUBLE_EQ(5.50000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(1));
    ASSERT_DOUBLE_EQ(5.00000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(0));
    ASSERT_DOUBLE_EQ(4.00000, medianFinder.findMedian());
    ASSERT_NO_THROW(medianFinder.addNum(0));
    ASSERT_DOUBLE_EQ(3.00000, medianFinder.findMedian());
}

}