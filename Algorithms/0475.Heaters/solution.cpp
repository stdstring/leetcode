#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findRadius(std::vector<int> const &houses, std::vector<int> const &heaters) const
    {
        std::vector<int> housesData(houses);
        std::sort(housesData.begin(), housesData.end());
        std::vector<int> heatersData(heaters);
        std::sort(heatersData.begin(), heatersData.end());
        int minRadius = 0;
        size_t heaterIndex = 0;
        size_t houseIndex = 0;
        while (houseIndex < housesData.size() && heaterIndex < heatersData.size())
        {
            if (housesData[houseIndex] <= heatersData[heaterIndex])
            {
                minRadius = std::max(minRadius, calcCurrentRadius(housesData, heatersData, houseIndex, heaterIndex));
                ++houseIndex;
            }
            else
                ++heaterIndex;
        }
        if (heaterIndex == heatersData.size())
            minRadius = std::max(minRadius, housesData.back() - heatersData.back());
        return minRadius;
    }

private:
    int calcCurrentRadius(std::vector<int> const &houses, std::vector<int> const &heaters, size_t houseIndex, size_t heaterIndex) const
    {
        if (heaterIndex == 0)
            return heaters[heaterIndex] - houses[houseIndex];
        return std::min(houses[houseIndex] - heaters[heaterIndex - 1], heaters[heaterIndex] - houses[houseIndex]);
    }
};

}

namespace HeatersTask
{

TEST(HeatersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.findRadius({1, 2, 3}, {2}));
    ASSERT_EQ(1, solution.findRadius({1, 2, 3, 4}, {1, 4}));
    ASSERT_EQ(3, solution.findRadius({1, 5}, {2}));
}

TEST(HeatersTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(13, solution.findRadius({1, 2, 3, 5, 15}, {2, 30}));
    ASSERT_EQ(161834419, solution.findRadius({282475249, 622650073, 984943658, 144108930, 470211272, 101027544, 457850878, 458777923},
                                             {823564440, 115438165, 784484492, 74243042, 114807987, 137522503, 441282327, 16531729, 823378840, 143542612}));
    ASSERT_EQ(132843297, solution.findRadius({35308228, 158374933, 75260298, 824938981, 595028635, 962408013, 137623865, 997389814, 20739063},
                                             {635339425, 654001669, 777724115, 269220094, 34075629, 478446501, 864546517}));
    ASSERT_EQ(0, solution.findRadius({1}, {1, 2, 3, 4}));
}


}