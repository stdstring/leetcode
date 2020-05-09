/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode *dest = nullptr;
        ListNode *current = nullptr;
        bool carry = false;
        while ((l1 != nullptr) || (l2 != nullptr))
        {
            int value = (l1 != nullptr ? l1->val : 0) + (l2 != nullptr ? l2->val : 0) + (carry ? 1 : 0);
            if (value > 9)
            {
                value %= 10;
                carry = true;
            }
            else
            {
                carry = false;
            }
            if (current == nullptr)
            {
                dest = current = new ListNode(value);
            }
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