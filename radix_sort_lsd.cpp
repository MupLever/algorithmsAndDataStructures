#include <iostream>
#include <string.h>

class GetKey {
public:
    long long operator()(long long key, int digit) const {
        if (digit)
            key = key >> (digit * 8);
        return static_cast<long long>(key & 255);
    }
};
template<class T>
void sortByKey(T* array, int size, int digit, const GetKey& getKey) {
    int i;
    T max = getKey(array[0], digit);

    for (i = 0; i < size; ++i)
        max = std::max(getKey(array[i], digit), max);

    int arrCountSize = max + 1;
    int *arrCount = new int [arrCountSize];
    memset(arrCount, 0, (arrCountSize) * sizeof(int));

    for (i = 0; i < size; ++i)
        ++arrCount[getKey(array[i], digit)];
  
    for (i = 1; i < arrCountSize; ++i)
        arrCount[i] += arrCount[i - 1];
  
    T* tmpArray = new T[size];
    for (i = size - 1; i >= 0; --i)
        tmpArray[--arrCount[getKey(array[i], digit)]] = array[i];

    for (i = 0; i < size; ++i)
        array[i] = tmpArray[i];
    delete [] arrCount;
    delete [] tmpArray;
}
template<class T>
void RadixSortLsd(T* array, int size, const GetKey& getKey) {
    for (int i = 0; i < 8; ++i)
        sortByKey(array, size, i, getKey);
}

int main() {
    GetKey getKey;
    int size;
    std::cin >> size;
    long long *array = new long long[size];
    for (int i = 0; i < size; ++i)
        std::cin >> array[i];
    RadixSortLsd(array, size, getKey);
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << ' ';
    delete [] array;
    return 0;
}
