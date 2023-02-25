#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    int getDecimalValue(ListNode* head) const
    {
        int value = 0;
        while (head != nullptr)
        {
            value = value * 2 + head->val;
            head = head->next;
        }
        return value;
    }
};

}

using CommonLib::createLinkedList;

namespace ConvertBinNumberInLinkedListToIntTask
{

TEST(ConvertBinNumberInLinkedListToIntTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.getDecimalValue(createLinkedList({1, 0, 1}, true).get()));
    ASSERT_EQ(0, solution.getDecimalValue(createLinkedList({0}, true).get()));
    ASSERT_EQ(1, solution.getDecimalValue(createLinkedList({1}, true).get()));
    ASSERT_EQ(18880, solution.getDecimalValue(createLinkedList({1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, true).get()));
    ASSERT_EQ(0, solution.getDecimalValue(createLinkedList({0, 0}, true).get()));
}

}