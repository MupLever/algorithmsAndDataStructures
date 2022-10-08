#include <iostream>
using namespace std;

template <typename T>
bool isMoreDefault(const T& left, const T& right) {
	return left > right;
}

template <typename T>
int partition(T* arr, int left, int right, bool(*isMore)(const T&, const T&) = isMoreDefault) {
	int length = right - left + 1;
	if (length > 2)
		swap(arr[rand() % (right - 1) + left], arr[right]);
	T pivot = arr[right];
	int i = 0, j = 0;
	while (j < right) {
		if (!isMore(arr[j], pivot))
			swap(arr[i++], arr[j]);
    	++j;
	}
	swap(arr[right], arr[i]);
	return i;
}

template <class T>
T KStat(T* arr, int left, int right, int k, bool(*isMore)(const T&, const T&) = isMoreDefault) {
	int pivotPos = partition(arr, left, right, isMore);
	while (pivotPos != k) {
		if (k < pivotPos)
			right = pivotPos - 1;
		else
			left = pivotPos + 1;
		pivotPos = partition(arr, left, right, isMore);
	}
	return arr[k];
}

int main() {
	int n = 0;
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
