#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numFactoredBinaryTrees(std::vector<int> const &arr) const
    {
        std::unordered_map<int, std::vector<std::pair<int, int>>> multipliersMap;
        std::unordered_map<int, int> binaryTreesMap;
        for (int number : arr)
        {
            multipliersMap.emplace(number, std::vector<std::pair<int, int>>());
            binaryTreesMap.emplace(number, 0);
        }
        for (size_t index1 = 0; index1 < arr.size(); ++index1)
        {
            for (size_t index2 = index1; index2 < arr.size(); ++index2)
            {
                const long long product = 1LL * arr[index1] * arr[index2];
                if (product > INT_MAX)
                    continue;
                auto iterator = multipliersMap.find(static_cast<int>(product));
                if (iterator == multipliersMap.end())
                    continue;
                iterator->second.emplace_back(arr[index1], arr[index2]);
            }
        }
        int result = 0;
        for (const int number : arr)
            result = (result + calcBinaryTrees(number, multipliersMap, binaryTreesMap)) % ModValue;
        return result;
    }

private:
    static constexpr int ModValue = 1000000007;

    [[nodiscard]] int calcBinaryTrees(int number, std::unordered_map<int, std::vector<std::pair<int, int>>> const &multipliersMap, std::unordered_map<int, int> &binaryTreesMap) const
    {
        if (binaryTreesMap[number] > 0)
            return binaryTreesMap[number];
        binaryTreesMap[number] = 1;
        for (auto const &[multiplier1, multiplier2] : multipliersMap.at(number))
        {
            const long long binaryTreesCount1 = calcBinaryTrees(multiplier1, multipliersMap, binaryTreesMap);
            const long long binaryTreesCount2 = calcBinaryTrees(multiplier2, multipliersMap, binaryTreesMap);
            const long long permutation = multiplier1 == multiplier2 ? 1 : 2;
            const int totalBinaryTreesCount = static_cast<int>((permutation * binaryTreesCount1 * binaryTreesCount2) % ModValue);
            binaryTreesMap[number] = (binaryTreesMap[number] + totalBinaryTreesCount) % ModValue;
        }
        return binaryTreesMap[number];
    }
};

}

namespace BinaryTreesWithFactorsTask
{

TEST(BinaryTreesWithFactorsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numFactoredBinaryTrees({2, 4}));
    ASSERT_EQ(7, solution.numFactoredBinaryTrees({2, 4, 5, 10}));
}

}