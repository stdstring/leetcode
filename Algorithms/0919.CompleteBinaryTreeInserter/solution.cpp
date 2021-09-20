#include <memory>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class CBTInserter
{
public:
    CBTInserter(TreeNode* root) : _root(CommonLib::createTreeHolder(root)), _levelSize(0), _totalLevelSize(0)
    {
        initCounters();
    }

    int insert(int v)
    {
        if (_levelSize == _totalLevelSize)
        {
            _levelSize = 0;
            _totalLevelSize *= 2;
        }
        TreeNode* parent = _root.get();
        size_t levelSize = _levelSize;
        size_t divider = _totalLevelSize / 2;
        while (divider != 1)
        {
            parent = levelSize / divider == 0 ? parent->left : parent->right;
            levelSize %= divider;
            divider /= 2;
        }
        (levelSize == 0 ? parent->left : parent->right) = new TreeNode(v);
        ++_levelSize;
        return parent->val;
    }

    TreeNode* get_root() const
    {
        return _root.get();
    }

private:
    std::shared_ptr<TreeNode> _root;
    size_t _levelSize;
    size_t _totalLevelSize;

    void initCounters()
    {
        _levelSize = calcTreeNodes(_root.get());
        _totalLevelSize = 1;
        while (_levelSize > _totalLevelSize)
        {
            _levelSize -= _totalLevelSize;
            _totalLevelSize *= 2;
        }
    }

    size_t calcTreeNodes(TreeNode* root) const
    {
        size_t count = 1;
        if (root->left != nullptr)
            count += calcTreeNodes(root->left);
        if (root->right != nullptr)
            count += calcTreeNodes(root->right);
        return count;
    }
};

}

using CommonLib::Codec;

namespace CompleteBinaryTreeInserterTask
{

TEST(CompleteBinaryTreeInserterTaskTests, Examples)
{
    CBTInserter inserter(Codec::createTreeRaw("[1,2]"));
    ASSERT_EQ(1, inserter.insert(3));
    ASSERT_EQ(2, inserter.insert(4));
    ASSERT_EQ("[1,2,3,4]", Codec::createDataRaw(inserter.get_root()));
}

}