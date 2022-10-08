#include <iostream>
using namespace std;

template <typename T>
bool isMoreDefault(const T& left, const T& right) {
	return left > right;
}

template <typename T>
int partition(T* arr, int left, int right, bool(*isMore)(const T&, const T&) = isMoreDefault) {
	int n = right - left + 1;
	if (n > 2)
		swap(arr[rand() % (right - 1) + left], arr[right]);
	int pivot = arr[right];
	int i = 0, j = 0;
	while (j < right) {
		if (!isMore(arr[j], pivot)){
	    	swap(arr[i], arr[j]);
			i++;
		}
    j++;
	}
	swap(arr[right], arr[i]);
	return i;
}

template <class T>
T KStat(T* arr, int l, int r, int k, bool(*isMore)(const T&, const T&) = isMoreDefault) {
	int pivotPos = partition(arr, l, r, isMore);
	while (pivotPos != k) {
		if (k < pivotPos)
			r = pivotPos - 1;
		else
			l = pivotPos + 1;
		pivotPos = partition(arr, l, r, isMore);
	}
	return arr[k];
}

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; ++i)
		cin >> arr[i];
	int perc10 = n / 10;
	int med = n >> 1;
	int perc90 = n - (n + 9) / 10;
	int stat10 = KStat(arr, 0, n - 1, perc10);
	int statMed = KStat(arr, 0, n - 1, med);
	int stat90 = KStat(arr, 0, n - 1, perc90);
	cout << stat10 << '\n' << statMed << '\n' << stat90;
	delete[] arr;
	return 0;
}
