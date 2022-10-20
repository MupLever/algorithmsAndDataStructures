#include <iostream>
#include <string.h>
#include <assert.h>

template <class T>
bool isLessDefault(const T& left, const T& right) {
	return left < right;
}

class Consumer {
public:
	Consumer(int _inTime, int _outTime) : inTime(_inTime), outTime(_outTime) {}
    void init(int _inTime, int _outTime) {
      inTime = _inTime;
      outTime = _outTime;
    }
    Consumer() : inTime(0), outTime(0) {}
    Consumer(const Consumer& obj) {
        this->inTime = obj.inTime;
        this->outTime = obj.outTime;
    }
    Consumer& operator=(const Consumer& obj) {
        this->inTime = obj.inTime;
        this->outTime = obj.outTime;
      return *this;
    }
    int getInTime() const { return inTime; }
    int getOutTime() const { return outTime; }
private:
	int inTime;
	int outTime;
};

bool isLessIn(const Consumer& left, const Consumer& right) {
	return left.getInTime() < right.getInTime();
}

bool isLessOut(const Consumer& left, const Consumer& right) {
	return left.getOutTime() < right.getOutTime();
}

template <class T>
T* growBuffer(T* array, int& bufSize) {
	T* newArr = new T[(bufSize << 1)];
	memcpy(newArr, array, bufSize * sizeof(T));
	delete[] array;
	bufSize =  bufSize << 1;
	return newArr;
}

template <class T>
void merge(T* leftArr, int leftArrSize, T* rightArr, int rightArrSize, T* resultArr, bool (isLess)(const T&, const T&)) {
int i = 0; int j = 0;
    for (; i < leftArrSize && j < rightArrSize;){
        if (isLess(leftArr[i], rightArr[j])) {
            resultArr[i + j] = leftArr[i];
            ++i;
        } else {
            resultArr[i + j] = rightArr[j];
            ++j;
        }
    }
    if (i == leftArrSize){
        for (;j < rightArrSize; ++j) {
            resultArr[i+j] = rightArr[j];
        }
    } else {
        for (;i < leftArrSize; ++i) {
            resultArr[i+j] = leftArr[i];
        }
    }
}

template <class T>
void mergeSort(T* array, int arraySize, bool (isLess)(const T&, const T&) = isLessDefault) {
	if (arraySize == 1)
		return;
	int leftSize = arraySize >> 1;
	int rightSize = arraySize - leftSize;
	mergeSort(array, leftSize, isLess);
	mergeSort(array + leftSize, rightSize, isLess);
	T* tmpArr = new T[arraySize];
	merge(array, leftSize, array + leftSize, rightSize, tmpArr, isLess);
	memcpy(array, tmpArr, arraySize * sizeof(T));
	delete[] tmpArr;
}

Consumer* withoutRepeatOut(Consumer* srcArr, int srcSize, Consumer* dstArr, int& dstSize, int& dstBuf) {
	for (int i = 0; i < srcSize - 1; i++) {
		if (srcArr[i].getOutTime() != srcArr[i + 1].getOutTime()) {
			if (dstSize == dstBuf)
				dstArr = growBuffer(dstArr, dstBuf);
			dstArr[dstSize++] = srcArr[i];
		}
	}
	dstArr[dstSize++] = srcArr[srcSize-1];
	return dstArr;
}

int countAdds(Consumer* array, int size) {
	int lastAdd = array[0].getOutTime();
	int preLastAdd = array[0].getOutTime() - 1;
	int cnt = 2;

	for (int i = 1; i < size; i++)
		if (array[i].getInTime() <= lastAdd) {
			if (array[i].getInTime() > preLastAdd) {
				preLastAdd = lastAdd;countAdds
				lastAdd = array[i].getOutTime();
				++cnt;
			}
		}
		else {
			preLastAdd = array[i].getOutTime() - 1;
			lastAdd = array[i].getOutTime();
			cnt += 2;
		}
	return cnt;
}

int main() {
	int n = 0;
	int in = 0, out = 0;
	std::cin >> n;
	Consumer* array = new Consumer[n];
	for (int i = 0; i < n; i++) {
		std::cin >> in >> out;
		array[i].init(in, out);
	}

	mergeSort(array, n, isLessIn);
	int newBuf = 4;
	Consumer* newArr = new Consumer[newBuf];
	int newSize = 0;
	newArr = withoutRepeatOut(array, n, newArr, newSize, newBuf);

	mergeSort(newArr, newSize, isLessOut);
	std::cout << countAdds(newArr, newSize);

	delete[] array;
	delete[] newArr;
	return 0;
}