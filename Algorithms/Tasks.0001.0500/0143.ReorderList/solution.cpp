#include <memory>
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
    void reorderList(ListNode* head)
    {
        if (head == nullptr)
            return;
        std::vector<ListNode*> nodes;
        ListNode* current = head;
        while (current != nullptr)
        {
            nodes.push_back(current);
            current = current->next;
        }
        size_t front = 0;
        size_t back = nodes.size() - 1;
        while (front < back)
        {
            nodes[front++]->next = nodes[back];
            nodes[back--]->next = nodes[front];
        }
        nodes[front]->next = nullptr;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace ReorderListTask
{

TEST(ReorderListTaskTests, Examples)
{
    Solution solution;
    const std::shared_ptr<ListNode> head1(createLinkedList({1, 2, 3, 4}, false));
    solution.reorderList(head1.get());
    checkAndDeleteLinkedList({1, 4, 2, 3}, head1.get());
    const std::shared_ptr<ListNode> head2(createLinkedList({1, 2, 3, 4, 5}, false));
    solution.reorderList(head2.get());
    checkAndDeleteLinkedList({1, 5, 2, 4, 3}, head2.get());
}

TEST(ReorderListTaskTests, FromWrongAnswers)
{
    Solution solution;
    ASSERT_NO_THROW(solution.reorderList(nullptr));
}

}