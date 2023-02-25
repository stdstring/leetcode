#include <vector>

#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> spiralMatrix(int m, int n, ListNode* head) const
    {
        std::vector<std::vector<int>> matrix(m, std::vector<int>(n, -1));
        const std::vector<std::pair<int, int>> directions({{0, 1}, {1, 0}, {0, -1}, {-1, 0}});
        int row = 0;
        int column = 0;
        size_t directionIndex = 0;
        while (head != nullptr)
        {
            matrix[row][column] = head->val;
            row += directions[directionIndex].first;
            column += directions[directionIndex].second;
            if ((row < 0) || (column < 0) || (row == m) || (column == n) || (matrix[row][column] != -1))
            {
                row -= directions[directionIndex].first;
                column -= directions[directionIndex].second;
                directionIndex = (directionIndex + 1) % directions.size();
                row += directions[directionIndex].first;
                column += directions[directionIndex].second;
            }
            head = head->next;
        }
        return matrix;
    }
};

}

using CommonLib::createLinkedList;

namespace SpiralMatrixIVTask
{

TEST(DeleteMiddleNodeOfLinkedListTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 0, 2, 6, 8}, {5, 0, -1, -1, 1}, {5, 2, 4, 9, 7}}),
              solution.spiralMatrix(3, 5, createLinkedList({3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0}, true).get()));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 1, 2, -1}}), solution.spiralMatrix(1, 4, createLinkedList({0, 1, 2}, true).get()));
}

}