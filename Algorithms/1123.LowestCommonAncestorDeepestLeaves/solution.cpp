#include <unordered_map>
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
    TreeNode* lcaDeepestLeaves(TreeNode* root) const
    {
        std::unordered_map<TreeNode*, TreeNode*> parentMap;
        std::unordered_set<TreeNode*> nodes;
        int deepestLevel = 0;
        findDeepestNodes(root, 1, parentMap, nodes, deepestLevel);
        std::unordered_set<TreeNode*> parents;
        while (nodes.size() > 1)
        {
            for (TreeNode* node : nodes)
                parents.emplace(parentMap[node]);
            std::swap(nodes, parents);
            parents.clear();
        }
        return *nodes.cbegin();
    }

private:
    void findDeepestNodes(TreeNode* root, int level, std::unordered_map<TreeNode*, TreeNode*> &parentMap, std::unordered_set<TreeNode*> &deepestNodes, int &deepestLevel) const
    {
        if (level > deepestLevel)
        {
            deepestNodes.clear();
            deepestLevel = level;
        }
        if (level == deepestLevel)
            deepestNodes.emplace(root);
        if (root->left != nullptr)
        {
            parentMap.emplace(root->left, root);
            findDeepestNodes(root->left, level + 1, parentMap, deepestNodes, deepestLevel);
        }
        if (root->right != nullptr)
        {
            parentMap.emplace(root->right, root);
            findDeepestNodes(root->right, level + 1, parentMap, deepestNodes, deepestLevel);
        }
    }
};

}

using CommonLib::Codec;

namespace LowestCommonAncestorDeepestLeavesTask
{

TEST(SmallestSubtreeWithAllDeepestNodesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[2,7,4]", Codec::createDataRaw(solution.lcaDeepestLeaves(Codec::createTree("[3,5,1,6,2,0,8,null,null,7,4]").get())));
    ASSERT_EQ("[1]", Codec::createDataRaw(solution.lcaDeepestLeaves(Codec::createTree("[1]").get())));
    ASSERT_EQ("[2]", Codec::createDataRaw(solution.lcaDeepestLeaves(Codec::createTree("[0,1,3,null,2]").get())));
}

}