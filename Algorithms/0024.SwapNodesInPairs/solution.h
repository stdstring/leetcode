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
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr)
            return head;
        if (head->next == nullptr)
            return head;
        ListNode* current = head;
        head = current->next;
        swapNodes(nullptr, current);
        ListNode* prev = current;
        current = current->next;
        while ((current != nullptr) && (current->next != nullptr))
        {
            swapNodes(prev, current);
            prev = current;
            current = current->next;
        }
        return head;
    }

private:
    void swapNodes(ListNode* prev, ListNode* current)
    {
        ListNode* next = current->next;
        current->next = next->next;
        next->next = current;
        if (prev != nullptr)
            prev->next = next;
    }
};