#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include "dequeexception.h"

struct Node{
    int value;
    Node* prev;
    Node* next;
};

class Deque{
public:
    Deque();
    ~Deque();
    bool Empty();
    unsigned int Length();

    void PushFront(int);
    void PushBack(int);

    int PopBack();
    int PopFront();

    void Clear();


    class DequeIterator: public std::iterator<std::bidirectional_iterator_tag, int>{
        friend class Deque;
    private:
        DequeIterator(Node*);

    public:

        ~DequeIterator();

        const int& operator*() const;

        bool operator== (const DequeIterator& it) const;
        bool operator!= (const DequeIterator& it) const;

        DequeIterator& operator++();
        DequeIterator operator++(int);
        DequeIterator& operator--();
        DequeIterator operator--(int);

        Node* _ptr;
    };

    DequeIterator begin();
    DequeIterator end();

    DequeIterator LeftFindItem(int);
    DequeIterator RightFindItem(int);

    void LeftRemoveItem(DequeIterator);
    void InsertItem(DequeIterator, int);

private:
    Node* _CreateNode(int);
    void _DeleteNode(Node*);
    void _AddFirstNode(int);
    int _PopLastItem();

private:
    unsigned int _size;
    Node* _begin;
    Node* _end;
};

#endif // DEQUE_H
