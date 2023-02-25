#include <map>

#include "gtest/gtest.h"

namespace
{

class Allocator
{
public:
    Allocator(int n) : _totalSpace(n), _freeSpace(n)
    {
    }

    int allocate(int size, int mID)
    {
        if (size > _freeSpace)
            return -1;
        auto iterator = _usedBlocks.cbegin();
        for (int start  = 0; start <= _totalSpace - size;)
        {
            if ((iterator == _usedBlocks.cend()) || (start + size <= iterator->first))
            {
                _usedBlocks.emplace(start, BlockData(size, mID));
                _freeSpace -= size;
                return start;
            }
            start = iterator->first + iterator->second.Size;
            ++iterator;
        }
        return -1;
    }

    int free(int mID)
    {
        int size = 0;
        for (auto iterator = _usedBlocks.begin(); iterator != _usedBlocks.end();)
        {
            const auto current = iterator;
            ++iterator;
            if (current->second.Id == mID)
            {
                size += current->second.Size;
                _usedBlocks.erase(current);
            }
        }
        _freeSpace += size;
        return size;
    }

private:
    struct BlockData
    {
        BlockData(int size, int id) : Size(size), Id(id)
        {
        }

        int Size;
        int Id;
    };

    int _totalSpace;
    int _freeSpace;
    std::map<int, BlockData> _usedBlocks;
};

}

namespace DesignMemoryAllocatorTask
{

TEST(DesignMemoryAllocatorTaskTests, Examples)
{
    Allocator allocator(10);
    ASSERT_EQ(0, allocator.allocate(1, 1));
    ASSERT_EQ(1, allocator.allocate(1, 2));
    ASSERT_EQ(2, allocator.allocate(1, 3));
    ASSERT_EQ(1, allocator.free(2));
    ASSERT_EQ(3, allocator.allocate(3, 4));
    ASSERT_EQ(1, allocator.allocate(1, 1));
    ASSERT_EQ(6, allocator.allocate(1, 1));
    ASSERT_EQ(3, allocator.free(1));
    ASSERT_EQ(-1, allocator.allocate(10, 2));
    ASSERT_EQ(0, allocator.free(7));
}

TEST(DesignMemoryAllocatorTaskTests, FromWrongAnswers)
{
    Allocator allocator(50);
    ASSERT_EQ(0, allocator.allocate(12, 6));
    ASSERT_EQ(12, allocator.allocate(28, 16));
    ASSERT_EQ(-1, allocator.allocate(17, 23));
    ASSERT_EQ(-1, allocator.allocate(50, 23));
    ASSERT_EQ(12, allocator.free(6));
    ASSERT_EQ(0, allocator.free(10));
    ASSERT_EQ(0, allocator.free(10));
    ASSERT_EQ(-1, allocator.allocate(16, 8));
    ASSERT_EQ(-1, allocator.allocate(17, 41));
    ASSERT_EQ(-1, allocator.allocate(44, 27));
    ASSERT_EQ(0, allocator.allocate(12, 45));
    ASSERT_EQ(0, allocator.free(33));
    ASSERT_EQ(0, allocator.free(8));
    ASSERT_EQ(28, allocator.free(16));
    ASSERT_EQ(0, allocator.free(23));
    ASSERT_EQ(0, allocator.free(23));
    ASSERT_EQ(0, allocator.free(23));
    ASSERT_EQ(0, allocator.free(29));
    ASSERT_EQ(12, allocator.allocate(38, 32));
    ASSERT_EQ(0, allocator.free(29));
    ASSERT_EQ(0, allocator.free(6));
    ASSERT_EQ(-1, allocator.allocate(40, 11));
    ASSERT_EQ(0, allocator.free(16));
    ASSERT_EQ(-1, allocator.allocate(22, 33));
    ASSERT_EQ(-1, allocator.allocate(27, 5));
    ASSERT_EQ(0, allocator.free(3));
    ASSERT_EQ(0, allocator.free(10));
    ASSERT_EQ(0, allocator.free(29));
    ASSERT_EQ(-1, allocator.allocate(16, 14));
    ASSERT_EQ(-1, allocator.allocate(46, 47));
    ASSERT_EQ(-1, allocator.allocate(48, 9));
    ASSERT_EQ(-1, allocator.allocate(36, 17));
    ASSERT_EQ(0, allocator.free(33));
    ASSERT_EQ(-1, allocator.allocate(14, 24));
    ASSERT_EQ(0, allocator.free(16));
    ASSERT_EQ(0, allocator.free(8));
    ASSERT_EQ(-1, allocator.allocate(2, 50));
    ASSERT_EQ(-1, allocator.allocate(31, 36));
    ASSERT_EQ(-1, allocator.allocate(17, 45));
    ASSERT_EQ(-1, allocator.allocate(46, 31));
    ASSERT_EQ(-1, allocator.allocate(2, 6));
    ASSERT_EQ(-1, allocator.allocate(16, 2));
    ASSERT_EQ(-1, allocator.allocate(39, 30));
    ASSERT_EQ(0, allocator.free(33));
    ASSERT_EQ(12, allocator.free(45));
    ASSERT_EQ(0, allocator.free(30));
    ASSERT_EQ(0, allocator.free(27));
}

}