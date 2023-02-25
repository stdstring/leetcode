#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    bool hasCycle(ListNode* head) const
    {
        if (head == nullptr || head->next == nullptr)
            return false;
        ListNode* first = head;
        ListNode* second = head->next->next;
        while (first != second)
        {
            if (second == nullptr || second->next == nullptr)
                return false;
            first = first->next;
            second = second->next->next;
        }
        return true;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::createLinkedListWithCycle;

namespace LinkedListCycleTask
{

TEST(ReorderListTaskTests, Examples)
{
    const Solution solution;
    ASSERT_TRUE(solution.hasCycle(createLinkedListWithCycle({3, 2, 0, -4}, 1).get()));
    ASSERT_TRUE(solution.hasCycle(createLinkedListWithCycle({1, 2}, 0).get()));
    ASSERT_FALSE(solution.hasCycle(createLinkedList({1}, true).get()));
}

}