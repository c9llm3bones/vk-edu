/*
Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n.
Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.
*/

#include <iostream>
 
using namespace std;

void fill_data(int* arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        cin >> arr[i];
    }
}

int find_left_border(int* A, int el, int n) {
    int l = 0, i = 0;

    while (l < n && A[l] < el) {
        l = (1 << i);  
        i++;
    }

    if (l != 0) {
        return min(l >> 1, n - 1); 
    }

     return 0;
}

int bin_search(int* A, int el, int l, int n) {
    int r = min(2 * l, n - 1); 

    while (l < r) {
        int mid = (l + r) / 2;

        if (A[mid] >= el) 
            r = mid;  
        else 
            l = mid + 1;  
        
    }

    return (A[l] >= el) ? l : n;  
}

int main() {
    int n, m;
    cin >> n >> m;

    int* A = new int[n];
    int* B = new int[m];

    fill_data(A, n);
    fill_data(B, m);

    for (size_t i = 0; i < m; i++) {
        int l = find_left_border(A, B[i], n);
        if (l == 0) { 
            
            if (B[i] > A[l]) 
                cout << 1 << ' ';
            else
                cout << 0 << ' ';
            
        }
        else
            cout << bin_search(A, B[i], l, n) << ' ';
    }

    delete[] A;
    delete[] B;

    return 0;
}
