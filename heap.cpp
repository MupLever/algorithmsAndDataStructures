#include <iostream>

class Node {
public:
    Node():identify(0), traffic(0) {}
    Node(int Identify, int Traffic):identify(Identify), traffic(Traffic) {}
    Node(const Node& obj);
    void Init(int id, int traffic);
    int getTraffic() const { return this->traffic; }
    friend std::ostream & operator<<(std::ostream &out, Node obj);
private:
    int identify;
    int traffic;
};
void Node::Init(int id, int traffic) {
        identify = id;
        this->traffic = traffic;
    }
Node::Node(const Node& obj) {
    this->identify = obj.identify;
    this->traffic = obj.traffic;
}

std::ostream & operator<<(std::ostream &out, Node obj) {
    out << obj.identify;
    return out;
}

template<class T>
class MyHeap {
public:
    MyHeap(T *arr, int size, int k, bool (*IsMore)(const T&, const T&));
    MyHeap();
    ~MyHeap();
    T extractMax();
    void insert(T val);
    void print();
    void partialSort();
private:
    void grow();
    void swap(T *a, T *b);
    void SiftUp(int i);
    void SiftDown(int i);
    bool isMoreDefault(const T& left, const T& right);
    bool (*isMore)(const T&, const T&);

    int heapSize, realSize, k;
    T *heap;
};

template <class T>
bool isMoreDefault(const T& left, const T& right) {
	return left < right;
}
template<class T>
MyHeap<T>::MyHeap(T *arr, int size, int k, bool (*IsMore)(const T&, const T&)) {
    isMore = IsMore;
    this->k = k;
    this->heapSize = size;
    this->realSize = size;
    int i;
    this->heap = new T[size];
    for (i = 0; i < size; ++i) 
        heap[i] = arr[i];
    for (i = (size >> 1) - 1; i >= 0; --i) {
        SiftDown(i);
    }
}
template<class T>
MyHeap<T>::MyHeap() {
    this->isMore = this->isMoreDefault;
    this->heapSize = 10;
    this->realSize = 0;
    this->k = 10;
    heap = new T[heapSize];
}
template<class T>
MyHeap<T>::~MyHeap(){
  delete [] heap;
}
template<class T>
void MyHeap<T>::grow() {
    int heapSize = realSize * 2;
    T *new_heap = new T [heapSize];
    for (int i = 0; i < realSize; ++i) {
        new_heap[i] = heap[i];
    }
    delete [] heap;
    heap = new_heap;
}
template<class T>
void MyHeap<T>::partialSort() {
    for (int i = 0; i < k; ++i) {
        heap[realSize] = extractMax();
    }
}
template<class T>
void MyHeap<T>::insert(T val) {
    if (realSize >= heapSize)
        grow();
    heap[realSize++] = val;
    SiftUp(realSize - 1);
}

template<class T>
T MyHeap<T>::extractMax() {
    T tmpNode = heap[0];
    heap[0] = heap[--realSize];
    SiftDown(0);
    return tmpNode;
}
template<class T>
void MyHeap<T>::SiftUp(int i) {
    bool stop = false;
    while (!stop && i > 1) {
        int parent = (i - 1) / 2;
        if(isMore(heap[i], heap[parent])) {
            swap(&heap[i], &heap[parent]);
            i = parent;
        } else {
            stop = true;
        }
        
    }
}
template<class T>
void MyHeap<T>::SiftDown(int i) {
    int j;
    while (2 * i + 1 <= realSize) {
        j = -1;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (isMore(heap[left], heap[i])) 
            j = left;
        if (right <= realSize && isMore(heap[right], heap[i]) && (j == -1 || isMore(heap[right], heap[left])))
            j = right;
        if (j == -1) break;
        swap(&heap[i], &heap[j]);
        i = j;
    }
}
template<class T>
void MyHeap<T>::print() {
    for (int i = 0; i < k - 1; ++i)
        std::cout << heap[realSize + i] << ' ';
	std::cout << heap[realSize + k - 1];
}
template<class T>
void MyHeap<T>::swap(T *a, T *b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}
bool isMore(const Node& val1, const Node& val2) {
  return val1.getTraffic() > val2.getTraffic();
}
int main() {
    int n = 0, k = 0, i, id, traffic;
    std:: cin >> n >> k;
    Node* arrayNodes = new Node [n];
    for (i = 0; i < n; ++i) {
        std::cin >> id >> traffic;
        arrayNodes[i].Init(id, traffic);
    }
    MyHeap<Node> heap(arrayNodes, n, k, isMore);
    heap.partialSort();
    heap.print();
    delete [] arrayNodes;
    return 0;
}



/* 
#include <iostream>

class Node {
    public:
    Node():identify(0), traffic(0) {}
    Node(int identify, int traffic) {
        this->identify = identify;
        this->traffic = traffic;
    }
    Node(const Node& obj) {
        this->identify = obj.identify;
        this->traffic = obj.traffic;
    }
    void Init(int id, int traffic) {
        identify = id;
        this->traffic = traffic;
    }
    int getTraffic() const { return this->traffic; }
    friend std::ostream & operator<<(std::ostream &out, Node obj);
private:
    int identify;
    int traffic;
};

std::ostream & operator<<(std::ostream &out, Node obj) {
    out << obj.identify;
    return out;
}

template<class T>
class MyHeap {
public:
    MyHeap(T *arr, int size, bool (*IsMore)(const T&, const T&));
    MyHeap(int size, bool (*IsMore)(const T&, const T&));
    MyHeap();
    ~MyHeap();
    T extractMax();
    void insert(T val);
    void printHeap();
private:
    void grow();
    void swap(T *a, T *b);
    void SiftUp(int i);
    void SiftDown(int i);
    bool isMoreDefault(const T& left, const T& right);
    bool (*isMore)(const T&, const T&);

    int heapSize, realSize;
    T *heap;
};

template <class T>
bool isMoreDefault(const T& left, const T& right) {
	return left < right;
}
template<class T>
MyHeap<T>::MyHeap(T *arr, int size, bool (*IsMore)(const T&, const T&)) {
    isMore = IsMore;
    this->heapSize = size;
    this->realSize = size;
    int i;
    this->heap = new T[size];
    for (i = 0; i < size; ++i) 
        heap[i] = arr[i];
    for (i = (size >> 1) - 1; i >= 0; --i) {
        SiftDown(i);
    }
}
template<class T>
MyHeap<T>::MyHeap() {
    this->isMore = this->isMoreDefault;
    this->heapSize = 10;
    this->realSize = 0;
    heap = new T[heapSize];
}
template<class T>
MyHeap<T>::MyHeap(int size, bool (*IsMore)(const T&, const T&)) {
    isMore = IsMore;
    this->heapSize = size;
    this->realSize = 0;
    heap = new T[heapSize];
}
template<class T>
MyHeap<T>::~MyHeap(){
  delete [] heap;
}
template<class T>
void MyHeap<T>::grow() {
    int heapSize = realSize * 2;
    T *new_heap = new T [heapSize];
    for (int i = 0; i < realSize; ++i) {
        new_heap[i] = heap[i];
    }
    delete [] heap;
    heap = new_heap;
}
template<class T>
void MyHeap<T>::insert(T val){
    if (realSize >= heapSize)
        grow();
    heap[realSize++] = val;
    SiftUp(realSize - 1);

}

template<class T>
T MyHeap<T>::extractMax() {
    T tmpNode = heap[0];
    heap[0] = heap[realSize--];
    SiftDown(0);
    return tmpNode;
}
template<class T>
void MyHeap<T>::SiftUp(int i) {
    bool stop = false;
    while (!stop && i > 1) {
        int parent = (i - 1) / 2;
        if(isMore(heap[i], heap[parent])) {
            swap(&heap[i], &heap[parent]);
            i = parent;
        } else {
            stop = true;
        }
        
    }
}
template<class T>
void MyHeap<T>::SiftDown(int i) {
    int j;
    while (2 * i + 1 <= realSize) {
        j = -1;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (isMore(heap[left], heap[i])) 
            j = left;
        if (right <= realSize && isMore(heap[right], heap[i]) && (j == -1 || isMore(heap[right], heap[left])))
            j = right;
        if (j == -1) break;
        swap(&heap[i], &heap[j]);
        i = j;
    }
}
template<class T>
void MyHeap<T>::printHeap() {
    for (int i = 0; i < realSize; ++i) 
        std::cout << heap[i];
}
template<class T>
void MyHeap<T>::swap(T *a, T *b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}
bool isMore(const Node& val1, const Node& val2) {
  return val1.getTraffic() > val2.getTraffic();
}
int main() {
    int n = 0, k = 0, i, id, traffic;
    std:: cin >> n >> k;
    Node* arrayNodes = new Node [n];
    for (i = 0; i < n; ++i) {
        std::cin >> id >> traffic;
        arrayNodes[i].Init(id, traffic);
    }
    MyHeap<Node> heap(arrayNodes, n, isMore);
    Node* tmpBuffer = new Node [k];
    for (i = k - 1; i >= 0; --i) {
      tmpBuffer[i] = heap.extractMax();
    }
    for (i = 0; i < k - 1; ++i) {
      std::cout<< tmpBuffer[i] << ' ';
    }
    std::cout<< tmpBuffer[k - 1];
    delete [] arrayNodes;
    delete [] tmpBuffer;
    return 0;
}

*/