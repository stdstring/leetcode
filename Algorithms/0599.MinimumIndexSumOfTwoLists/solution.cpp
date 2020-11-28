#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::string> findRestaurant(std::vector<std::string> const &list1, std::vector<std::string> const &list2) const
    {
        std::unordered_map<std::string, size_t> list2IndexData;
        for (size_t index = 0; index < list2.size(); ++index)
            list2IndexData.emplace(list2[index], index);
        size_t leastIndexSum = list1.size() + list2.size();
        std::vector<std::string> result;
        for (size_t index = 0; index < list1.size(); ++index)
        {
            std::unordered_map<std::string, size_t>::const_iterator entry = list2IndexData.find(list1[index]);
            if (entry != list2IndexData.cend())
            {
                const size_t indexSum = index + entry->second;
                if (indexSum == leastIndexSum)
                    result.push_back(list1[index]);
                if (indexSum < leastIndexSum)
                {
                    leastIndexSum = indexSum;
                    result.clear();
                    result.push_back(list1[index]);
                }
            }
        }
        return result;
    }
};

}

namespace MinimumIndexSumOfTwoListsTask
{

TEST(MinimumIndexSumOfTwoListsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::string>({"Shogun"}),
              solution.findRestaurant({"Shogun", "Tapioca Express", "Burger King", "KFC"}, {"Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"}));
    ASSERT_EQ(std::vector<std::string>({"Shogun"}), solution.findRestaurant({"Shogun","Tapioca Express","Burger King","KFC"}, {"KFC","Shogun","Burger King"}));
    ASSERT_EQ(std::vector<std::string>({"Shogun", "Tapioca Express", "Burger King", "KFC"}),
              solution.findRestaurant({"Shogun","Tapioca Express","Burger King","KFC"}, {"KFC","Burger King","Tapioca Express","Shogun"}));
    ASSERT_EQ(std::vector<std::string>({"Shogun", "Tapioca Express", "Burger King", "KFC"}),
              solution.findRestaurant({"Shogun","Tapioca Express","Burger King","KFC"}, {"KNN","KFC","Burger King","Tapioca Express","Shogun"}));
    ASSERT_EQ(std::vector<std::string>({"KFC"}), solution.findRestaurant({"KFC"}, {"KFC"}));
}

}