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
    TreeNode* recoverFromPreorder(std::string const &traversal) const
    {
        size_t index = 0;
        return recoverNode(traversal, index, 0);
    }

private:
    TreeNode* recoverNode(std::string const &traversal, size_t &index, size_t level) const
    {
        if (index + level >= traversal.size())
            return nullptr;
        for (size_t shift = 0; shift < level; ++shift)
        {
            if (traversal[index + shift] != '-')
                return nullptr;
        }
        index += level;
        const int number = extractNumber(traversal, index);
        TreeNode* node = new TreeNode(number);
        node->left = recoverNode(traversal, index, level + 1);
        node->right = recoverNode(traversal, index, level + 1);
        return node;
    }

    int extractNumber(std::string const &traversal, size_t &index) const
    {
        int number = 0;
        while (index < traversal.size() && std::isdigit(traversal[index]))
            number = 10 * number + (traversal[index++] - '0');
        return number;
    }
};

}

using CommonLib::Codec;
using CommonLib::createTreeHolder;

namespace RecoverTreeFromPreorderTraversalTask
{

TEST(RecoverTreeFromPreorderTraversalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("[1,2,5,3,4,6,7]", Codec::createData(createTreeHolder(solution.recoverFromPreorder("1-2--3--4-5--6--7"))));
    ASSERT_EQ("[1,2,5,3,null,6,null,4,null,7]", Codec::createData(createTreeHolder(solution.recoverFromPreorder("1-2--3---4-5--6---7"))));
    ASSERT_EQ("[1,401,null,349,88,90]", Codec::createData(createTreeHolder(solution.recoverFromPreorder("1-401--349---90--88"))));
}

}