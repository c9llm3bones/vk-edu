#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
struct defaultComparator {
    bool operator()(const T &a, const T &b) {
        return a < b;
    }
};

template <typename T, typename Comparator=defaultComparator<T>>
size_t medianOfThree(T* arr, size_t l, size_t r, Comparator cmp) {
    size_t mid = l + (r - l) / 2;

    if (cmp(arr[r - 1], arr[l])) swap(arr[l], arr[r - 1]);
    if (cmp(arr[mid], arr[l])) swap(arr[mid], arr[l]);
    if (cmp(arr[r - 1], arr[mid])) swap(arr[mid], arr[r - 1]);

    return mid;
}

template <typename T, typename Comparator=defaultComparator<T>>
size_t partition(T* arr, size_t l, size_t r, Comparator cmp = Comparator()) {
    size_t pivotIdx = medianOfThree(arr, l, r, cmp);
    T pivotValue = arr[pivotIdx];
    swap(arr[pivotIdx], arr[r - 1]);  

    size_t i = l;  
    for (size_t j = l; j < r - 1; ++j) {  
        if (!cmp(pivotValue, arr[j])) {  
            swap(arr[i], arr[j]);
            ++i;
        }
    }
    swap(arr[i], arr[r - 1]);  
    return i;
}

template <typename T, typename Comparator=defaultComparator<T>>
void kthElement(T* arr, size_t size, size_t k, Comparator cmp = Comparator()) {
    size_t l = 0, r = size;
    while (l < r) {
        size_t pivotIdx = partition(arr, l, r, cmp);
        if (pivotIdx == k) {
            return;
        }
        if (k < pivotIdx) {
            r = pivotIdx;
        } else {
            l = pivotIdx + 1;
        }
    }
}

int main() {
    int n;
    cin >> n;
    
    int *arr = new int[n];
    size_t p10 = n / 10;
    size_t p50 = n / 2;
    size_t p90 = n * 9 / 10;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    kthElement(arr, n, p10);
    kthElement(arr, n, p50);
    kthElement(arr, n, p90);

    cout << arr[p10] << '\n';
    cout << arr[p50] << '\n';
    cout << arr[p90];
         
    delete[] arr;
    return 0;
}
