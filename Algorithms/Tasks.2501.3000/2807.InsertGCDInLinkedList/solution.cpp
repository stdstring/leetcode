#include <numeric>
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
    [[nodiscard]] ListNode* insertGreatestCommonDivisors(ListNode* head) const
    {
        std::stack<ListNode*> nodes;
        while (head != nullptr)
        {
            nodes.emplace(head);
            head = head->next;
        }
        ListNode* result = new ListNode(nodes.top()->val);
        nodes.pop();
        while (!nodes.empty())
        {
            const int gcd = std::gcd(result->val, nodes.top()->val);
            result = new ListNode(gcd, result);
            result = new ListNode(nodes.top()->val, result);
            nodes.pop();
        }
        return result;
    }
};

}

using CommonLib::createLinkedList;
using CommonLib::checkAndDeleteLinkedList;

namespace InsertGCDInLinkedListTask
{

TEST(InsertGCDInLinkedListTaskTests, Examples)
{
    constexpr Solution solution;
    checkAndDeleteLinkedList({18, 6, 6, 2, 10, 1, 3}, solution.insertGreatestCommonDivisors(createLinkedList({18, 6, 10, 3}, true).get()));
    checkAndDeleteLinkedList({7}, solution.insertGreatestCommonDivisors(createLinkedList({7}, true).get()));
}

}