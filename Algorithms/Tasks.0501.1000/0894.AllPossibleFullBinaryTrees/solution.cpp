#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::createTreeHolder;
using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<TreeNode*> allPossibleFBT(int n) const
    {
        if (n % 2 == 0)
            return {};
        if (n == 1)
            return {new TreeNode(0)};
        std::vector<std::vector<std::shared_ptr<TreeNode>>> possibleTrees;
        possibleTrees.push_back({createTreeHolder(new TreeNode(0))});
        for (int size = 3; size < n; size += 2)
        {
            possibleTrees.emplace_back();
            for (int firstSize = 1; firstSize <= size / 2; firstSize += 2)
            {
                const int secondSize = size - firstSize - 1;
                for (std::shared_ptr<TreeNode> const &firstSubtree : possibleTrees[firstSize / 2])
                {
                    for (std::shared_ptr<TreeNode> const &secondSubtree : possibleTrees[secondSize / 2])
                    {
                        possibleTrees[size / 2].push_back(createTreeHolder(createTree(firstSubtree, secondSubtree)));
                        if (firstSize != secondSize)
                            possibleTrees[size / 2].push_back(createTreeHolder(createTree(secondSubtree, firstSubtree)));
                    }
                }
            }
        }
        std::vector<TreeNode*> dest;
        for (int firstSize = 1; firstSize <= n / 2; firstSize += 2)
        {
            const int secondSize = n - firstSize - 1;
            for (std::shared_ptr<TreeNode> const &firstSubtree : possibleTrees[firstSize / 2])
            {
                for (std::shared_ptr<TreeNode> const &secondSubtree : possibleTrees[secondSize / 2])
                {
                    dest.push_back(createTree(firstSubtree, secondSubtree));
                    if (firstSize != secondSize)
                        dest.push_back(createTree(secondSubtree, firstSubtree));
                }
            }
        }
        return dest;
    }

private:
    TreeNode* copyTree(TreeNode* source) const
    {
        if (source == nullptr)
            return nullptr;
        TreeNode* dest = new TreeNode(source->val);
        dest->left = copyTree(source->left);
        dest->right = copyTree(source->right);
        return dest;
    }

    TreeNode* createTree(std::shared_ptr<TreeNode> const &leftSubtree, std::shared_ptr<TreeNode> const &rightSubtree) const
    {
        return new TreeNode(0, copyTree(leftSubtree.get()), copyTree(rightSubtree.get()));
    }
};

}

using CommonLib::createTreeHolder;
using CommonLib::Codec;

namespace
{

void checkAllPossibleFBT(int n, std::vector<std::string> const &expectedData)
{
    constexpr Solution solution;
    const std::vector<TreeNode*> trees(solution.allPossibleFBT(n));
    std::vector<std::shared_ptr<TreeNode>> treeHolders;
    std::transform(trees.cbegin(), trees.cend(), std::back_inserter(treeHolders), [](TreeNode* node){ return createTreeHolder(node); });
    std::vector<std::string> actualData;
    std::transform(treeHolders.cbegin(), treeHolders.cend(), std::back_inserter(actualData), [](std::shared_ptr<TreeNode> const &node){ return Codec::createData(node); });
    ASSERT_EQ(expectedData, actualData);
}

}

namespace AllPossibleFullBinaryTreesTask
{

TEST(AllPossibleFullBinaryTreesTaskTests, Examples)
{
    checkAllPossibleFBT(7, {"[0,0,0,null,null,0,0,null,null,0,0]", "[0,0,0,0,0,null,null,null,null,0,0]", "[0,0,0,null,null,0,0,0,0]", "[0,0,0,0,0,null,null,0,0]", "[0,0,0,0,0,0,0]"});
    checkAllPossibleFBT(3, {"[0,0,0]"});
}

}