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
        while ((head != nullptr) && hasDuplicates(head))
        {
            head = removeDuplicates(head);
        }
        if (head == nullptr)
            return head;
        ListNode* prev = head;
        ListNode* current = head->next;
        while (current != nullptr)
        {
            if (hasDuplicates(current))
            {
                prev->next = current = removeDuplicates(current);
            }
            else
            {
                prev = prev->next;
                current = current->next;
            }
        }
        return head;
    }

private:
    bool hasDuplicates(ListNode* current)
    {
        return (current->next != nullptr) && (current->val == current->next->val);
    }

    ListNode* removeDuplicates(ListNode* current)
    {
        int val = current->val;
        while ((current != nullptr) && (current->val == val))
        {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
        return current;
    }
};