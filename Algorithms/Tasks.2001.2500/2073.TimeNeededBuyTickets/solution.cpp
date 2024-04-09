#include <queue>
#include <vector>
#include <utility>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int timeRequiredToBuy(std::vector<int> const &tickets, int k) const
    {
        const size_t selectedPerson = k;
        std::queue<std::pair<size_t, int>> persons;
        for (size_t index = 0; index < tickets.size(); ++index)
            persons.emplace(index, tickets[index]);
        int requiredTime = 0;
        while (persons.size() > 1)
        {
            ++requiredTime;
            auto [currentPerson, currentTickets] = persons.front();
            persons.pop();
            if (currentTickets > 1)
                persons.emplace(currentPerson, currentTickets - 1);
            else if (currentPerson == selectedPerson)
                return requiredTime;
        }
        return requiredTime + persons.front().second;
    }
};

}

namespace TimeNeededBuyTicketsTask
{

TEST(TimeNeededBuyTicketsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.timeRequiredToBuy({2, 3, 2}, 2));
    ASSERT_EQ(8, solution.timeRequiredToBuy({5, 1, 1, 1}, 0));
}

}