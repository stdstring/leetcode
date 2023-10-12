#include <algorithm>
#include <stdexcept>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class MountainArray
{
public:
    MountainArray(std::vector<int> const &data) : _data(data)
    {
    }

    int get(int index) const
    {
        if (_getCallCount == MaxGetCallCount)
            throw std::logic_error("Too much MountainArray::get call count");
        ++_getCallCount;
        return _data[index];
    }

    int length() const
    {
        return static_cast<int>(_data.size());
    }

private:
    std::vector<int> _data;
    mutable int _getCallCount = 0;
    static constexpr  int MaxGetCallCount = 100;
};

class MountainArrayProxy
{
public:
    explicit MountainArrayProxy(MountainArray const& source) : _source(source), _cache(source.length(), -1)
    {
    }

    int get(int index) const
    {
        if (_cache[index] == -1)
            _cache[index] = _source.get(index);
        return _cache[index];
    }

    int length() const
    {
        return _source.length();
    }

private:
    MountainArray const &_source;
    mutable std::vector<int> _cache;
};

class Solution
{
public:
    [[nodiscard]] int findInMountainArray(int target, MountainArray const &mountainArr) const
    {
        const MountainArrayProxy mountainArrProxy(mountainArr);
        const int leftValue = mountainArrProxy.get(0);
        const int rightValue = mountainArrProxy.get(mountainArrProxy.length() - 1);
        if (leftValue == target)
            return 0;
        if ((target < leftValue) && (target < rightValue))
            return -1;
        const int peak = findPeak(mountainArrProxy);
        const int peakValue = mountainArrProxy.get(peak);
        if (target == peakValue)
            return peak;
        if ((leftValue < target) && (target < peakValue))
        {
            const int targetIndex = findTarget(target, mountainArrProxy, 0, peak, true);
            if (targetIndex != -1)
                return targetIndex;
        }
        if (rightValue == target)
            return mountainArrProxy.length() - 1;
        if ((rightValue < target) && (target < peakValue))
            return findTarget(target, mountainArrProxy, peak, mountainArrProxy.length() - 1, false);
        return -1;
    }

private:
    [[nodiscard]] int findPeak(MountainArrayProxy const &mountainArr) const
    {
        int left = 0;
        int right = mountainArr.length() - 1;
        while ((right - left) > 1)
        {
            const int middle = (left + right) / 2;
            const int middleValue = mountainArr.get(middle);
            const int prevMiddleValue = mountainArr.get(middle - 1);
            ((prevMiddleValue < middleValue) ? left : right) = middle;
        }
        return left;
    }

    [[nodiscard]] int findTarget(int target, MountainArrayProxy const &mountainArr, int left, int right, bool increasing) const
    {
        while ((right - left) > 1)
        {
            const int middle = (left + right) / 2;
            const int middleValue = mountainArr.get(middle);
            if (middleValue == target)
                return middle;
            if (middleValue < target)
                (increasing ? left : right) = middle;
            else
                (increasing ? right : left) = middle;
        }
        return -1;
    }
};

}

namespace FindInMountainArrayTask
{

TEST(FindInMountainArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findInMountainArray(3, MountainArray({1, 2, 3, 4, 5, 3, 1})));
    ASSERT_EQ(-1, solution.findInMountainArray(3, MountainArray({0, 1, 2, 4, 2, 1})));
}

TEST(FindInMountainArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findInMountainArray(2, MountainArray({1, 5, 2})));
    ASSERT_EQ(3, solution.findInMountainArray(2, MountainArray({3, 5, 3, 2, 0})));
}

}