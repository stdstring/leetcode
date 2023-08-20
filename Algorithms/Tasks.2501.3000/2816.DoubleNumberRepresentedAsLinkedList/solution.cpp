#include <stack>

#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    [[nodiscard]] ListNode* doubleIt(ListNode* head) const
    {
        std::stack<ListNode*> nodes;
        while (head != nullptr)
        {
            nodes.push(head);
            head = head->next;
        }
        ListNode* result = nullptr;
        int carry = 0;
        while (!nodes.empty())
        {
            const int value = 2 * nodes.top()->val + carry;
            result = new ListNode(value % 10, result);
            carry = value / 10;
            nodes.pop();
        }
        if (carry > 0)
            result = new ListNode(carry, result);
        return result;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace DoubleNumberRepresentedAsLinkedListTask
{

TEST(DoubleNumberRepresentedAsLinkedListTaskTests, Examples)
{
    constexpr Solution solution;
    checkAndDeleteLinkedList({3, 7, 8}, solution.doubleIt(createLinkedList({1, 8, 9}, true).get()));
    checkAndDeleteLinkedList({1, 9, 9, 8}, solution.doubleIt(createLinkedList({9, 9, 9}, true).get()));
}

}