#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<std::string>> displayTable(std::vector<std::vector<std::string>> const &orders) const
    {
        std::set<int> tables;
        std::map<std::string, std::unordered_map<int, int>> foodTableOrders;
        for (std::vector<std::string> const &order : orders)
        {
            constexpr size_t foodIndex = 2;
            constexpr size_t tableIndex = 1;
            int table = stoi(order[tableIndex]);
            tables.insert(table);
            auto iterator = foodTableOrders.find(order[foodIndex]);
            if (iterator == foodTableOrders.end())
                iterator = foodTableOrders.emplace(order[foodIndex], std::unordered_map<int, int>()).first;
            ++iterator->second[table];
        }
        std::unordered_map<int, size_t> tableIndices;
        std::vector<std::vector<std::string>> result;
        const size_t columnCount = foodTableOrders.size() + 1;
        result.emplace_back(std::vector<std::string>(columnCount, ""));
        result.back()[0] = "Table";
        size_t tableIndex = 1;
        for (int table : tables)
        {
            tableIndices[table] = (tableIndex++);
            result.emplace_back(std::vector<std::string>(columnCount, "0"));
            result.back()[0] = std::to_string(table);
        }
        size_t columnIndex = 1;
        for (const auto& foodTableOrder : foodTableOrders)
        {
            result[0][columnIndex] = foodTableOrder.first;
            for (auto [table, count] : foodTableOrder.second)
                result[tableIndices[table]][columnIndex] = std::to_string(count);
            ++columnIndex;
        }
        return result;
    }
};

}

namespace DisplayTableOfFoodOrdersInRestaurantTask
{

TEST(DisplayTableOfFoodOrdersInRestaurantTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"Table", "Beef Burrito", "Ceviche", "Fried Chicken", "Water"},
                                                     {"3", "0", "2", "1", "0"},
                                                     {"5", "0", "1", "0", "1"},
                                                     {"10", "1", "0", "0", "0"}}),
              solution.displayTable({{"David", "3", "Ceviche"},
                                     {"Corina", "10", "Beef Burrito"},
                                     {"David", "3", "Fried Chicken"},
                                     {"Carla", "5", "Water"},
                                     {"Carla", "5", "Ceviche"},
                                     {"Rous", "3", "Ceviche"}}));
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"Table", "Canadian Waffles", "Fried Chicken"}, {"1", "2", "0"}, {"12", "0", "3"}}),
              solution.displayTable({{"James", "12", "Fried Chicken"},
                                     {"Ratesh", "12", "Fried Chicken"},
                                     {"Amadeus", "12", "Fried Chicken"},
                                     {"Adam", "1", "Canadian Waffles"},
                                     {"Brianna", "1", "Canadian Waffles"}}));
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"Table", "Bean Burrito", "Beef Burrito", "Soda"}, {"2", "1", "1", "1"}}),
              solution.displayTable({{"Laura", "2", "Bean Burrito"}, {"Jhon", "2", "Beef Burrito"}, {"Melissa", "2", "Soda"}}));
}

}