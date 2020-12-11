#include <iostream>
#include <cmath>

using namespace std;

template<class Key, class Value>
class BST {
private:
	struct Node {
		Key key;
		Value data;
		Node *left;
		Node *right;
	};

	Node *insert(Node *&tree, Node *node) {
		if (tree == nullptr) tree = node;
		else if (node->key < tree->key) insert(tree->left, node);
		else if (node->key > tree->key) insert(tree->right, node);
		return tree;
	}

	Node *search(Node *&tree, Key key) {
		if (tree == nullptr) return nullptr;
		else if (key < tree->key) search(tree->left, key);
		else if (key > tree->key) search(tree->right, key);
		return tree;
	}

	Node *findMin(Node *node) {
		Node *current = node;
		while (current && current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	Node *remove(Node *tree, int key) {
		if (tree == nullptr) return tree;
		if (key < tree->key) tree->left = remove(tree->left, key);
		else if (key > tree->key) tree->right = remove(tree->right, key);
		else {
			if (tree->left == nullptr) {
				Node *temp = tree->right;
				delete tree;
				return temp;
			} else if (tree->right == nullptr) {
				Node *temp = tree->left;
				delete tree;
				return temp;
			}

			Node *temp = findMin(tree->right);
			tree->key = temp->key;
			tree->right = remove(tree->right, temp->key);
		}
		return tree;
	}

	Node *root;
	int size{0};
	int levels{0};

public:
	BST() {
		root = nullptr;
	}

	void insert(Key key, Value value) {
		Node* node = createNode(key, value);
		root = insert(root, node);
		size++;
		levels = floor(log2(size));
	}

	void remove(Key key) {
		root = remove(root, key);
		size--;
		levels = floor(log2(size));
	}

	void display() {
		inorder(root);
		cout << endl;
	}

	void search(int x) {
		root = find(root, x);
	}

	Node *createNode(Key key, Value value) {
		Node *node = new Node;
		node->key = key;
		node->data = value;
		node->left = nullptr;
		node->right = nullptr;
		return node;
	}

	void out(Node *&node, int i) {
		if (node) {
			out(node->right, i + 1);
			for (int k = 0; k < levels * i; k++) {
				cout << ' ';
			}
			cout << node->key << endl;
			out(node->left, i + 1);
		}
	};

	void print() {
		out(root, 0);
	};
};
