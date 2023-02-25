#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getNumberOfBacklogOrders(std::vector<std::vector<int>> const &orders) const
    {
        auto buyCmp = [](Order const &left, Order const &right) { return left.Price < right.Price; };
        auto sellCmp = [](Order const &left, Order const &right) { return left.Price > right.Price; };
        std::priority_queue<Order, std::vector<Order>, std::function<bool(Order const&, Order const&)>> buyQueue(buyCmp);
        std::priority_queue<Order, std::vector<Order>, std::function<bool(Order const&, Order const&)>> sellQueue(sellCmp);
        for (std::vector<int> const &order : orders)
        {
            const int price = order[0];
            int amount = order[1];
            const int type = order[2];
            switch (type)
            {
                case 0:
                    while ((amount > 0) && !sellQueue.empty() && (sellQueue.top().Price <= price))
                        amount = updateQueue(sellQueue, amount);
                    if (amount > 0)
                        buyQueue.emplace(price, amount);
                    break;
                case 1:
                    while ((amount > 0) && !buyQueue.empty() && (buyQueue.top().Price >= price))
                        amount = updateQueue(buyQueue, amount);
                    if (amount > 0)
                        sellQueue.emplace(price, amount);
                    break;
                default:
                    throw std::logic_error("Bad order type");
            }
        }
        uint64_t result = 0;
        result += calcOrdersInQueue(buyQueue);
        result += calcOrdersInQueue(sellQueue);
        return static_cast<int>(result % 1000000007);
    }

private:
    struct Order
    {
        Order(int price, int amount) : Price(price), Amount(amount)
        {
        }

        int Price;
        int Amount;
    };

    int updateQueue(std::priority_queue<Order, std::vector<Order>, std::function<bool(Order const&, Order const&)>> &queue, int amount) const
    {
        if (queue.top().Amount <= amount)
        {
            amount -= queue.top().Amount;
            queue.pop();
        }
        else
        {
            int topItemPrice = queue.top().Price;
            int topItemAmount = queue.top().Amount - amount;
            queue.pop();
            queue.emplace(topItemPrice, topItemAmount);
            amount = 0;
        }
        return amount;
    }

    uint64_t calcOrdersInQueue(std::priority_queue<Order, std::vector<Order>, std::function<bool(Order const&, Order const&)>> &queue) const
    {
        uint64_t result = 0;
        while (!queue.empty())
        {
            result += queue.top().Amount;
            queue.pop();
        }
        return result;
    }
};

}

namespace NumberOfOrdersInBacklogTask
{

TEST(NumberOfOrdersInBacklogTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.getNumberOfBacklogOrders({{10, 5, 0}, {15, 2, 1}, {25, 1, 1}, {30, 4, 0}}));
    ASSERT_EQ(999999984, solution.getNumberOfBacklogOrders({{7, 1000000000, 1}, {15, 3, 0}, {5, 999999995, 0}, {5, 1, 1}}));
}

TEST(NumberOfOrdersInBacklogTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(597466125, solution.getNumberOfBacklogOrders({{485892086, 324173812, 0},
                                                            {543654114, 476938198, 0},
                                                            {590552061, 829475366, 0},
                                                            {271381554, 683613211, 0},
                                                            {455457663, 790419242, 0},
                                                            {395526922, 451903643, 1},
                                                            {302317355, 707587320, 0},
                                                            {965023202, 97148783, 0},
                                                            {908754494, 5173679, 1},
                                                            {288702557, 498607743, 1},
                                                            {854599176, 839172022, 1},
                                                            {682724429, 804623264, 1}}));
}

}