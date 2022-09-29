#include <set>

#include "gtest/gtest.h"

namespace
{

class SmallestInfiniteSet
{
public:
    SmallestInfiniteSet() = default;

    int popSmallest()
    {
        if (!_beforeBorderNumbers.empty())
        {
            const int smallestNumber = *_beforeBorderNumbers.cbegin();
            _beforeBorderNumbers.erase(smallestNumber);
            return smallestNumber;
        }
        return _bottomBorder++;
    }

    void addBack(int num)
    {
        if (num >= _bottomBorder)
            return;
        if (_beforeBorderNumbers.count(num) != 0)
            return;
        _beforeBorderNumbers.emplace(num);
    }

private:
    int _bottomBorder = 1;
    std::set<int> _beforeBorderNumbers;
};

}

namespace SmallestNumberInInfiniteSetTask
{

TEST(SmallestNumberInInfiniteSetTaskTests, Examples)
{
    SmallestInfiniteSet set;
    ASSERT_NO_THROW(set.addBack(2));
    ASSERT_EQ(1, set.popSmallest());
    ASSERT_EQ(2, set.popSmallest());
    ASSERT_EQ(3, set.popSmallest());
    ASSERT_NO_THROW(set.addBack(1));
    ASSERT_EQ(1, set.popSmallest());
    ASSERT_EQ(4, set.popSmallest());
    ASSERT_EQ(5, set.popSmallest());
}

}