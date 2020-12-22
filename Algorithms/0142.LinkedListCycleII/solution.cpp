#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    ListNode* detectCycle(ListNode* head) const
    {
        if (head == nullptr || head->next == nullptr)
            return nullptr;
        // find cycle
        ListNode* first = head->next;
        ListNode* second = head->next->next;
        while (first != second)
        {
            if (second == nullptr || second->next == nullptr)
                return nullptr;
            first = first->next;
            second = second->next->next;
        }
        // find cycle start
        first = head;
        while (first != second)
        {
            first = first->next;
            second = second->next;
        }
        return first;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::createLinkedListWithCycle;

namespace LinkedListCycleIITask
{

TEST(LinkedListCycleIITaskTests, Examples)
{
    const Solution solution;
    const std::shared_ptr<ListNode> case1 = createLinkedListWithCycle({3, 2, 0, -4}, 1);
    ASSERT_EQ(2, solution.detectCycle(case1.get())->val);
    const std::shared_ptr<ListNode> case2 = createLinkedListWithCycle({1, 2}, 0);
    ASSERT_EQ(1, solution.detectCycle(case2.get())->val);
    const std::shared_ptr<ListNode> case3 = createLinkedList({1}, true);
    ASSERT_EQ(nullptr, solution.detectCycle(case3.get()));
}

}