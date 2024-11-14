/*
Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт, и выводит их в порядке возрастания посещаемости.
Количество заходов и идентификаторы пользователей не повторяются.

Требования:

Время работы O(N * logK)
Куча должна быть реализована в виде шаблонного класса.
Решение должно поддерживать передачу функции сравнения снаружи.
Куча должна быть динамической.
*/

#include <iostream>
#include <cassert>

using namespace std;


template <typename T>
class defaultComparator {
    public:
    bool operator()(const T &a, const T &b) {
        return a < b;
    }
};

class pairComp {
    public:
        bool operator()(const pair<int, int> &a,const pair<int, int>& b) {
            return a.second < b.second;
        }

};

template <typename T, typename Comparator = defaultComparator<T>>
class Heap {
    public:
        Heap(size_t capacity, Comparator cmp = Comparator()) : capacity(capacity), size(0), cmp(cmp) {
            buf = new T[capacity];
        }
        Heap() : capacity(0), size(0){};
        Heap(const Heap&)=delete;
        Heap(const Heap&&)=delete;

        ~Heap(){
            delete[] buf;
        }

        const T& top() const {
            assert(size != 0);
            return buf[0];
        }
        
        void pop();
        void push(const T& data);
        void printHeap();
   
    private:
        void siftDown(size_t i);
        void siftUp(size_t i);
        T *buf;
        void grow();
        size_t capacity;
        size_t size;
        Comparator cmp;
};

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftDown(size_t i) {
    size_t left = 2 * i + 1, right = 2 * i + 2, minIdx = i;

    if (left < size && cmp(buf[left], buf[i])) {
        minIdx = left;
    }
    if (right < size && cmp(buf[right], buf[minIdx])) {
        minIdx = right;
    }

    if(minIdx != i) {
        swap(buf[i], buf[minIdx]);
        siftDown(minIdx);
    }
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::grow() {
    capacity *= 2;
    T* newBuf = new T[capacity];

    for (size_t i = 0; i < size; i++) {
        newBuf[i] = buf[i];
    }

    delete[] buf;
    buf = newBuf;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::siftUp(size_t i) {
    while(i) {
        size_t parent = (i -  1) / 2;
        if (!cmp(buf[i], buf[parent])) {
            return;
        }

        swap(buf[i], buf[parent]);
        i = parent;
    }

    return;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::push(const T& data) {
    if (size == capacity) {
        if (!cmp(buf[0], data))
            return;
        pop();
    }
    
    buf[size] = data;   
    siftUp(size);
    size++;
    return;
}

template <typename T, typename Comparator>
void Heap<T, Comparator>::pop() {
    assert(size > 0);
    swap(buf[0], buf[size-1]);
    size--;
    siftDown(0);
    return;
}

int main() {

    int n, k;
    cin >> n >> k;

    Heap<pair<int, int>, pairComp> heap(k);
   
    while(n--) {
        pair<int, int> p;
        cin >> p.first >> p.second;
        heap.push(p);
    }

    while(k--) {
        pair<int, int> el = heap.top();
        heap.pop();
        cout << el.first << ' ';
    }

    return 0;
}