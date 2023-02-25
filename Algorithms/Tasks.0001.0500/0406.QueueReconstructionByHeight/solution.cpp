#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> reconstructQueue(std::vector<std::vector<int>> const &people) const
    {
        std::vector<std::vector<int>> sortedPeople(people);
        std::sort(sortedPeople.begin(), sortedPeople.end(), [](std::vector<int> const &l, std::vector<int> const &r){ return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] > r[1])); });
        std::vector<std::vector<int>> result(people.size(), std::vector<int>({-1, -1}));
        for (std::vector<int> const &man : sortedPeople)
        {
            size_t index = 0;
            int personBefore = -1;
            while (personBefore < man[1])
            {
                if (result[index][0] == -1)
                    ++personBefore;
                ++index;
            }
            result[index - 1] = man;
        }
        return result;
    }
};

}

namespace QueueReconstructionByHeightTask
{

TEST(QueueReconstructionByHeightTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{5, 0}, {7, 0}, {5, 2}, {6, 1}, {4, 4}, {7, 1}}), solution.reconstructQueue({{7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{4, 0}, {5, 0}, {2, 2}, {3, 2}, {1, 4}, {6, 0}}), solution.reconstructQueue({{6, 0}, {5, 0}, {4, 0}, {3, 2}, {2, 2}, {1, 4}}));
}

}