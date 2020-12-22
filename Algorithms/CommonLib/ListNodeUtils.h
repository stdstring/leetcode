#pragma once

#include <memory>
#include <vector>

#include "ListNode.h"

namespace CommonLib
{

template<typename TListNode> void deleteLinkedList(TListNode* root)
{
    TListNode* current = root;
    while (current != nullptr)
    {
        TListNode* next = current->next;
        delete current;
        current = next;
    }
}

template<typename TListNode> std::shared_ptr<TListNode> createLinkedListHolder(TListNode* head, bool withDeleter)
{
    return std::shared_ptr<TListNode>(head, withDeleter ? deleteLinkedList<TListNode> : [](TListNode* root) { /* do nothing */ });
}

std::shared_ptr<ListNode> createLinkedList(std::vector<int> const &source, bool withDeleter);
std::shared_ptr<ListNode> createLinkedListWithCycle(std::vector<int> const &source, size_t cycleStartPos);
std::vector<int> convertLinkedListToVector(ListNode* current);
void checkAndDeleteLinkedList(std::vector<int> const &expectedValues, ListNode *current);

}