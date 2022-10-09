/* Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. 
Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, 
равного или превосходящего B[i]: A[k] >= B[i].
Если такого элемента нет, выведите n. Время работы поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.
*/
#include <iostream>

using namespace std;

template<typename T>
int BinarySearch(T *arr, int length, int lgr, int rgr, T code) {
    int result = -1;
    int idx = (rgr + lgr) >> 1;
    while (rgr - lgr >= 0) {
        if (code <= arr[idx]) {
            result = idx;
            rgr = idx - 1;
        } else {
            lgr = idx + 1;
        }
        idx = (rgr + lgr) >> 1;
    }
    return result;
}

template<typename T>
int ExpSearch(T *arr, int length, T code) {
    int rgr = 1;
    while (rgr < length && arr[rgr] < code) {
        rgr = rgr << 1;
    }
    if (rgr > length - 1)
        rgr = length - 1;
    return BinarySearch(arr, length, (rgr >> 1), rgr  , code);
}
int main() {
    int n = 0, m = 0, i;
    cin >> n >> m;
    int *A_array = new int [n];
    int *B_array = new int [m];
    for (i = 0; i < n; ++i) {
        cin >> A_array[i];
    }
    for (i = 0; i < m; ++i) {
        cin >> B_array[i];
    }
    for (i = 0; i < m - 1; ++i) {
        cout << ExpSearch(A_array, n, B_array[i]) << ' ';
    }
    cout << ExpSearch(A_array, n, B_array[m - 1]);
    delete [] A_array;
    delete [] B_array;
    return 0; 
}
