#include <iostream>
#include <queue>
#include <cassert>
template<class T>
struct Node {
    Node(const T _key) : key(_key), left(nullptr), right (nullptr), height(1), count(1) {}
    T key;
    Node* left;
    Node* right;
    unsigned char height;
    int count;
};

bool isLessDefault(const int& left, const int& right) {
    return left < right;
}

template<class T>
class AVLTree {
private:

    bool (*isLess)(const T&, const T&);
    Node<T>* root;
public:
    AVLTree(bool (*isLess)(const T&, const T&) = isLessDefault);
    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;
    ~AVLTree(){ deleteTree(root); };
    void levelOrder();
    void add(const T& key) { root = insert(root, key); };
    void remove(const T& key) { root = del(root, key); };
    const T& getKStat(int K) { return kStat(K, root); };
private:
    unsigned char getHeight(Node<T>* node) { return node ? node->height : 0;                        };
	int getCount(Node<T>* node)            { return node ? node->count : 0;                         };
    int bfactor(Node<T>* node)             { return getHeight(node->right) - getHeight(node->left); };
	void fixCount(Node<T>* node);

    void fixHeight(Node<T>* node); 
    Node<T>* rotateLeft(Node<T>* node);
    Node<T>* rotateRight(Node<T>* node);
    Node<T>* balance(Node<T>* node);

    Node<T>* insert(Node<T>* node, T key);

    void deleteTree(Node<T>* node);
    Node<T>* del(Node<T>* p, T k);
	Node<T>* findMin(Node<T>* p) { return p->left ? findMin(p->left) : p; }
	Node<T>* removeMin(Node<T>* p);
    Node<T>* findRemoveMin(Node<T>* p, Node<T>*& min);

    const T& kStat(int K, Node<T>* node);
};

template<class T>
void AVLTree<T>::deleteTree(Node<T>* node) {
	if (node) {
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}

template<class T>
AVLTree<T>::AVLTree(bool (*IsLess)(const T&, const T&)) {
    isLess = IsLess;
    root = nullptr; 
}

template<class T>
void AVLTree<T>::fixHeight(Node<T>* node) {
 	unsigned char heightLeft = getHeight(node->left);
	unsigned char heightRight = getHeight(node->right);
	node->height = (heightLeft > heightRight ? heightLeft : heightRight) + 1;
}

template <class T>
void AVLTree<T>::fixCount(Node<T>* node) {
	int countLeft = getCount(node->left);
	int countRight = getCount(node->right);
	node->count = (countLeft + countRight + 1);
}

template<class T>
Node<T>* AVLTree<T>::rotateRight(Node<T>* node) {
    Node<T>* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    fixHeight(node);
    fixCount(node);
    
    fixHeight(temp);
    fixCount(temp);
    return temp;
}

template<class T>
Node<T>* AVLTree<T>::rotateLeft(Node<T>* node) {
    Node<T>* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    fixHeight(node);
    fixCount(node);

    fixHeight(temp);
    fixCount(temp);
    return temp;
}

template<class T>
Node<T>* AVLTree<T>::balance(Node<T>* node) {
	fixHeight(node);
    fixCount(node);

	if (bfactor(node) == 2) {
		if (bfactor(node->right) < 0)
			node->right = rotateRight(node->right);
		return rotateLeft(node);
	}
	if (bfactor(node) == -2) {
		if (bfactor(node->left) > 0)
			node->left = rotateLeft(node->left);
		return rotateRight(node);
	}
	return node;
}

template<class T>
Node<T>* AVLTree<T>::insert(Node<T>* node, T key) {
	if (!node)
		return new Node<T>(key);
	if (isLess(key, node->key))
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);
	return balance(node);
}

template <class T>
Node<T>* AVLTree<T>::removeMin(Node<T>* p) {
	if (p->left == 0)
		return p->right;
	p->left = removeMin(p->left);
	return balance(p);
}

template <class T>
Node<T>* AVLTree<T>::del(Node<T>* node, T key) {
	if (!node)
		return nullptr;

	if (isLess(key, node->key))
		node->left = del(node->left, key);
	else if (isLess(node->key, key))
		node->right = del(node->right, key);
	else {
		Node<T>* tempLeft = node->left;
		Node<T>* tempRight = node->right;

		delete node;
		if (!tempRight) return tempLeft;

		Node<T>* min = nullptr;
		findRemoveMin(tempRight, min);
		min->left = tempLeft;
		return balance(min);
	}

	return balance(node);
}

template <class T>
Node<T>* AVLTree<T>::findRemoveMin(Node<T>* node, Node<T>*&min) {
	if (!node->left) {
		min = node;
		return node->right;
	}
	node->left = findRemoveMin(node->left, min);
	min->right = balance(node); // уже спустились до самого левого элемента, а значит min != NULL
	return min->right;
}

template<class T>
void AVLTree<T>::levelOrder() {
    if (root == nullptr)
		return;
	std::queue<Node<T>*> queue;
	queue.push(root);
	while (!queue.empty()) {
		Node<T>* current = queue.front();
        queue.pop();
        std::cout << current->key << "\n";
		if (current->left != nullptr)
			queue.push(current->left);
		if (current->right != nullptr)
			queue.push(current->right);
	}
}

template <class T>
const T& AVLTree<T>::kStat(int K, Node<T>* node) {
	if (!node)
		assert("Bad K value, not enough elements!" && false);

	int leftCount = getCount(node->left);
	if (K == leftCount)
		return node->key;
	if (K < leftCount)
		return kStat(K, node->left);
	else
		return kStat(K - leftCount - 1, node->right);
}

int main() {
    AVLTree<int> map;
	int size;
	int value;
	int stat;
	std::cin >> size;
	for (int i = 0; i < size; i++) {
		std::cin >> value >> stat;
		if (value < 0)
			map.remove(abs(value));
		else
			map.add(value);

		int res = map.getKStat(stat);
		std::cout << res << std::endl;
	}
    return 0;
}
