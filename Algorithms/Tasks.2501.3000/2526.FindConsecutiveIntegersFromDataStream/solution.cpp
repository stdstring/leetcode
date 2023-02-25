#include "gtest/gtest.h"

namespace
{

class DataStream
{
public:
    DataStream(int value, int k) : _value(value), _minSize(k), _currentSize(0)
    {
    }

    bool consec(int num)
    {
        if (num != _value)
            _currentSize = 0;
        else if (_currentSize < _minSize)
            ++_currentSize;
        return _currentSize == _minSize;
    }

private:
    int _value;
    size_t _minSize;
    size_t _currentSize;
};

}

namespace FindConsecutiveIntegersFromDataStreamTask
{

TEST(FindConsecutiveIntegersFromDataStreamTaskTests, Examples)
{
    DataStream stream(4, 3);
    ASSERT_EQ(false, stream.consec(4));
    ASSERT_EQ(false, stream.consec(4));
    ASSERT_EQ(true, stream.consec(4));
    ASSERT_EQ(false, stream.consec(3));
}

}