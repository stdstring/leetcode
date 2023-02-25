#include <unordered_map>
#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    std::vector<int> findFrequentTreeSum(TreeNode* root) const
    {
        std::unordered_map<int, size_t> sumFrequencyMap;
        calcSum(root, sumFrequencyMap);
        size_t maxFrequency = 0;
        for (auto const &entry : sumFrequencyMap)
            maxFrequency = std::max(maxFrequency, entry.second);
        std::vector<int> dest;
        for (auto const &entry : sumFrequencyMap)
        {
            if (entry.second == maxFrequency)
                dest.push_back(entry.first);
        }
        return dest;
    }

private:
    int calcSum(TreeNode* root, std::unordered_map<int, size_t> &sumFrequencyMap) const
    {
        int sum = root->val;
        if (root->left != nullptr)
            sum += calcSum(root->left, sumFrequencyMap);
        if (root->right != nullptr)
            sum += calcSum(root->right, sumFrequencyMap);
        ++sumFrequencyMap[sum];
        return sum;
    }
};

}

using CommonLib::Codec;

namespace MostFrequentSubtreeSumTask
{

TEST(MostFrequentSubtreeSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, -3, 4}), solution.findFrequentTreeSum(Codec::createTree("[5,2,-3]").get()));
    ASSERT_EQ(std::vector<int>({2}), solution.findFrequentTreeSum(Codec::createTree("[5,2,-5]").get()));
}

}
