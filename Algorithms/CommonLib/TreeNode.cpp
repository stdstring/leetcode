#include <vector>

#include "TreeNode.h"

CommonLib::TreeNode::TreeNode() : val(0), left(nullptr), right(nullptr), next(nullptr)
{
}

CommonLib::TreeNode::TreeNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr)
{
}

CommonLib::TreeNode::TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right), next(nullptr)
{
}

CommonLib::TreeNode::TreeNode(int x, int leftValue, TreeNode* right) : val(x), left(new TreeNode(leftValue)), right(right), next(nullptr)
{
}

CommonLib::TreeNode::TreeNode(int x, TreeNode* left, int rightValue) : val(x), left(left), right(new TreeNode(rightValue)), next(nullptr)
{
}

CommonLib::TreeNode::TreeNode(int x, int leftValue, int rightValue) : val(x), left(new TreeNode(leftValue)), right(new TreeNode(rightValue)), next(nullptr)
{
}

CommonLib::NTreeNode::NTreeNode() : val(0)
{
}

CommonLib::NTreeNode::NTreeNode(int x) : val(x)
{
}

CommonLib::NTreeNode::NTreeNode(int x, std::vector<NTreeNode*> const &children) : val(x), children(children)
{
}