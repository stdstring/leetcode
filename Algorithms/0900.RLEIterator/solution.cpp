#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class RLEIterator
{
public:
    RLEIterator(std::vector<int> const &encoding) : _data(encoding), _index(0), _shift(0)
    {
    }

    int next(int n)
    {
        size_t nextCount = n;
        while ((_index < _data.size()) && (nextCount > 0))
        {
            size_t count = _data[_index] - _shift;
            if (count < nextCount)
            {
                nextCount -= count;
                _index += 2;
                _shift = 0;
            }
            else
            {
                _shift += std::min(count, nextCount);
                nextCount = 0;
            }
        }
        if (_index == _data.size())
            return -1;
        return _data[_index + 1];
    }

private:
    std::vector<int> _data;
    size_t _index;
    size_t _shift;
};

}

namespace RLEIteratorTask
{

TEST(RLEIteratorTaskTests, Examples)
{
    RLEIterator rleIterator({3, 8, 0, 9, 2, 5});
    ASSERT_EQ(8, rleIterator.next(2));
    ASSERT_EQ(8, rleIterator.next(1));
    ASSERT_EQ(5, rleIterator.next(1));
    ASSERT_EQ(-1, rleIterator.next(2));

}

}
