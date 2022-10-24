#include <iostream>

template<class T>
class Queue {
private:
    struct Node {
        Node* next;
        T data;
        Node(const T& _data) : data(_data), next(nullptr) {}
    };
public:
    Queue() : size(0), head(nullptr) {}
    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;
    ~Queue() { clear(); }
    T popFront();
    void pushBack(const T& data);
    void clear();
    bool isEmpty() { return size == 0; }
    int getSize() { return size; }
    int size;
    Node *head;
};

template<class T>
T Queue<T>::popFront() {
    Node *temp = head;
    T resultData = head->data;
    head = head->next;
    --size;
    delete temp;
    return resultData;
}

template<class T>
void Queue<T>::pushBack(const T& data) {
    if (head == nullptr) {
        head = new Node(data);
    } else {
        Node *current = this->head;
        while (current->next != nullptr) {
          current = current->next;
        }
        current->next = new Node(data);
    }
    ++size;
}

template<class T>
void Queue<T>::clear() {
    while (size) {
        popFront();
    }
}

template<class T>
class Stack {
private:
	struct Node {
        Node* next;
        T data;
        Node(const T& _data) : data(_data), next(nullptr) {}
	};
public:
    Stack() : head(nullptr) {}
    ~Stack() { clear(); }
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;
    T pop();
    void push(const T& data);
    void clear();
    bool isEmpty() { return head == nullptr; }
	Node *head;
};


template<class T>
T Stack<T>::pop() {
	Node *temp = head;
    T resultData = head->data;
	head = head->next;
    delete temp;
    return resultData;
}

template<class T>
void Stack<T>::push(const T& data) {
    if (head == nullptr) {
        head = new Node(data);
    } else {
        Node *current = new Node(data);
        current->next = head;
        head = current;
    }
}

template<class T>
void Stack<T>::clear() {
    Node* temp = head;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

bool isMoreDefault(const int& left, const int& right) {
    return left < right;
}

template<class T>
class MyMap {
public:
    MyMap(bool (*isMore)(const T&, const T&) = isMoreDefault);
    MyMap(const MyMap&) = delete;
    MyMap& operator=(const MyMap&) = delete;
    void insert(const T& item);
    void inOrder();
    void preOrder();
    void postOrder();
    void levelOrder();
private:
    struct Node {
        Node(const T _data) : data(_data), left(nullptr), right (nullptr) {}
        Node* left;
        Node* right;
        T data;
    };
    bool (*isMore)(const T&, const T&);
    Node* root;
};


template<class T>
MyMap<T>::MyMap(bool (*IsMore)(const T&, const T&)) {
    isMore = IsMore;
    root = nullptr; 
}

template<class T>
void MyMap<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new Node(data);
    } else {
        Node* node = root;
        while (node->data != data) {
            if (isMore(node->data, data))
                if (node->right == nullptr)
                    node->right = new Node(data);
                else
                    node = node->right;
            else if (node->left == nullptr)
                node->left = new Node(data);
            else
                node = node->left;
        }
    }
}

template<class T>
void MyMap<T>::inOrder() {
  //implement
}

template<class T>
void MyMap<T>::preOrder() {
    Stack<Node*> stack;
    stack.push(root);
    while (!stack.isEmpty()) {
        Node* node = stack.pop();
        std::cout << node->data << std::endl;
        if (node->right != nullptr)
            stack.push(node->right);
        if (node->left != nullptr)
            stack.push(node->left);
    }
}

template<class T>
void MyMap<T>::postOrder() {
  //implement
}

template<class T>
void MyMap<T>::levelOrder() {
    Queue<Node*> queue;
    queue.pushBack(root);
    while (!queue.isEmpty()) {
        Node* node = queue.popFront();
        std::cout << node->data << std::endl;
        if (node->left != nullptr)
            queue.pushBack(node->left);
        if (node->right != nullptr)
            queue.pushBack(node->right);
    }
}

int main() {
    MyMap<int> map;
    map.insert(3);
    map.insert(1);
    map.insert(4);
    map.insert(2);
    map.preOrder();
    map.levelOrder();
    return 0;
}
