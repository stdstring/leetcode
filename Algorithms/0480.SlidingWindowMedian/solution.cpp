#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution {
public:
    [[nodiscard]] std::vector<double> medianSlidingWindow(std::vector<int> const &nums, int k) const
    {
        std::vector<int> initWindow(nums.cbegin(), nums.cbegin() + k);
        std::sort(initWindow.begin(), initWindow.end());
        std::multiset<int> leftRange(initWindow.begin(), initWindow.begin() + k / 2);
        std::multiset<int> rightRange(initWindow.begin() + k / 2, initWindow.end());
        std::vector<double> medians;
        medians.push_back(calcMedian(leftRange, rightRange));
        for(size_t index = k; index < nums.size(); ++index)
        {
            const int numberForRemove = nums[index - k];
            removeNumber(leftRange, rightRange, numberForRemove);
            const int numberForAdd = nums[index];
            addNumber(leftRange, rightRange, numberForAdd);
            balanceRanges(leftRange, rightRange);
            medians.push_back(calcMedian(leftRange, rightRange));
        }
        return medians;
    }

private:
    [[nodiscard]] double calcMedian(std::multiset<int> const &leftRange, std::multiset<int> const &rightRange) const
    {
        return leftRange.size() == rightRange.size() ? (static_cast<double>(*leftRange.crbegin()) + static_cast<double>(*rightRange.cbegin())) / 2 : static_cast<double>(*rightRange.cbegin());
    }

    void removeNumber(std::multiset<int> &leftRange, std::multiset<int> &rightRange, int number) const
    {
        if (number >= *rightRange.cbegin())
            rightRange.erase(rightRange.find(number));
        else
            leftRange.erase(leftRange.find(number));
    }

    void addNumber(std::multiset<int> &leftRange, std::multiset<int> &rightRange, int number) const
    {
        if (!rightRange.empty() && number >= *rightRange.cbegin())
            rightRange.insert(number);
        else
            leftRange.insert(number);
    }

    void balanceRanges(std::multiset<int> &leftRange, std::multiset<int> &rightRange) const
    {
        if (leftRange.size() > rightRange.size())
        {
            rightRange.insert(*leftRange.crbegin());
            auto iterator = leftRange.cend();
            --iterator;
            leftRange.erase(iterator);
        }
        if ((leftRange.size() + 1) < rightRange.size())
        {
            leftRange.insert(*rightRange.cbegin());
            rightRange.erase(rightRange.cbegin());
        }
    }
};

}

namespace SlidingWindowMedianTask
{

TEST(SlidingWindowMedianTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector({1.0, -1.0, -1.0, 3.0, 5.0, 6.0}), solution.medianSlidingWindow({1, 3, -1, -3, 5, 3, 6, 7}, 3));
    ASSERT_EQ(std::vector({2.0, 3.0, 3.0, 3.0, 2.0, 3.0, 2.0}), solution.medianSlidingWindow({1, 2, 3, 4, 2, 3, 1, 4, 2}, 3));
}

}