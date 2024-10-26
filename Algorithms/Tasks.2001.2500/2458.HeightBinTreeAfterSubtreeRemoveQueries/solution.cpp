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
    [[nodiscard]] std::vector<int> treeQueries(TreeNode* root, std::vector<int> const &queries) const
    {
        const int maxNumber = findMaxNumberInTree(root);
        std::vector<NodeData> nodeData(maxNumber + 1);
        const int rootLeftHeight = root->left == nullptr ? 0 : processSubtree(root->left, nodeData, true, root->val, 1) + 1;
        const int rootRightHeight = root->right == nullptr ? 0 : processSubtree(root->right, nodeData, false, root->val, 1) + 1;
        std::vector<int> result(queries.size(), 0);
        for (size_t index = 0; index < queries.size(); ++index)
        {
            int current = queries[index];
            int currentSubtreeHeight = 0;
            while (nodeData[current].Parent != root->val)
            {
                const int parent = nodeData[current].Parent;
                int otherSubtreeHeight = nodeData[parent].PathToRoot +
                                         (nodeData[parent].LeftChild == current ? nodeData[parent].RightHeight : nodeData[parent].LeftHeight);
                if (otherSubtreeHeight > currentSubtreeHeight)
                    currentSubtreeHeight = otherSubtreeHeight;
                current = parent;
            }
            result[index] = std::max(currentSubtreeHeight, nodeData[current].IsLeftSubtree ? rootRightHeight : rootLeftHeight);
        }
        return result;
    }

private:
    struct NodeData
    {
        NodeData() : IsLeftSubtree(false), Parent(-1), PathToRoot(0), LeftChild(-1), LeftHeight(0), RightChild(-1), RightHeight(0)
        {
        }

        NodeData(bool isLeftSubtree, int parent, int pathToRoot, int leftChild, int leftHeight, int rightChild, int rightHeight) :
            IsLeftSubtree(isLeftSubtree),
            Parent(parent),
            PathToRoot(pathToRoot),
            LeftChild(leftChild),
            LeftHeight(leftHeight),
            RightChild(rightChild),
            RightHeight(rightHeight)
        {}

        bool IsLeftSubtree;
        int Parent;
        int PathToRoot;
        int LeftChild;
        int LeftHeight;
        int RightChild;
        int RightHeight;
    };

    [[nodiscard]] int findMaxNumberInTree(TreeNode* root) const
    {
        int maxNumber = root->val;
        if (root->left != nullptr)
            maxNumber = std::max(maxNumber, findMaxNumberInTree(root->left));
        if (root->right != nullptr)
            maxNumber = std::max(maxNumber, findMaxNumberInTree(root->right));
        return maxNumber;
    }

    [[nodiscard]] int processSubtree(TreeNode* root, std::vector<NodeData>& nodeData, bool isLeftSubtree, int parent, int pathToRoot) const
    {
        const int leftChild = root->left == nullptr ? -1 : root->left->val;
        const int leftHeight = root->left == nullptr ? 0 : processSubtree(root->left, nodeData, isLeftSubtree, root->val, pathToRoot + 1) + 1;
        const int rightChild = root->right == nullptr ? 1 : root->right->val;
        const int rightHeight = root->right == nullptr ? 0 : processSubtree(root->right, nodeData, isLeftSubtree, root->val, pathToRoot + 1) + 1;
        NodeData data(isLeftSubtree, parent, pathToRoot, leftChild, leftHeight, rightChild, rightHeight);
        std::swap(nodeData[root->val], data);
        return std::max(leftHeight, rightHeight);
    }
};

}

using CommonLib::Codec;

namespace HeightBinTreeAfterSubtreeRemoveQueriesTask
{

TEST(HeightBinTreeAfterSubtreeRemoveQueriesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2}), solution.treeQueries(Codec::createTree("[1,3,4,2,null,6,5,null,null,null,null,null,7]").get(), {4}));
    ASSERT_EQ(std::vector<int>({3, 2, 3, 2}), solution.treeQueries(Codec::createTree("[5,8,9,2,1,3,7,4,6]").get(), {3, 2, 4, 8}));
}

}