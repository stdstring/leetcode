#include "gtest/gtest.h"

namespace
{

class MyLinkedList
{
public:
    // Initialize your data structure here.
    MyLinkedList();

    // Destructor
    ~MyLinkedList();

    MyLinkedList(MyLinkedList const&) = delete;
    MyLinkedList(MyLinkedList&&) = delete;
    MyLinkedList& operator= (MyLinkedList const&) = delete;
    MyLinkedList& operator= (MyLinkedList&&) = delete;


    // Get the value of the index-th node in the linked list. If the index is invalid, return -1.
    int get(int index) const;

    // Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list.
    void addAtHead(int val);

    // Append a node of value val to the last element of the linked list.
    void addAtTail(int val);

    // Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list.
    // If index is greater than the length, the node will not be inserted.
    void addAtIndex(int index, int val);

    // Delete the index-th node in the linked list, if the index is valid.
    void deleteAtIndex(int index);

private:
    struct Node
    {
        Node(int val) : value(val), next(nullptr) {}

        int value;
        Node* next;
    };

    Node* _head;
    int _size;
};

MyLinkedList::MyLinkedList() : _head(nullptr), _size(0)
{
}

MyLinkedList::~MyLinkedList()
{
    Node* current = _head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

int MyLinkedList::get(int index) const
{
    if (index >= _size)
        return -1;
    Node* current = _head;
    for (int pos = 0; pos < index; ++pos)
        current = current->next;
    return current->value;
}

void MyLinkedList::addAtHead(int val)
{
    Node* newNode = new Node(val);
    newNode->next = _head;
    _head = newNode;
    ++_size;
}

void MyLinkedList::addAtTail(int val)
{
    Node* newNode = new Node(val);
    if (_head == nullptr)
        _head = newNode;
    else
    {
        Node* current = _head;
        while (current->next != nullptr)
            current = current->next;
        current->next = newNode;
    }
    ++_size;
}

void MyLinkedList::addAtIndex(int index, int val)
{
    if (index > _size)
        return;
    if (index == _size)
        addAtTail(val);
    else if (index == 0)
    {
        Node* newNode = new Node(val);
        newNode->next = _head;
        _head = newNode;
        ++_size;
    }
    else
    {
        Node* prev = _head;
        for (int pos = 0; pos < index - 1; ++pos)
            prev = prev->next;
        Node* newNode = new Node(val);
        newNode->next = prev->next;
        prev->next = newNode;
        ++_size;
    }
}

void MyLinkedList::deleteAtIndex(int index)
{
    if (index >= _size)
        return;
    if (index == 0)
    {
        Node* head = _head;
        _head = head->next;
        delete head;
    }
    else
    {
        Node* prev = _head;
        for (int pos = 0; pos < index - 1; ++pos)
            prev = prev->next;
        Node* current = prev->next;
        prev->next = current->next;
        delete current;
    }
    --_size;
}

}

namespace DesignLinkedListTask
{

TEST(DesignLinkedListTaskTests, Examples)
{
    MyLinkedList linkedList;
    ASSERT_NO_THROW(linkedList.addAtHead(1));
    ASSERT_NO_THROW(linkedList.addAtTail(3));
    ASSERT_NO_THROW(linkedList.addAtIndex(1, 2));
    ASSERT_EQ(2, linkedList.get(1));
    ASSERT_NO_THROW(linkedList.deleteAtIndex(1));
    ASSERT_EQ(3, linkedList.get(1));
}

TEST(DesignLinkedListTaskTests, FromWrongAnswers)
{
    MyLinkedList linkedList;
    ASSERT_NO_THROW(linkedList.addAtHead(7));
    ASSERT_NO_THROW(linkedList.addAtHead(2));
    ASSERT_NO_THROW(linkedList.addAtHead(1));
    ASSERT_NO_THROW(linkedList.addAtIndex(3, 0));
    ASSERT_NO_THROW(linkedList.deleteAtIndex(2));
    ASSERT_NO_THROW(linkedList.addAtHead(6));
    ASSERT_NO_THROW(linkedList.addAtTail(4));
    ASSERT_EQ(4, linkedList.get(4));
    ASSERT_NO_THROW(linkedList.addAtHead(4));
    ASSERT_NO_THROW(linkedList.addAtIndex(5, 0));
    ASSERT_NO_THROW(linkedList.addAtHead(6));
}

}