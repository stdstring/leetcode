#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> findClosestElementsViaPriorityQueue(std::vector<int> const &arr, int k, int x) const
    {
        auto cmp = [x](int left, int right)
        {
            const int deltaLeft = std::abs(left - x);
            const int deltaRight = std::abs(right - x);
            return !((deltaLeft < deltaRight) || ((deltaLeft == deltaRight) && (left < right)));
        };
        std::priority_queue<int, std::vector<int>, decltype(cmp)> queue(cmp);
        for (int number : arr)
            queue.push(number);
        std::vector<int> result(k, 0);
        for (size_t index = 0; index < result.size(); ++index)
        {
            result[index] = queue.top();
            queue.pop();
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    [[nodiscard]] std::vector<int> findClosestElementsViaBinarySearch(std::vector<int> const &arr, int k, int x) const
    {
        if (x <= arr.front())
            return {arr.cbegin(), std::next(arr.cbegin(), k)};
        if (x >= arr.back())
            return {std::prev(arr.cend(), k), arr.cend()};
        auto [left, right] = binarySearch(arr, x);
        std::deque<int> result;
        if (left == right)
        {
            result.push_back(arr[left]);
            left = left == 0 ? arr.size() : left - 1;
            ++right;
        }
        while (result.size() < static_cast<size_t>(k))
        {
            const int deltaLeft = left == arr.size() ? 0 : x - arr[left];
            const int deltaRight = right == arr.size() ? 0 : arr[right] - x;
            if ((left == arr.size()) || ((right != arr.size()) && (deltaRight < deltaLeft)))
                result.push_back(arr[right++]);
            else
            {
                result.push_front(arr[left]);
                left = left == 0 ? arr.size() : left - 1;
            }
        }
        return {result.cbegin(), result.cend()};
    }

private:
    [[nodiscard]] std::pair<size_t, size_t> binarySearch(std::vector<int> const &arr, int value) const
    {
        size_t left = 0;
        size_t right = arr.size() - 1;
        while ((right - left) > 1)
        {
            size_t middle = (left + right) / 2;
            if (arr[middle] == value)
                return {middle, middle};
            if (arr[middle] < value)
                left = middle;
            else
                right = middle;
        }
        return {left, right};
    }
};

}

namespace
{

void checkFindClosestElements(std::vector<int> const &arr, int k, int x, std::vector<int> const &expected)
{
    constexpr Solution solution;
    ASSERT_EQ(expected, solution.findClosestElementsViaPriorityQueue(arr, k, x));
    ASSERT_EQ(expected, solution.findClosestElementsViaBinarySearch(arr, k, x));
}

}

namespace FindKClosestElementsTask
{

TEST(FindKClosestElementsTaskTests, Examples)
{
    checkFindClosestElements({1, 2, 3, 4, 5}, 4, 3, {1, 2, 3, 4});
    checkFindClosestElements({1, 2, 3, 4, 5}, 4, -1, {1, 2, 3, 4});
}

TEST(FindKClosestElementsTaskTests, FromWrongAnswers)
{
    checkFindClosestElements({-2, -1, 1, 2, 3, 4, 5}, 7, 3, {-2, -1, 1, 2, 3, 4, 5});
}

}