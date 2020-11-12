#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* reverseKGroup(ListNode* head, int k)
    {
        ListNode* destHead = nullptr;
        ListNode* tail = nullptr;
        ListNode* current = head;
        while (current != nullptr)
        {
            const int groupSize = groupNodes(current, k);
            if (groupSize == k)
            {
                ListNode* newHead;
                ListNode* newTail;
                std::tie(newHead, newTail) = reverseGroup(current, k);
                if (destHead == nullptr)
                    destHead = newHead;
                if (tail != nullptr)
                    tail->next = newHead;
                tail = newTail;
                current = tail->next;
            }
            else
            {
                if (destHead == nullptr)
                    destHead = current;
                current = nullptr;
            }
        }
        return destHead;
    }

private:
    int groupNodes(ListNode* head, int k) const
    {
        int groupSize = 0;
        while (head != nullptr && groupSize < k)
        {
            head = head->next;
            ++groupSize;
        }
        return groupSize;
    }

    // new head, new tail
    std::tuple<ListNode*, ListNode*> reverseGroup(ListNode* head, int k)
    {
        ListNode* newHead = nullptr;
        ListNode* current = head;
        for (int index = 0; index < k; ++index)
        {
            ListNode* next = current->next;
            current->next = newHead;
            newHead = current;
            current = next;
        }
        head->next = current;
        return std::make_tuple(newHead, head);
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace ReverseNodesInKGroupTask
{

TEST(ReverseNodesInKGroupTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({2, 1, 4, 3, 5}, solution.reverseKGroup(createLinkedList({1, 2, 3, 4, 5}, false).get(), 2));
    checkAndDeleteLinkedList({3, 2, 1, 4, 5}, solution.reverseKGroup(createLinkedList({1, 2, 3, 4, 5}, false).get(), 3));
    checkAndDeleteLinkedList({1, 2, 3, 4, 5}, solution.reverseKGroup(createLinkedList({1, 2, 3, 4, 5}, false).get(), 1));
    checkAndDeleteLinkedList({1}, solution.reverseKGroup(createLinkedList({1}, false).get(), 1));
}


}