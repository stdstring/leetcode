#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class KthLargest
{
public:
    KthLargest(int k, std::vector<int> const &nums) : _numbers(nums.cbegin(), nums.cend()), _expextedSize(k)
    {
        while (!_numbers.empty() && (_numbers.size() > _expextedSize))
            removeLast();
    }

    int add(int val)
    {
        _numbers.insert(val);
        if (_numbers.size() > _expextedSize)
            removeLast();
        return *_numbers.rbegin();
    }

private:
    void removeLast()
    {
        auto lastNumber = _numbers.end();
        --lastNumber;
        _numbers.erase(lastNumber);
    }

    std::multiset<int, std::greater<int>> _numbers;
    size_t _expextedSize;
};

}

namespace
{

void checkKthLargest(int k, std::vector<int> const &nums, std::vector<int> const &values, std::vector<int> const &expected)
{
    KthLargest stream(k, nums);
    for (size_t index = 0; index < values.size(); ++index)
        ASSERT_EQ(expected[index], stream.add(values[index]));
}

}

namespace KthLargestElementInStreamTask
{

TEST(KthLargestElementInStreamTaskTests, Examples)
{
    checkKthLargest(3, {4, 5, 8, 2}, {3, 5, 10, 9, 4}, {4, 5, 5, 8, 8});
}

TEST(KthLargestElementInStreamTaskTests, FromWrongAnswers)
{
    checkKthLargest(1, {}, {-3, -2, -4, 0, 4}, {-3, -2, -2, 0, 4});
}

}