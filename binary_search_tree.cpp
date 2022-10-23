#include <iostream>
using namespace std;

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
    template<class T>
    class Node {
    public:
    Node(T data = T(), Node *left = nullptr, Node *right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
    }
    Node(const Node& obj) = delete;
    Node& operator=(const Node& obj) = delete;
        Node* left;
        Node* right;
        T data;
    };
    bool (*isMore)(const T&, const T&);
    Node<T>* root;
    
};


template<class T>
MyMap<T>::MyMap(bool (*IsMore)(const T&, const T&)) {
  isMore = IsMore;
  root = nullptr;
}


template<class T>
void MyMap<T>::insert(const T& item) {
  if (root == nullptr) {
    root = new Node<T>(item);
  } else {
    Node<T>* node = root;
    while (node->item != item) {
        if (isMore(item, node->item))
            if (node->right == nullptr)
                node->right = new Node<T>(item);
            else
                node = node->right;
        else
            if (node->left == nullptr)
                node->left = new Node<T>(item);
            else
                node = node->left;
    }
  }
}

template<class T>
void MyMap<T>::inOrder() {
    if (root != nullptr){
        inOrder(root->left);
        std::cout << root->item;
        inOrder(root->right);
    }
}

template<class T>
void MyMap<T>::preOrder() {
    if (root != nullptr) {
        std::cout << root->item;
        preOrder(root->left);
        preOrder(root->right);
    }
}

template<class T>
void MyMap<T>::postOrder() {
    if (root != nullptr) {
        postOrder(root->right);
        postOrder(root->left);
        std::cout << root->item;
    }
}

template<class T>
void MyMap<T>::levelOrder() {
    Queue<Node<int>> queue;
    queue.push_back(root);
    while (!queue.empty()) {
        Node<T>* node = queue.popFront();
        std::cout << node->data;
        if (node->left != nullptr)
            queue.pushBack(node->left);
        if (node->right != nullptr)
            queue.pushBack(node->right);
    }
}

int main() {
  return 0;
}
