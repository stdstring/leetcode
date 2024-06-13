#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minMovesToSeat(std::vector<int> const &seats, std::vector<int> const &students) const
    {
        std::vector<int> sortedSeats(seats);
        std::vector<int> sortedStudents(students);
        std::ranges::sort(sortedSeats);
        std::ranges::sort(sortedStudents);
        int moves = 0;
        for (size_t index = 0; index < sortedSeats.size(); ++index)
            moves += std::abs(sortedSeats[index] - sortedStudents[index]);
        return moves;
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minMovesToSeat({3, 1, 5}, {2, 7, 4}));
    ASSERT_EQ(7, solution.minMovesToSeat({4, 1, 5, 9}, {1, 3, 2, 6}));
    ASSERT_EQ(4, solution.minMovesToSeat({2, 2, 6, 6}, {1, 3, 2, 6}));
}

}