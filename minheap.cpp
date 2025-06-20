#include <iostream>
#include <climits>
#include <cmath>
#include <cfloat>

class NodeCost {
public:
    int city_index;
    float cost;  // Total cost to reach this city

    // Constructor with parameters
    NodeCost(int city, float cost_val) : city_index(city), cost(cost_val) {}

    // Default constructor (initialize with invalid data)
    NodeCost() : city_index(-1), cost(FLT_MAX) {}

    // Overload the < operator to compare NodeCost objects based on cost
    bool operator<(const NodeCost& other) const {
        return cost < other.cost;  // Min-heap: smaller cost has higher priority
    }

    bool operator>(const NodeCost& other) const {
        return cost > other.cost;  // Min-heap: smaller cost has higher priority
    }
};


class MinHeap {
public:
    NodeCost* heap;
    int size;
    int capacity;

    MinHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new NodeCost[capacity];  // Now works with the default constructor
    }

    ~MinHeap() {
        delete[] heap;
    }

    void swap(int i, int j) {
        NodeCost temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    int parent(int i) {
        return (i - 1) / 2;
    }

    int left(int i) {
        return 2 * i + 1;
    }

    int right(int i) {
        return 2 * i + 2;
    }

    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        
        if (l < size && heap[l] < heap[smallest]) {
            smallest = l;
        }

        if (r < size && heap[r] < heap[smallest]) {
            smallest = r;
        }

        if (smallest != i) {
            swap(i, smallest);
            heapify(smallest);
        }
    }

    void insert(NodeCost n) {
        if (size == capacity) return;  // Cannot insert if heap is full
        
        size++;
        int i = size - 1;
        heap[i] = n;

        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    NodeCost extract_min() {
        if (size <= 0) return NodeCost();  // Return a default invalid NodeCost
        if (size == 1) {
            size--;
            return heap[0];
        }

        NodeCost root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapify(0);

        return root;
    }

    void decrease_key(int i, float new_cost) {
        heap[i].cost = new_cost;
        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(i, parent(i));
            i = parent(i);
        }
    }
    bool empty() {
        return size == 0;
    }
};
