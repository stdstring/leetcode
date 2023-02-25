#include "ListNode.h"
#include "ListNodeUtils.h"

#include "gtest/gtest.h"

using CommonLib::ListNode;

namespace
{

class Solution
{
public:
    bool isPalindrome(ListNode* head) const
    {
        if (head == nullptr)
            return true;
        const size_t length = calcLength(head);
        ListNode* current = head;
        return isPalindrome(current, current->val, 0, length);
    }

private:
    size_t calcLength(ListNode* head) const
    {
        size_t result = 0;
        while (head != nullptr)
        {
            ++result;
            head = head->next;
        }
        return result;
    }

    // TODO (std_string) : think about such impl
    bool isPalindrome(ListNode* &current, int val, size_t firstPartIndex, size_t length) const
    {
        if (firstPartIndex < length /2)
        {
            current = current->next;
            const bool result = isPalindrome(current, current->val, firstPartIndex + 1, length);
            if (!result)
                return false;
            if (current->val != val)
                return false;
            current = current->next;
            return true;
        }
        if (length % 2 == 1)
            current = current->next;
        return true;
    }
};

}

using CommonLib::createLinkedList;

namespace PalindromeLinkedListTask
{

TEST(PalindromeLinkedListTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.isPalindrome(createLinkedList({1, 2}, true).get()));
    ASSERT_EQ(true, solution.isPalindrome(createLinkedList({1, 2, 2, 1}, true).get()));
}

}