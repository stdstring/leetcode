#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int getWinner(std::vector<int> const &arr, int k) const
    {
        const size_t roundCount = k;
        if (roundCount >= arr.size())
            return *std::max_element(arr.cbegin(), arr.cend());
        size_t current = 0;
        size_t count = 0;
        for (size_t index = 1; index < arr.size(); ++index)
        {
            if (arr[current] > arr[index])
                ++count;
            else
            {
                current = index;
                count = 1;
            }
            if (count == roundCount)
                break;
        }
        return arr[current];
    }
};

}

namespace FindWinnerOfArrayGameTask
{

TEST(FindWinnerOfArrayGameTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.getWinner({2, 1, 3, 5, 4, 6, 7}, 2));
    ASSERT_EQ(3, solution.getWinner({3, 2, 1}, 10));
    ASSERT_EQ(9, solution.getWinner({1, 9, 8, 2, 3, 7, 6, 4, 5}, 7));
    ASSERT_EQ(99, solution.getWinner({1, 11, 22, 33, 44, 55, 66, 77, 88, 99}, 1000000000));
}


}
