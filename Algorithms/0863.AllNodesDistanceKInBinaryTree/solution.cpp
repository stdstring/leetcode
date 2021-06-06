#include <memory>
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
    std::vector<int> distanceK(TreeNode* root, TreeNode* target, int k) const
    {
        std::vector<int> nodes;
        std::unordered_map<TreeNode*, TreeNode*> parentMap;
        parentMap.emplace(root, nullptr);
        findTarget(root, target, parentMap);
        TreeNode* prev = nullptr;
        TreeNode* current = target;
        while ((current != nullptr) && k > 0)
        {
            if (prev == nullptr)
                findNodes(current, k, nodes);
            else
                findNodes(current->left == prev ? current->right : current->left, k - 1, nodes);
            --k;
            prev = current;
            current = parentMap[current];
        }
        if ((k == 0) && (current != nullptr))
            nodes.push_back(current->val);
        return nodes;
    }

private:
    bool findTarget(TreeNode* root, TreeNode* target, std::unordered_map<TreeNode*, TreeNode*> &parentMap) const
    {
        if (root == target)
            return true;
        if (root->left != nullptr)
        {
            parentMap.emplace(root->left, root);
            if (findTarget(root->left, target, parentMap))
                return true;
        }
        if (root->right != nullptr)
        {
            parentMap.emplace(root->right, root);
            if (findTarget(root->right, target, parentMap))
                return true;
        }
        return false;
    }

    void findNodes(TreeNode* root, int distance, std::vector<int> &nodes) const
    {
        if (root == nullptr)
            return;
        if (distance == 0)
            nodes.push_back(root->val);
        else
        {
            findNodes(root->left, distance - 1, nodes);
            findNodes(root->right, distance - 1, nodes);
        }
    }
};

}

using CommonLib::Codec;
using CommonLib::findNodeByValue;

namespace AllNodesDistanceKInBinaryTree
{

TEST(AllNodesDistanceKInBinaryTreeTests, Examples)
{
    const Solution solution;
    const std::shared_ptr<TreeNode> root = Codec::createTree("[3,5,1,6,2,0,8,null,null,7,4]");
    const int targetValue = 5;
    TreeNode* target = findNodeByValue(root.get(), targetValue);
    ASSERT_EQ(std::vector<int>({ 7, 4, 1 }), solution.distanceK(root.get(), target, 2));
}

}