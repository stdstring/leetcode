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
    std::vector<std::vector<std::string>> printTree(TreeNode* root) const
    {
        const size_t height = calcHeight(root);
        const size_t rowCount = height + 1;
        const size_t columnCount = (1ll << (height + 1)) - 1;
        std::vector<std::vector<std::string>> board(rowCount, std::vector<std::string>(columnCount, ""));
        processNode(root, height, 0, columnCount / 2, board);
        return board;
    }

private:
    int calcHeight(TreeNode* root) const
    {
        if (root->left == nullptr && root->right == nullptr)
            return 0;
        return 1 + std::max(root->left == nullptr ? 0 : calcHeight(root->left), root->right == nullptr ? 0 : calcHeight(root->right));
    }

    void processNode(TreeNode* root, size_t height, size_t row, size_t column, std::vector<std::vector<std::string>> &board) const
    {
        board[row][column] = std::to_string(root->val);
        if (root->left != nullptr)
            processNode(root->left, height, row + 1, column - (1ll << (height - row - 1)), board);
        if (root->right != nullptr)
            processNode(root->right, height, row + 1, column + (1ll << (height - row - 1)), board);
    }
};

}

using CommonLib::Codec;

namespace PrintBinaryTreeTask
{

TEST(PrintBinaryTreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"", "1", ""}, {"2", "", ""}}), solution.printTree(Codec::createTree("[1,2]").get()));
    ASSERT_EQ(std::vector<std::vector<std::string>>({{"", "", "", "1", "", "", ""}, {"", "2", "", "", "", "3", ""}, {"", "", "4", "", "", "", ""}}),
              solution.printTree(Codec::createTree("[1,2,3,null,4]").get()));
}

}