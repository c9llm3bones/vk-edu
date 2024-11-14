#include <iostream>

using namespace std;

template <typename T>
struct defaultComparator {
    bool operator()(const T &a, const T &b) {
        return a < b;
    }
};

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
        }
        else {
            l = pivotIdx + 1;
        }
    }
    return;
}

template <typename T, typename Comparator=defaultComparator<T>>
size_t partition(T* arr, size_t l, size_t r, Comparator cmp = Comparator()) {
    size_t pivotIdx = l + (r - l) / 2;
    swap(arr[pivotIdx], arr[r-1]);
    size_t i = l, j = r-1;

    while (i < j) {
        for (; cmp(arr[i], arr[r-1]); i++);
        
        while (!cmp(arr[j], arr[r-1])) {
            j--;
        }  

        if (i < j) {
            swap(arr[j], arr[i]);
            i++;
            j--;
        }
    }

    swap(arr[i], arr[r-1]);
    return i;
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
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << '\n' << arr[p10];
    cout << '\n' << arr[p50];
    cout << '\n' << arr[p90];
         
    delete[] arr;
    return 0;
}