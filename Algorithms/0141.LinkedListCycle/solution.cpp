#include "ListNode.h"

#include "gtest/gtest.h"

using CommonDefs::ListNode;

namespace
{

class Solution
{
public:
    bool hasCycle(ListNode *head) const
    {
        if (head == nullptr || head->next == nullptr)
            return false;
        ListNode *first = head;
        ListNode *second = head->next->next;
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

namespace LinkedListCycleTask
{

TEST(ReorderListTaskTests, Examples)
{
    const Solution solution;
    const std::shared_ptr<ListNode> case1Node4 = std::make_shared<ListNode>(-4);
    const std::shared_ptr<ListNode> case1Node3 = std::make_shared<ListNode>(0, case1Node4.get());
    const std::shared_ptr<ListNode> case1Node2 = std::make_shared<ListNode>(2, case1Node3.get());
    const std::shared_ptr<ListNode> case1Node1 = std::make_shared<ListNode>(3, case1Node2.get());
    case1Node4->next = case1Node2.get();
    ASSERT_EQ(true, solution.hasCycle(case1Node1.get()));
    const std::shared_ptr<ListNode> case2Node2 = std::make_shared<ListNode>(2);
    const std::shared_ptr<ListNode> case2Node1 = std::make_shared<ListNode>(1, case2Node2.get());
    case2Node2->next = case2Node1.get();
    ASSERT_EQ(true, solution.hasCycle(case2Node1.get()));
    const std::shared_ptr<ListNode> case3Node1 = std::make_shared<ListNode>(1);
    ASSERT_EQ(false, solution.hasCycle(case3Node1.get()));
}

}