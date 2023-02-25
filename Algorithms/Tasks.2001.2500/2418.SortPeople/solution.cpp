#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> sortPeople(std::vector<std::string> const &names, std::vector<int> const &heights) const
    {
        std::vector<size_t> indices(names.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&heights](size_t left, size_t right){ return heights[left] > heights[right]; });
        std::vector<std::string> result(names.size(), "");
        for (size_t index = 0; index < indices.size(); ++index)
            result[index] = names[indices[index]];
        return result;
    }
};

}

namespace SortPeopleTask
{

TEST(SortPeopleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"Mary", "Emma", "John"}), solution.sortPeople({"Mary", "John", "Emma"}, {180, 165, 170}));
    ASSERT_EQ(std::vector<std::string>({"Bob", "Alice", "Bob"}), solution.sortPeople({"Alice", "Bob", "Bob"}, {155, 185, 150}));
}

}