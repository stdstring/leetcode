#include "ListNode.h"

#include "gtest/gtest.h"

using CommonDefs::ListNode;

namespace
{

class Solution
{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) const
    {
        ListNode *dest = nullptr;
        ListNode *current = nullptr;
        bool carry = false;
        while (l1 != nullptr || l2 != nullptr)
        {
            int value = (l1 != nullptr ? l1->val : 0) + (l2 != nullptr ? l2->val : 0) + (carry ? 1 : 0);
            if (value > 9)
            {
                value %= 10;
                carry = true;
            }
            else
                carry = false;
            if (current == nullptr)
                dest = current = new ListNode(value);
            else
            {
                current->next = new ListNode(value);
                current = current->next;
            }
            l1 = l1 != nullptr ? l1->next : nullptr;
            l2 = l2 != nullptr ? l2->next : nullptr;
        }
        if (carry)
            current->next = new ListNode(1);
        return dest;
    }
};

}

using CommonDefs::createLinkedList;
using CommonDefs::checkAndDeleteLinkedList;

namespace AddTwoNumbersTask
{

TEST(AddTwoNumbersTaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList(std::vector<int>({7, 0, 8}), solution.addTwoNumbers(createLinkedList({2, 4, 3}, true).get(), createLinkedList({5, 6, 4}, true).get()));
}

}