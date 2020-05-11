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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *tail = head;
        for (int index = 0; index < n; ++index)
        {
            tail = tail->next;
        }
        if (tail == nullptr)
        {
            ListNode *current = head->next;
            delete head;
            return current;
        }
        tail = tail->next;
        ListNode *prev = head;
        while (tail != nullptr)
        {
            tail = tail->next;
            prev = prev->next;
        }
        ListNode *current = prev->next;
        prev->next = current->next;
        delete current;
        return head;
    }
};