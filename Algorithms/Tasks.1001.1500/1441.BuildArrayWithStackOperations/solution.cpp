#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> buildArray(std::vector<int> const &target, int n) const
    {
        std::vector<std::string> operations;
        int prevNumber = 0;
        for (const int number : target)
        {
            insertPushPop(operations, number - prevNumber - 1);
            operations.emplace_back("Push");
            prevNumber = number;
        }
        return operations;
    }

private:
    void insertPushPop(std::vector<std::string> &operations, size_t count) const
    {
        for (size_t index = 0; index < count; ++index)
        {
            operations.emplace_back("Push");
            operations.emplace_back("Pop");
        }
    }
};

}

namespace BuildArrayWithStackOperationsTask
{

TEST(BuildArrayWithStackOperationsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"Push", "Push", "Pop", "Push"}), solution.buildArray({1, 3}, 3));
    ASSERT_EQ(std::vector<std::string>({"Push", "Push", "Push"}), solution.buildArray({1, 2, 3}, 3));
    ASSERT_EQ(std::vector<std::string>({"Push", "Push"}), solution.buildArray({1, 2}, 4));
}

}
