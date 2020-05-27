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
    ListNode* removeElements(ListNode* head, int val)
    {
        // remove from head
        while(head != nullptr && head->val == val)
        {
            ListNode *node = head;
            head = head->next;
            delete node;
        }
        if (head == nullptr)
            return head;
        // remove from body
        ListNode *prev = head;
        while (prev->next != nullptr)
        {
            ListNode *current = prev->next;
            if (current->val == val)
            {
                prev->next = current->next;
                delete current;
            }
            else
                prev = prev->next;
        }
        return head;
    }
};