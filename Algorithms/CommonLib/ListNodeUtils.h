#pragma once

#include <memory>
#include <vector>

#include "ListNode.h"

namespace CommonLib
{

std::shared_ptr<ListNode> createLinkedList(std::vector<int> const &source, bool withDeleter);
std::vector<int> convertLinkedListToVector(ListNode* current);
void checkAndDeleteLinkedList(std::vector<int> const &expectedValues, ListNode *current);

}