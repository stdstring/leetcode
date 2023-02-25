#include <algorithm>
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
    int pairSum(ListNode* head) const
    {
        // prepare half data
        std::stack<int> firstHalfNumbers;
        ListNode* singlePointer = head;
        ListNode* doublePointer = head;
        while (doublePointer != nullptr)
        {
            firstHalfNumbers.push(singlePointer->val);
            singlePointer = singlePointer->next;
            doublePointer = doublePointer->next->next;
        }
        // calc maximum twin sum
        int maxTwinSum = INT_MIN;
        while (singlePointer != nullptr)
        {
            maxTwinSum = std::max(maxTwinSum, firstHalfNumbers.top() + singlePointer->val);
            firstHalfNumbers.pop();
            singlePointer = singlePointer->next;
        }
        return maxTwinSum;
    }
};

}

using CommonLib::createLinkedList;

namespace MaxTwinSumOfLinkedListTask
{

TEST(MaxTwinSumOfLinkedListTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.pairSum(createLinkedList({5, 4, 2, 1}, true).get()));
    ASSERT_EQ(7, solution.pairSum(createLinkedList({4, 2, 2, 3}, true).get()));
    ASSERT_EQ(100001, solution.pairSum(createLinkedList({1, 100000}, true).get()));
}

}