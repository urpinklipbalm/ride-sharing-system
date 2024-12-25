#ifndef QUEUE_H
#define QUEUE_H

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue();
    void enqueue(T data);
    T dequeue();
    bool isEmpty() const;
};

template <typename T>
Queue<T>::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

template <typename T>
void Queue<T>::enqueue(T data) {
    Node* newNode = new Node(data);
    if (rear) {
        rear->next = newNode;
    } else {
        front = newNode;
    }
    rear = newNode;
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty()) {
        throw std::out_of_range("Queue is empty");
    }
    Node* temp = front;
    T data = front->data;
    front = front->next;
    if (!front) {
        rear = nullptr;
    }
    delete temp;
    return data;
}

template <typename T>
bool Queue<T>::isEmpty() const {
    return front == nullptr;
}

#endif // QUEUE_H