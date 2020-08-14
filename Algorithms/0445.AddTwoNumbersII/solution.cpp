#include <vector>

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
        std::vector<int> values1;
        fillValues(l1, values1);
        std::vector<int> values2;
        fillValues(l2, values2);
        // addition
        std::vector<int> dest;
        int carry = 0;
        for (size_t index = 0; index < values1.size() || index < values2.size(); ++index)
        {
            const int value1 = index < values1.size() ? values1[values1.size() - 1 - index] : 0;
            const int value2 = index < values2.size() ? values2[values2.size() - 1 - index] : 0;
            const int sum = value1 + value2 + carry;
            dest.push_back(sum % 10);
            carry = sum / 10;
        }
        if (carry > 0)
            dest.push_back(carry);
        // convert to linked list
        ListNode* resultHead = nullptr;
        for (int digit : dest)
            resultHead = new ListNode(digit, resultHead);
        return resultHead;
    }

private:
    void fillValues(ListNode* head, std::vector<int> &values) const
    {
        while (head != nullptr)
        {
            values.push_back(head->val);
            head = head->next;
        }
    }
};

}

using CommonDefs::createLinkedList;
using CommonDefs::checkAndDeleteLinkedList;

namespace AddTwoNumbersIITask
{

TEST(AddTwoNumbersIITaskTests, Examples)
{
    const Solution solution;
    checkAndDeleteLinkedList({7, 8, 0, 7}, solution.addTwoNumbers(createLinkedList({7, 2, 4, 3}, true).get(), createLinkedList({5, 6, 4}, true).get()));
}

}