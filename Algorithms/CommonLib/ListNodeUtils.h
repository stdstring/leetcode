#pragma once

#include <functional>
#include <memory>
#include <vector>

#include "ListNode.h"

namespace CommonLib
{

template<typename TListNode> std::shared_ptr<TListNode> createLinkedListHolder(TListNode* head, bool withDeleter)
{
    std::function<void(TListNode*)> deleteLinkedList = [](TListNode* root)
    {
        TListNode* current = root;
        while (current != nullptr)
        {
            TListNode* next = current->next;
            delete current;
            current = next;
        }
    };
    return std::shared_ptr<TListNode>(head, withDeleter ? deleteLinkedList : [](TListNode* root) { /* do nothing */ });
}

std::shared_ptr<ListNode> createLinkedList(std::vector<int> const &source, bool withDeleter);
std::vector<int> convertLinkedListToVector(ListNode* current);
void checkAndDeleteLinkedList(std::vector<int> const &expectedValues, ListNode *current);

}