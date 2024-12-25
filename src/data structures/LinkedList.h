#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };
    Node* head;

public:
    LinkedList() : head(nullptr) {}
    ~LinkedList();
    void insert(T data);
    void remove(T data);
    bool search(T data) const;
};

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::insert(T data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
}

template <typename T>
void LinkedList<T>::remove(T data) {
    Node* current = head;
    Node* previous = nullptr;
    while (current && current->data != data) {
        previous = current;
        current = current->next;
    }
    if (current) {
        if (previous) {
            previous->next = current->next;
        } else {
            head = current->next;
        }
        delete current;
    }
}

template <typename T>
bool LinkedList<T>::search(T data) const {
    Node* current = head;
    while (current) {
        if (current->data == data) {
            return true;
        }
        current = current->next;
    }
    return false;
}

#endif // LINKEDLIST_H