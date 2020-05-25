#include "deque.h"

Deque::Deque(){
    this->_size = 0;
    this->_begin = this->_CreateNode(0);
    this->_end = this->_CreateNode(0);
}

Deque::~Deque(){
    this->Clear();
    this->_DeleteNode(this->_begin);
    this->_DeleteNode(this->_end);
}

bool Deque::Empty(){
    return this->_size == 0;
}

unsigned int Deque::Length(){
    return this->_size;
}

void Deque::PushBack(int value){
    if (this->Empty()){
        this->_AddFirstNode(value);
        return;
    }

    Node * node = this->_CreateNode(value);
    Node * last = this->_end->prev;
    last->next = node;
    node->prev = last;
    node->next = this->_end;
    this->_end->prev = node;
    this->_size++;

}

void Deque::PushFront(int value){
    if (this->Empty()){
        this->_AddFirstNode(value);
        return;
    }

    Node* node = this->_CreateNode(value);
    Node* front = this->_begin->next;
    node->next = front;
    front->prev = node;
    this->_begin->next = node;
    this->_size++;
}

int Deque::PopBack(){
    if (this->Length() == 0){
        throw DequeException(5, "Delete Item from Empty Deque");
    }

    if (this->Length() == 1){
        return this->_PopLastItem();
    }

    Node* last = this->_end->prev;
    this->_end->prev = last->prev;
    this->_end->prev->next = this->_end;

    int value = last->value;
    this->_DeleteNode(last);
    this->_size--;
    return value;
}

int Deque::PopFront(){
    if (this->Length() == 0){
        throw DequeException(5, "Delete Item from Empty Deque");
    }

    if (this->Length() == 1){
        return this->_PopLastItem();
    }

    Node* front = this->_begin->next;
    this->_begin->next = front->next;
    front->next->prev = this->_begin;

    int value = front->value;
    this->_DeleteNode(front);
    this->_size--;
    return value;
}

void Deque::Clear(){
    while (this->_size != 0)
        this->PopFront();
}


Deque::DequeIterator Deque::begin(){
    if (this->Empty())
        throw DequeException(13, "Empty Deque, Iterator not Exist");

    DequeIterator it(this->_begin->next);
    return it;
}

Deque::DequeIterator Deque::end(){
    if (this->Empty())
        throw DequeException(13, "Empty Deque, Iterator not Exist");

    DequeIterator it(this->_end);
    return it;
}

Deque::DequeIterator Deque::LeftFindItem(int value){
    DequeIterator it = this->begin();
    for(; it != this->end(); it++){
        if (*it == value)
            return it;
    }
    return it;
}


Deque::DequeIterator Deque::RightFindItem(int value){
    DequeIterator it = --this->end();
    for(; it != this->begin(); it--){
        if (*it == value)
            return it;
    }
    return it;
}

void Deque::LeftRemoveItem(Deque::DequeIterator find){
    DequeIterator it = this->begin();
    if (find == it){
        this->PopFront();
        return;
    }

    if (find == --this->end()){
        this->PopBack();
        return;
    }

    it++;
    for(; it != this->end(); it++){
        if (it == find){
            Node* prev = it._ptr->prev;
            Node* next = it._ptr->next;
            prev->next = next;
            next->prev = prev;
            this->_size--;
            this->_DeleteNode(it._ptr);

            break;
        }
    }
}

void Deque::InsertItem(DequeIterator insert, int value){
    if (insert == this->begin()){
        this->PushFront(value);
        return;
    }

    
    if (insert == --this->end()){
        this->PushBack(value);
        return;
    }

    Node* node = this->_CreateNode(value);
    Node* prev = insert._ptr->prev;
    Node* next = insert._ptr;
    prev->next = node;
    node->prev = prev;
    node->next = next;
    next->prev = node;
    this->_size++;

}

Node* Deque::_CreateNode(int value){
    try{
        Node* node = new Node();
        node->value = value;
        node->next = nullptr;
        node->prev = nullptr;
        return node;
    }
    catch (std::exception err){
	        
	/*if (node != nullptr) 
		delete node;*/
        throw DequeException(10, "Memory Limit: No Creation Node");
    }

}

void Deque::_DeleteNode(Node* node){
    node->next = nullptr;
    node->prev = nullptr;
    delete node;
}

void Deque::_AddFirstNode(int value){
    Node* node = this->_CreateNode(value);
    this->_begin->next = node;
    node->prev = nullptr;
    node->next = this->_end;
    this->_end->prev = node;
    this->_size++;
}

int Deque::_PopLastItem(){
    Node* node = this->_begin->next;
    this->_begin->next = nullptr;
    this->_end->prev = nullptr;
    this->_size = 0;
    int value = node->value;
    this->_DeleteNode(node);
    return value;
}


//____DequeIterator__________________

Deque::DequeIterator::DequeIterator(Node* node):
_ptr(node){

}

Deque::DequeIterator::~DequeIterator(){
    this->_ptr = nullptr;
}

const int& Deque::DequeIterator::operator*() const{
    if (this->_ptr->next == nullptr)
        throw DequeException(31, "Empty Iterator");

    return this->_ptr->value;
}

bool Deque::DequeIterator::operator== (const DequeIterator& it) const{
    return this->_ptr == it._ptr;
}

bool Deque::DequeIterator::operator!= (const DequeIterator& it) const{
    return !(*this == it);
}

Deque::DequeIterator& Deque::DequeIterator::operator++(){
    if (this->_ptr->next == nullptr)
        throw DequeException(33, "It is Last Iterator");

    this->_ptr = this->_ptr->next;
    return *this;
}

Deque::DequeIterator Deque::DequeIterator::operator++(int){
    if (this->_ptr->next == nullptr)
        throw DequeException(33, "It is Last Iterator");

    this->_ptr = this->_ptr->next;
    return *this;
}

Deque::DequeIterator& Deque::DequeIterator::operator--(){
    if (this->_ptr->prev == nullptr)
        throw DequeException(35, "It is First Iterator");

    this->_ptr = this->_ptr->prev;
    return *this;
}

Deque::DequeIterator Deque::DequeIterator::operator--(int){
    if (this->_ptr->prev == nullptr)
        throw DequeException(35, "It is First Iterator");

    this->_ptr = this->_ptr->prev;
    return *this;
}
