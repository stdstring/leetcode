#include <unordered_set>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    int minCameraCover(TreeNode* root) const
    {
        std::unordered_set<TreeNode*> coveredNodes;
        coveredNodes.insert(nullptr);
        return static_cast<int>(calcNodesWithCameras(root, nullptr, coveredNodes));
    }

private:
    size_t calcNodesWithCameras(TreeNode* root, TreeNode* parent, std::unordered_set<TreeNode*> &coveredNodes) const
    {
        if (root == nullptr)
            return 0;
        size_t camerasCount = calcNodesWithCameras(root->left, root, coveredNodes) + calcNodesWithCameras(root->right, root, coveredNodes);
        const bool isChildrenCovered = (coveredNodes.count(root->left) * coveredNodes.count(root->right) == 1);
        if (!isChildrenCovered || ((parent == nullptr) && (coveredNodes.count(root) == 0)))
        {
            coveredNodes.insert(root->left);
            coveredNodes.insert(root->right);
            coveredNodes.insert(root);
            coveredNodes.insert(parent);
            ++camerasCount;
        }
        return camerasCount;
    }
};

}

using CommonLib::Codec;

namespace BinaryTreeCamerasTask
{

TEST(BinaryTreeCamerasTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minCameraCover(Codec::createTree("[0,0,null,0,0]").get()));
    ASSERT_EQ(2, solution.minCameraCover(Codec::createTree("[0,0,null,0,null,0,null,null,0]").get()));
}

TEST(BinaryTreeCamerasTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minCameraCover(Codec::createTree("[0]").get()));
}

}