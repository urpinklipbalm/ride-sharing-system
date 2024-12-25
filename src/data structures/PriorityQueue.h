#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <algorithm>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void push(T data);
    T pop();
    bool isEmpty() const;
};

template <typename T>
void PriorityQueue<T>::heapifyUp(int index) {
    while (index > 0 && heap[index] > heap[(index - 1) / 2]) {
        std::swap(heap[index], heap[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index) {
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    int largest = index;

    if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
        largest = leftChild;
    }
    if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
        largest = rightChild;
    }
    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapifyDown(largest);
    }
}

template <typename T>
void PriorityQueue<T>::push(T data) {
    heap.push_back(data);
    heapifyUp(heap.size() - 1);
}

template <typename T>
T PriorityQueue<T>::pop() {
    if (isEmpty()) {
        throw std::out_of_range("PriorityQueue is empty");
    }
    T data = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapifyDown(0);
    return data;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const {
    return heap.empty();
}

#endif // PRIORITYQUEUE_H