#include <queue>

#include "gtest/gtest.h"

namespace
{

class SeatManager
{
public:
    SeatManager(int n)
    {
        for (int number = 1; number <= n; ++number)
            _unreservedSeats.push(number);
    }

    int reserve()
    {
        const int seat = _unreservedSeats.top();
        _unreservedSeats.pop();
        return seat;
    }

    void unreserve(int seatNumber)
    {
        _unreservedSeats.push(seatNumber);
    }

private:
    std::priority_queue<int, std::vector<int>, std::greater<int>> _unreservedSeats;
};

}

namespace SeatReservationManagerTask
{

TEST(SeatReservationManagerTaskTests, Examples)
{
    SeatManager seatManager(5);
    ASSERT_EQ(1, seatManager.reserve());
    ASSERT_EQ(2, seatManager.reserve());
    ASSERT_NO_THROW(seatManager.unreserve(2));
    ASSERT_EQ(2, seatManager.reserve());
    ASSERT_EQ(3, seatManager.reserve());
    ASSERT_EQ(4, seatManager.reserve());
    ASSERT_EQ(5, seatManager.reserve());
    ASSERT_NO_THROW(seatManager.unreserve(5));
    ASSERT_EQ(5, seatManager.reserve());
}

}