#include <deque>
#include <memory>

#include "TreeNode.h"
#include "TreeNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::TreeNode;

namespace
{

class BSTIterator
{
public:
    BSTIterator(TreeNode* root) : _root(root), _current(nullptr)
    {
    }

    int next()
    {
        if (_current == nullptr)
        {
            _current = _root;
            moveLeftDown();
        }
        else if (_current->right != nullptr)
        {
            moveRightDownOneStep();
            moveLeftDown();
        }
        else
        {
            moveRightUp();
            if (_current == _parents.front()->left)
                moveLeftUpOneStep();
        }
        return _current->val;
    }

    bool hasNext()
    {
        if (_current == nullptr)
            return _root != nullptr;
        if (_current->right != nullptr)
            return true;
        TreeNode* child = _current;
        for (TreeNode* parent : _parents)
        {
            if (child == parent->left)
                return true;
            child = parent;
        }
        return false;
    }

private:
    void moveLeftDown()
    {
        while (_current->left != nullptr)
        {
            _parents.push_front(_current);
            _current = _current->left;
        }
    }

    void moveLeftUpOneStep()
    {
        _current = _parents.front();
        _parents.pop_front();
    }

    void moveRightDownOneStep()
    {
        _parents.push_front(_current);
        _current = _current->right;
    }

    void moveRightUp()
    {
        while (_current == _parents.front()->right)
        {
            _current = _parents.front();
            _parents.pop_front();
        }
    }

    std::deque<TreeNode*> _parents;
    TreeNode* _root;
    TreeNode* _current;
};

}

using CommonLib::Codec;

namespace BinarySearchTreeIteratorTask
{

TEST(BinarySearchTreeIteratorTaskTests, Examples)
{
    const std::shared_ptr<TreeNode> tree = Codec::createTree("[7,3,15,null,null,9,20]");
    BSTIterator bSTIterator(tree.get());
    ASSERT_EQ(3, bSTIterator.next());
    ASSERT_EQ(7, bSTIterator.next());
    ASSERT_TRUE(bSTIterator.hasNext());
    ASSERT_EQ(9, bSTIterator.next());
    ASSERT_TRUE(bSTIterator.hasNext());
    ASSERT_EQ(15, bSTIterator.next());
    ASSERT_TRUE(bSTIterator.hasNext());
    ASSERT_EQ(20, bSTIterator.next());
    ASSERT_FALSE(bSTIterator.hasNext());
}

TEST(BinarySearchTreeIteratorTaskTests, FromWrongAnswers)
{
    const std::shared_ptr<TreeNode> tree = Codec::createTree("[3,1,4,null,2]");
    BSTIterator bSTIterator(tree.get());
    ASSERT_TRUE(bSTIterator.hasNext());
    ASSERT_EQ(1, bSTIterator.next());
    ASSERT_TRUE(bSTIterator.hasNext());
    ASSERT_EQ(2, bSTIterator.next());
    ASSERT_TRUE(bSTIterator.hasNext());
    ASSERT_EQ(3, bSTIterator.next());
    ASSERT_TRUE(bSTIterator.hasNext());
    ASSERT_EQ(4, bSTIterator.next());
    ASSERT_FALSE(bSTIterator.hasNext());
}

}
