#include <algorithm>
#include <iterator>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> sortedSquares(std::vector<int> const &nums) const
    {
        std::vector<int> dest;
        dest.reserve(nums.size());
        const std::vector<int>::const_iterator zeroPoint = std::lower_bound(nums.cbegin(), nums.cend(), 0);
        std::vector<int>::const_iterator nonnegativeIterator = zeroPoint;
        std::vector<int>::const_iterator negativeIterator = zeroPoint == nums.cbegin() ? nums.cend() : zeroPoint - 1;
        while ((nonnegativeIterator != nums.cend()) && (negativeIterator != nums.cend()))
        {
            int negativeSquare = (*negativeIterator) * (*negativeIterator);
            int nonnegativeSquare = (*nonnegativeIterator) * (*nonnegativeIterator);
            if (negativeSquare < nonnegativeSquare)
            {
                dest.push_back(negativeSquare);
                moveToFront(nums, negativeIterator);
            }
            else
            {
                std::advance(nonnegativeIterator, 1);
                dest.push_back(nonnegativeSquare);
            }
        }
        while (negativeIterator != nums.cend())
        {
            int square = (*negativeIterator) * (*negativeIterator);
            dest.push_back(square);
            moveToFront(nums, negativeIterator);
        }
        while (nonnegativeIterator != nums.cend())
        {
            int square = (*nonnegativeIterator) * (*nonnegativeIterator);
            dest.push_back(square);
            std::advance(nonnegativeIterator, 1);
        }
        return dest;
    }

private:
    void moveToFront(std::vector<int> const &nums, std::vector<int>::const_iterator &iterator) const
    {
        if (iterator == nums.cbegin())
            iterator = nums.cend();
        else
            std::advance(iterator, -1);
    }
};

}

namespace SquaresOfSortedArrayTask
{

TEST(SquaresOfSortedArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 9, 16, 100}), solution.sortedSquares({-4, -1, 0, 3, 10}));
    ASSERT_EQ(std::vector<int>({4, 9, 9, 49, 121}), solution.sortedSquares({-7, -3, 2, 3, 11}));
}

}