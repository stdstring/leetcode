#include <vector>

#include "gtest/gtest.h"

namespace
{

class LockingTree
{
public:
    LockingTree(std::vector<int> const &parent) : _parent(parent), _children(parent.size(), std::vector<size_t>()), _locks(parent.size(), -1)
    {
        // 0 - root node
        for (size_t index = 1; index < parent.size(); ++index)
            _children[parent[index]].push_back(index);
    }

    bool lock(int num, int user)
    {
        if (_locks[num] != -1)
            return false;
        _locks[num] = user;
        return true;
    }

    bool unlock(int num, int user)
    {
        if (_locks[num] != user)
            return false;
        _locks[num] = -1;
        return true;
    }

    bool upgrade(int num, int user)
    {
        if (_locks[num] != -1)
            return false;
        if (hasLockedAncestors(num))
            return false;
        if (!hasLockedDescendants(num))
            return false;
        unlockDescendants(num);
        _locks[num] = user;
        return true;
    }

private:
    bool hasLockedAncestors(int num)
    {
        while (num != -1)
        {
            if (_locks[num] != -1)
                return true;
            num = _parent[num];
        }
        return false;
    }

    bool hasLockedDescendants(size_t num)
    {
        if (_locks[num] != -1)
            return true;
        for (const size_t child : _children[num])
        {
            if (hasLockedDescendants(child))
                return true;
        }
        return false;
    }

    void unlockDescendants(size_t num)
    {
        _locks[num] = -1;
        for (const size_t child : _children[num])
            unlockDescendants(child);
    }

    std::vector<int> _parent;
    std::vector<std::vector<size_t>> _children;
    std::vector<int> _locks;
};

}

namespace OperationsOnTreeTask
{

TEST(OperationsOnTreeTaskTests, Examples)
{
    LockingTree lockingTree({-1, 0, 0, 1, 1, 2, 2});
    ASSERT_EQ(true, lockingTree.lock(2, 2));
    ASSERT_EQ(false, lockingTree.unlock(2, 3));
    ASSERT_EQ(true, lockingTree.unlock(2, 2));
    ASSERT_EQ(true, lockingTree.lock(4, 5));
    ASSERT_EQ(true, lockingTree.upgrade(0, 1));
    ASSERT_EQ(false , lockingTree.lock(0, 1));
}

TEST(OperationsOnTreeTaskTests, FromWrongAnswers)
{
    LockingTree lockingTree({-1, 4, 0, 2, 5, 0, 4, 8, 2, 4});
    ASSERT_EQ(false, lockingTree.upgrade(9, 22));
    ASSERT_EQ(false, lockingTree.unlock(6, 21));
    ASSERT_EQ(false, lockingTree.unlock(8, 40));
    ASSERT_EQ(false, lockingTree.upgrade(3, 24));
    ASSERT_EQ(false, lockingTree.unlock(3, 24));
    ASSERT_EQ(false, lockingTree.upgrade(6, 17));
    ASSERT_EQ(false, lockingTree.upgrade(4, 42));
    ASSERT_EQ(true, lockingTree.lock(6, 41));
    ASSERT_EQ(false, lockingTree.unlock(5, 49));
    ASSERT_EQ(false, lockingTree.lock(6, 14));
    ASSERT_EQ(false, lockingTree.upgrade(9, 6));
    ASSERT_EQ(false, lockingTree.upgrade(2, 46));
    ASSERT_EQ(true, lockingTree.upgrade(0, 7));
    ASSERT_EQ(false, lockingTree.upgrade(8, 13));
    ASSERT_EQ(false, lockingTree.upgrade(2, 47));
    ASSERT_EQ(false, lockingTree.upgrade(3, 5));
    ASSERT_EQ(true, lockingTree.lock(5, 17));
    ASSERT_EQ(false, lockingTree.upgrade(7, 9));
    ASSERT_EQ(false, lockingTree.lock(5, 32));
    ASSERT_EQ(true, lockingTree.lock(9, 46));
}

}