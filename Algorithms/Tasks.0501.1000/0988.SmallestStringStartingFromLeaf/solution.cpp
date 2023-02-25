#include <string>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class Solution
{
public:
    std::string smallestFromLeaf(TreeNode* root) const
    {
        std::string current;
        std::string best;
        traverseTree(root, current, best);
        std::reverse(best.begin(), best.end());
        return best;
    }

private:
    bool reverseLess(std::string const &a, std::string const &b) const
    {
        size_t rIndex = 0;
        while ((rIndex < a.size()) && (rIndex < b.size()))
        {
            if (a[a.size() - 1 - rIndex] < b[b.size() - 1 - rIndex])
                return true;
            if (a[a.size() - 1 - rIndex] > b[b.size() - 1 - rIndex])
                return false;
            ++rIndex;
        }
        return (rIndex == a.size()) && (rIndex != b.size());
    }

    void traverseTree(TreeNode* root, std::string &current, std::string &best) const
    {
        const char ch = static_cast<char>('a' + root->val);
        current.push_back(ch);
        if ((root->left == nullptr) && (root->right == nullptr))
        {
            if (best.empty() || reverseLess(current,  best))
                best = current;
        }
        else
        {
            if (root->left != nullptr)
                traverseTree(root->left, current, best);
            if (root->right != nullptr)
                traverseTree(root->right, current, best);
        }
        current.pop_back();
    }
};

}

using CommonLib::Codec;

namespace SmallestStringStartingFromLeafTask
{

TEST(SmallestStringStartingFromLeafTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("dba", solution.smallestFromLeaf(Codec::createTree("[0,1,2,3,4,3,4]").get()));
    ASSERT_EQ("adz", solution.smallestFromLeaf(Codec::createTree("[25,1,3,1,3,0,2]").get()));
    ASSERT_EQ("abc", solution.smallestFromLeaf(Codec::createTree("[2,2,1,null,1,0,null,0]").get()));
}

}