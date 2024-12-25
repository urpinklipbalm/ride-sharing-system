#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(T data) : data(data), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    ~DoublyLinkedList();
    void insertFront(T data);
    void insertBack(T data);
    void remove(T data);
    bool search(T data) const;
};

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void DoublyLinkedList<T>::insertFront(T data) {
    Node* newNode = new Node(data);
    if (head) {
        head->prev = newNode;
        newNode->next = head;
    } else {
        tail = newNode;
    }
    head = newNode;
}

template <typename T>
void DoublyLinkedList<T>::insertBack(T data) {
    Node* newNode = new Node(data);
    if (tail) {
        tail->next = newNode;
        newNode->prev = tail;
    } else {
        head = newNode;
    }
    tail = newNode;
}

template <typename T>
void DoublyLinkedList<T>::remove(T data) {
    Node* current = head;
    while (current && current->data != data) {
        current = current->next;
    }
    if (current) {
        if (current->prev) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        if (current->next) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        delete current;
    }
}

template <typename T>
bool DoublyLinkedList<T>::search(T data) const {
    Node* current = head;
    while (current) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

#endif // DOUBLYLINKEDLIST_H