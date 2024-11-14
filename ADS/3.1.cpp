/*
Реализовать очередь с динамическим зацикленным буфером.
Обрабатывать команды push back и pop front.
*/
#include <iostream>
#include <cassert>

using namespace std;

class Queue {
public:
    Queue(int cap) : capacity(cap), size(0), head(0), tail(0) {
        buffer = new int[capacity];
    }

    ~Queue() {
        delete[] buffer;
    }

    Queue(const Queue &other) = delete;
    Queue& operator=(const Queue &other) = delete;

    bool isEmpty() const {
        return size == 0;
    }

    void Enqueue(int data) {
        if (size == capacity) {
            Grow();  
        }
        buffer[tail] = data;
        tail = (tail + 1) % capacity;
        size++;
    }

    int Dequeue() {
        if (isEmpty())
            return -1;

        int tmpData = buffer[head];
        head = (head + 1) % capacity;
        size--;
        return tmpData;
    }

private:
    int* buffer;
    size_t capacity;
    size_t size;
    int head;
    int tail;

    void Grow() {
        int newCapacity = capacity * 2;
        int* newBuffer = new int[newCapacity];
        //cout << "growing...\n";
        for (size_t i = 0; i < size; i++) {
            newBuffer[i] = buffer[(head + i) % capacity];
        }

        head = 0;
        tail = size;
        capacity = newCapacity;

        delete[] buffer;
        buffer = newBuffer;
    }
};

void testLogic() {
    Queue q(1);
    int size = 10;

    assert(q.isEmpty());

    for (int i = 0; i < size; i++) {
        q.Enqueue(i);
    }

    assert(!q.isEmpty());

    for (int i = 0; i < size; i++) {
        int el = q.Dequeue();
        cout << el << ' ';
    }

    assert(q.isEmpty());
}

bool checkCorrectness(int a, int b, Queue& q) {
    if (a == 3) {
        q.Enqueue(b);
    }
    if (a == 2) {
        int data = q.Dequeue();
        if (data != b) {
            return false;
        }
    }
    return true;
}

int main() {
    testLogic();

    int n;
    cin >> n;
    Queue q(3);  

    while (n--) {
        int a, b;
        cin >> a >> b;
        if (!checkCorrectness(a, b, q)) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";

    return 0;
}
