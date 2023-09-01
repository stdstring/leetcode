#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> groupThePeople(std::vector<int> const &groupSizes) const
    {
        std::vector<std::vector<int>> result;
        std::unordered_map<size_t, std::vector<int>> currentGroups;
        for (size_t index = 0; index < groupSizes.size(); ++index)
        {
            int id = static_cast<int>(index);
            size_t currentSize = groupSizes[index];
            auto iterator = currentGroups.find(currentSize);
            if (iterator == currentGroups.end())
                iterator = currentGroups.emplace(currentSize, std::vector<int>()).first;
            iterator->second.emplace_back(id);
            if (iterator->second.size() == currentSize)
            {
                result.emplace_back(iterator->second);
                currentGroups.erase(iterator);
            }
        }
        return result;
    }
};

}

namespace GroupPeopleGivenGroupSizeTheyBelongToTask
{

TEST(GroupPeopleGivenGroupSizeTheyBelongToTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1, 2}, {5}, {3, 4, 6}}), solution.groupThePeople({3, 3, 3, 3, 3, 1, 3}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1}, {2, 3, 4}, {0, 5}}), solution.groupThePeople({2, 1, 3, 3, 3, 2}));
}

}