#include <memory>
#include <vector>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

struct TreeData
{
    TreeData(TreeNode* root, size_t nodesCount) : Root(root), NodesCount(nodesCount), Processed(false)
    {
    }

    TreeNode* Root;
    size_t NodesCount;
    bool Processed;
};

class Solution
{
public:
    std::vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) const
    {
        std::map<int, std::vector<TreeData>> storage;
        collectData(root, storage);
        std::vector<TreeNode*> subtrees;
        for (auto entry : storage)
        {
            for (size_t index1 = 0; index1 < entry.second.size() - 1; ++index1)
            {
                if (entry.second[index1].Processed)
                    continue;
                for (size_t index2 = index1 + 1; index2 < entry.second.size(); ++index2)
                {
                    if (entry.second[index2].Processed)
                        continue;
                    if (entry.second[index1].NodesCount != entry.second[index2].NodesCount)
                        continue;
                    if (compareTrees(entry.second[index1].Root, entry.second[index2].Root))
                    {
                        if (!entry.second[index1].Processed)
                            subtrees.push_back(entry.second[index1].Root);
                        entry.second[index1].Processed = true;
                        entry.second[index2].Processed = true;
                    }
                }
            }
        }
        return subtrees;
    }

private:
    size_t collectData(TreeNode* root, std::map<int, std::vector<TreeData>> &storage) const
    {
        if (root == nullptr)
            return 0;
        size_t nodesCount = 1 + collectData(root->left, storage) + collectData(root->right, storage);
        auto iterator = storage.find(root->val);
        if (iterator == storage.end())
            iterator = storage.emplace(root->val, std::vector<TreeData>()).first;
        iterator->second.emplace_back(root, nodesCount);
        return nodesCount;
    }

    bool compareTrees(TreeNode* a, TreeNode* b) const
    {
        if (a->val != b->val)
            return false;
        if ((a->left == nullptr) != (b->left == nullptr))
            return false;
        if ((a->left != nullptr) && !compareTrees(a->left, b->left))
            return false;
        if ((a->right == nullptr) != (b->right == nullptr))
            return false;
        if ((a->right != nullptr) && !compareTrees(a->right, b->right))
            return false;
        return true;
    }
};

}

using CommonLib::Codec;

namespace
{

void checkFindDuplicateSubtrees(std::string const &source, std::vector<std::string> const &expected)
{
    const std::shared_ptr<TreeNode> tree(Codec::createTree(source));
    constexpr Solution solution;
    const std::vector<TreeNode*> actual(solution.findDuplicateSubtrees(tree.get()));
    ASSERT_EQ(expected.size(), actual.size());
    for (size_t index = 0; index < expected.size(); ++index)
        ASSERT_EQ(expected[index], Codec::createDataRaw(actual[index]));
}

}

namespace FindDuplicateSubtreesTask
{

TEST(FindDuplicateSubtreesTaskTests, Examples)
{
    checkFindDuplicateSubtrees("[1,2,3,4,null,2,4,null,null,4]", {"[2,4]","[4]"});
    checkFindDuplicateSubtrees("[2,1,1]", {"[1]"});
    checkFindDuplicateSubtrees("[2,2,2,3,null,3,null]", {"[2,3]", "[3]"});
}

}