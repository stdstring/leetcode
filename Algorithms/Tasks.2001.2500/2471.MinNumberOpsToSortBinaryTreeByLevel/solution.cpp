#include <algorithm>
#include <utility>
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
    int minimumOperations(TreeNode* root) const
    {
        std::vector<std::vector<TLayerData>> layers;
        fillLayers(root, 0, layers);
        size_t operationCount = 0;
        for (std::vector<TLayerData> &layer : layers)
            operationCount += calcOperationCount(layer);
        return static_cast<int>(operationCount);
    }

private:
    typedef std::pair<TreeNode*, size_t> TLayerData;

    void fillLayers(TreeNode* root, size_t layer, std::vector<std::vector<TLayerData>> &layers) const
    {
        if (layer == layers.size())
            layers.emplace_back(std::vector<TLayerData>());
        layers[layer].emplace_back(root, layers[layer].size());
        if (root->left != nullptr)
            fillLayers(root->left, layer + 1, layers);
        if (root->right != nullptr)
            fillLayers(root->right, layer + 1, layers);
    }

    size_t calcOperationCount(std::vector<TLayerData> &layer) const
    {
        if (layer.size() == 1)
            return 0;
        std::sort(layer.begin(), layer.end(), [](TLayerData const &left, TLayerData const &right){ return left.first->val < right.first->val; });
        std::vector<bool> usedNodes(layer.size(), false);
        size_t operationCount = 0;
        for (size_t index = 0; index < layer.size(); ++index)
        {
            if (usedNodes[index] || (layer[index].second == index))
                continue;
            size_t cycleSize = 0;
            for (size_t current = index; !usedNodes[current]; current = layer[current].second)
            {
                ++cycleSize;
                usedNodes[current] = true;
            }
            operationCount += (cycleSize - 1);
        }
        return operationCount;
    }
};

}

using CommonLib::Codec;

namespace MinNumberOpsToSortBinaryTreeByLevelTask
{

TEST(MinNumberOpsToSortBinaryTreeByLevelTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minimumOperations(Codec::createTree("[1,4,3,7,6,8,5,null,null,null,null,9,null,10]").get()));
    ASSERT_EQ(3, solution.minimumOperations(Codec::createTree("[1,3,2,7,6,5,4]").get()));
    ASSERT_EQ(0, solution.minimumOperations(Codec::createTree("[1,2,3,4,5,6]").get()));
}

}
