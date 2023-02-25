#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* sortList(ListNode* head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        const size_t size = calcSize(head);
        return sortList(head, size);
    }

private:
    ListNode* sortList(ListNode* head, size_t size)
    {
        if (size == 2)
            return sort2(head);
        if (size == 3)
            return sort3(head);
        ListNode* head2 = nullptr;
        splitList(head, size / 2, head2);
        head = sortList(head, size / 2);
        head2 = sortList(head2, size - size / 2);
        return merge(head, head2);
    }

    size_t calcSize(ListNode* head)
    {
        size_t size = 0;
        while (head != nullptr)
        {
            ++size;
            head = head->next;
        }
        return size;
    }

    void splitList(ListNode* head, size_t size, ListNode* &head2)
    {
        ListNode* current = head;
        for (size_t index = 0; index < size - 1; ++index)
            current = current->next;
        head2 = current->next;
        current->next = nullptr;
    }

    ListNode* sort2(ListNode* head)
    {
        ListNode* node1 = head;
        ListNode* node2 = head->next;
        node2->next = nullptr;
        if (node1->val <= node2->val)
            return head;
        node2->next = node1;
        node1->next = nullptr;
        return node2;
    }

    ListNode* sort3(ListNode* head)
    {
        ListNode* node1 = head;
        ListNode* node2 = node1->next;
        ListNode* node3 = node2->next;
        node3->next = nullptr;
        if (node1->val <= node2->val && node1->val <= node3->val)
        {
            node1->next = sort2(node2);
            return node1;
        }
        if (node2->val <= node1->val && node2->val <= node3->val)
        {
            node1->next = node3;
            node2->next = sort2(node1);
            return node2;
        }
        node1->next = node2;
        node3->next = sort2(node1);
        return node3;
    }

    ListNode* merge(ListNode* head1, ListNode* head2)
    {
        ListNode* head = nullptr;
        ListNode* current = nullptr;
        while (head1 != nullptr && head2 != nullptr)
        {
            ListNode* node = nullptr;
            if (head1->val <= head2->val)
            {
                node = head1;
                head1 = head1->next;
            }
            else
            {
                node = head2;
                head2 = head2->next;
            }
            node->next = nullptr;
            if (head == nullptr)
                head = node;
            else
                current->next = node;
            current = node;
        }
        if (head1 != nullptr)
            current->next = head1;
        if (head2 != nullptr)
            current->next = head2;
        return head;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace SortListTask
{

TEST(SortListTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 2, 3, 4}, solution.sortList(createLinkedList({4, 2, 1, 3}, false).get()));
    checkAndDeleteLinkedList({-1, 0, 3, 4, 5}, solution.sortList(createLinkedList({-1, 5, 3, 4, 0}, false).get()));
    ASSERT_EQ(nullptr, solution.sortList(nullptr));
}

}