#include <iostream>

class Node {
public:
    Node():identify(0), traffic(0) {}
    Node(int Identify, int Traffic):identify(Identify), traffic(Traffic) {}
    Node(const Node& obj);
    Node& operator=(const Node& obj);
    void init(int id, int traffic);
    int getTraffic() const { return traffic; }
    friend std::ostream & operator<<(std::ostream &out, Node obj);
private:
    int identify;
    int traffic;
};

Node& Node::operator=(const Node& obj) {
    this->identify = obj.identify;
    this->traffic = obj.traffic;
    return *this;
}
void Node::init(int _identify, int _traffic) {
        identify = _identify;
        traffic = _traffic;
    }
Node::Node(const Node& obj) {
    this->identify = obj.identify;
    this->traffic = obj.traffic;
}

std::ostream & operator<<(std::ostream &out, Node obj) {
    out << obj.identify;
    return out;
}

template <class T>
bool isLessDefault(const T& left, const T& right) {
    return left < right;
}

bool isLessTraffic(const Node& left, const Node& right) {
  return left.getTraffic() < right.getTraffic();
}

template<class T>
class MyHeap {
public:
    MyHeap(const T *arr, const int size, bool (*isLess)(const T&, const T&) = isLessDefault);
    MyHeap() = delete;
    MyHeap(const MyHeap&) = delete;
    MyHeap& operator=(const MyHeap&) = delete;
    ~MyHeap();
    T extractMin();
    T getMin() { return heap[0]; };
    void insert(const T& val);
    void print();
private:
    void grow();
    void swap(T *a, T *b);
    void siftUp(int i);
    void siftDown(int i);
    bool (*isLess)(const T&, const T&);
    int heapSize, realSize;
    T *heap;
};

template<class T>
MyHeap<T>::MyHeap(const T *arr, const int size, bool (*isLess)(const T&, const T&)) {
    isLess = isLess;
    heapSize = size;
    realSize = size;
    int i;
    heap = new T[size];
    for (i = 0; i < size; ++i)
        heap[i] = arr[i];
    for (int i = size / 2 - 1; i >= 0; i--)
        siftDown(i);
}

template<class T>
MyHeap<T>::~MyHeap(){
  delete [] heap;
}

template<class T>
void MyHeap<T>::grow() {
    int heapSize = realSize * 2;
    T *newHeap = new T [heapSize];
    for (int i = 0; i < realSize; ++i) {
        newHeap[i] = heap[i];
    }
    delete [] heap;
    heap = newHeap;
}

template<class T>
void MyHeap<T>::insert(const T& val) {
    if (realSize >= heapSize)
        grow();
    heap[realSize++] = val;
    siftUp(realSize - 1);
}

template<class T>
T MyHeap<T>::extractMin() {
    T tmpNode = heap[0];
    heap[0] = heap[--realSize];
    siftDown(0);
    return tmpNode;
}

template<class T>
void MyHeap<T>::siftUp(int i) {
    bool stop = false;
    while (!stop && i > 1) {
        int parent = (i - 1) / 2;
        if(isLess(heap[i], heap[parent])) {
            swap(&heap[i], &heap[parent]);
            i = parent;
        } else {
            stop = true;
        }
    }
}

template<class T>
void MyHeap<T>::siftDown(int i) {
    int j;
    while (2 * i + 1 < realSize) {
        j = -1;
        int left = 2 * i + 1;
        int right = left + 1;
        if (isLess(heap[left], heap[i]))
            j = left;
        if (right < realSize && isLess(heap[right], heap[i]) && (j == -1 || isLess(heap[right], heap[left])))
            j = right;
        if (j == -1) break;
        swap(&heap[i], &heap[j]);
        i = j;
    }
}

template<class T>
void MyHeap<T>::swap(T *a, T *b) {
    T tmp = *a;
    *a = *b;
    *b = tmp;
}

template<class T>
void MyHeap<T>::print() {
    for (int i = 0; i < realSize - 1; ++i)
        std::cout << heap[i] << ' ';
    std::cout << heap[realSize - 1];
}

int main() {
    int n = 0, k = 0, i, id, traffic;
    std:: cin >> n >> k;
    Node* arrayNodes = new Node [n];
    for (i = 0; i < n; ++i) {
        std::cin >> id >> traffic;
        arrayNodes[i].init(id, traffic);
    }
    MyHeap<Node> heap(arrayNodes, k, isLessTraffic);
    for (i = k; i < n; ++i) {
        if (isLessTraffic(heap.getMin(), arrayNodes[i])) {
            heap.extractMin();
            heap.insert(arrayNodes[i]);
        }
    }
    for (i = 0; i < k - 1; ++i) {
            std::cout << heap.extractMin() << ' ';
    }
    std::cout << heap.extractMin();
    delete [] arrayNodes;
    return 0;
}
