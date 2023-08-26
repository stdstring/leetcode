#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct Employee
{
    Employee(int id, int importance, std::vector<int> const &subordinates) :
        id(id), importance(importance), subordinates(subordinates)
    {
    }

    int id;
    int importance;
    std::vector<int> subordinates;
};

class Solution
{
public:
    [[nodiscard]] int getImportance(std::vector<Employee const*> const &employees, int id) const
    {
        std::unordered_map<int, Employee const*> employeeMap;
        for (Employee const* employee : employees)
            employeeMap.emplace(employee->id, employee);
        return getImportance(employeeMap, id);
    }

private:
    [[nodiscard]] int getImportance(std::unordered_map<int, Employee const*> const &employeeMap, int id) const
    {
        Employee const* employee = employeeMap.at(id);
        int importanceValue = employee->importance;
        for (const int subordinateId : employee->subordinates)
            importanceValue += getImportance(employeeMap, subordinateId);
        return importanceValue;
    }
};

}

namespace
{

void checkGetImportance(std::vector<Employee> const &employees, int id, int expectedValue)
{
    std::vector<Employee const*> employeePointers(employees.size(), nullptr);
    for (size_t index = 0; index < employees.size(); ++index)
        employeePointers[index] = &employees[index];
    constexpr Solution solution;
    ASSERT_EQ(expectedValue, solution.getImportance(employeePointers, id));
}

}

namespace EmployeeImportanceTask
{

TEST(EmployeeImportanceTaskTests, Examples)
{
    checkGetImportance({Employee(1, 5, {2, 3}), Employee(2, 3, {}), Employee(3, 3, {})}, 1, 11);
    checkGetImportance({Employee(1, 2, {5}), Employee(5, -3, {})}, 5, -3);
}

}