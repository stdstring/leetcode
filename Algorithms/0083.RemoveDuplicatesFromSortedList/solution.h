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
class Solution
{
public:
    ListNode* deleteDuplicates(ListNode* head)
    {
        if (head == nullptr)
            return head;
        ListNode *prev = head;
        ListNode *current = head->next;
        while (current != nullptr)
        {
            if (current->val == prev->val)
            {
                prev->next = current->next;
                delete current;
            }
            else
            {
                prev = current;
            }
            current = prev->next;
        }
        return head;
    }
};