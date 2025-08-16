#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfUnplacedFruits(std::vector<int> const &fruits, std::vector<int> const &baskets) const
    {
        size_t bestSize = calcBestSize(fruits.size());
        std::vector<int> maxTree(2 * bestSize, INT_MIN);
        buildMaxTree(baskets, maxTree, 0, 0, bestSize);
        size_t result = 0;
        for (int fruit : fruits)
        {
            if (maxTree[0] < fruit)
                ++result;
            extractLeftmostBasket(maxTree, 0, fruit);
        }
        return static_cast<int>(result);
    }

private:
    [[nodiscard]] size_t calcBestSize(size_t currentSize) const
    {
        size_t bestSize = 1;
        for (; currentSize > 0; currentSize >>= 1)
            bestSize <<= 1;
        return bestSize;
    }

    void buildMaxTree(std::vector<int> const &source, std::vector<int> &segmentTree, size_t treeIndex, size_t leftIndex, size_t rightIndex) const
    {
        if (leftIndex == rightIndex - 1)
            segmentTree[treeIndex] = leftIndex < source.size() ? source[leftIndex] : INT_MIN;
        else
        {
            size_t middleIndex = (leftIndex + rightIndex) / 2;
            buildMaxTree(source, segmentTree, treeIndex * 2 + 1, leftIndex, middleIndex);
            buildMaxTree(source, segmentTree, treeIndex * 2 + 2, middleIndex, rightIndex);
            segmentTree[treeIndex] = std::max(segmentTree[treeIndex * 2 + 1], segmentTree[treeIndex * 2 + 2]);
        }
    }

    void extractLeftmostBasket(std::vector<int> &segmentTree, size_t treeIndex, int minCapacity) const
    {
        if ((2 * treeIndex + 2) >= segmentTree.size())
        {
            const int basketValue = segmentTree[treeIndex];
            segmentTree[treeIndex] = INT_MIN;
            return;
        }
        const size_t leftChild = treeIndex * 2 + 1;
        const size_t rightChild = treeIndex * 2 + 2;
        extractLeftmostBasket(segmentTree, segmentTree[leftChild] >= minCapacity ? leftChild : rightChild, minCapacity);
        segmentTree[treeIndex] = std::max(segmentTree[leftChild], segmentTree[rightChild]);
    }
};

}

namespace FruitsIntoBaskets3Task
{

TEST(FruitsIntoBaskets3TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numOfUnplacedFruits({4, 2, 5}, {3, 5, 4}));
    ASSERT_EQ(0, solution.numOfUnplacedFruits({3, 6, 1}, {6, 4, 7}));
}

}