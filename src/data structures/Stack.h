#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };
    Node* top;

public:
    Stack() : top(nullptr) {}
    ~Stack();
    void push(T data);
    T pop();
    bool isEmpty() const;
};

template <typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::push(T data) {
    Node* newNode = new Node(data);
    newNode->next = top;
    top = newNode;
}

template <typename T>
T Stack<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("Stack is empty");
    }
    Node* temp = top;
    T data = top->data;
    top = top->next;
    delete temp;
    return data;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return top == nullptr;
}

#endif // STACK_H