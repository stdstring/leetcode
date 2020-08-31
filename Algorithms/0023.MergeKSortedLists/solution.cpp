#include <queue>
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
    ListNode* mergeKLists(std::vector<ListNode*> const &lists)
    {
        auto comp = [](ListNode* left, ListNode* right){ return left->val > right->val; };
        std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(comp)> queue(comp);
        for (ListNode* head : lists)
        {
            while (head != nullptr)
            {
                queue.push(head);
                head = head->next;
            }
        }
        ListNode* head = nullptr;
        ListNode* current = nullptr;
        while (!queue.empty())
        {
            if (current == nullptr)
                head = current = queue.top();
            else
            {
                current->next = queue.top();
                current = current->next;
            }
            queue.pop();
        }
        if (current != nullptr)
            current->next = nullptr;
        return head;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace MergeKSortedListsTask
{

TEST(ReorderListTaskTests, Examples)
{
    Solution solution;
    checkAndDeleteLinkedList({1, 1, 2, 3, 4, 4, 5, 6}, solution.mergeKLists({createLinkedList({1, 4, 5}, false).get(),
                                                                             createLinkedList({1, 3, 4}, false).get(),
                                                                             createLinkedList({2, 6}, false).get()}));
}

TEST(ReorderListTaskTests, FromWrongAnswers)
{
    Solution solution;
    checkAndDeleteLinkedList({}, solution.mergeKLists({}));
    checkAndDeleteLinkedList({}, solution.mergeKLists({nullptr}));
}

}