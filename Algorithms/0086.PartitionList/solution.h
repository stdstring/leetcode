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
    ListNode* partition(ListNode* head, int x)
    {
        ListNode* partition1Head = nullptr;
        ListNode* partition2Head = nullptr;
        ListNode* partition1Current = nullptr;
        ListNode* partition2Current = nullptr;
        ListNode* current = head;
        while (current != nullptr)
        {
            ListNode* next = current->next;
            if (current->val < x)
                addNodeToPartition(partition1Head, partition1Current, current);
            else
                addNodeToPartition(partition2Head, partition2Current, current);
            current = next;
        }
        if (partition1Head == nullptr)
            return partition2Head;
        partition1Current->next = partition2Head;
        return partition1Head;
    }

private:
    void addNodeToPartition(ListNode* &partitionHead, ListNode* &partitionCurrent, ListNode* node)
    {
        if (partitionHead == nullptr)
            partitionHead = node;
        if (partitionCurrent != nullptr)
            partitionCurrent->next = node;
        partitionCurrent = node;
        partitionCurrent->next = nullptr;
    }
};