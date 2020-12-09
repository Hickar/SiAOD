#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

class BinaryTree {
private:
	struct Node {
		int data;
		Node *left;
		Node *right;
	};

	typedef Node *Tree;
	Tree Root;
	int size{0};
	int levels{0};

public:
	explicit BinaryTree(int size) {
		this->size = size;
		this->levels = floor(log2(size));
		//Количество уровней высчитывается посредством логарифма по основанию двойки,
		//так как количество узлов в сбалансировнном дереве при
		//максимальной заполненности равняется 2^n-1, где n – количество узлов
		Root = nullptr;
		createNode(Root, size);
	}

	void createNode(Tree &node, int size) {
		int nl, nr, data;
		if (size != 0) {
			node = new Node;
			node->left = nullptr;
			node->right = nullptr;
			cin >> data;
			node->data = data;
			nl = size / 2;
			nr = size - nl - 1;
			createNode(node->left, nl);
			createNode(node->right, nr);
		};
	}

	void out(Tree &node, int i) {
		if (node) {
			out(node->right, i + 1);
			for (int k = 0; k < levels * i; k++) {
				cout << ' ';
			}
			cout << node->data << endl;
			out(node->left, i + 1);
		}
	};

	//Метод для поиска количества листьев с положительными значениями
	int getPositiveLeafsCount() {
		int count{};
		checkLeafsValues(Root, count);
		return count;
	}

	void checkLeafsValues(Tree &node, int &count) {
		if (node) {
			if (node->left == nullptr && node->right == nullptr) {
				if (node->data > 0) count++;
			} else {
				checkLeafsValues(node->left, count);
				checkLeafsValues(node->right, count);
			}
		}
	}

	//Метод для подсчёта количества узлов с указанным в аргументе значением
	int includeValueCount(int value) {
		int count{0};
		checkForValue(Root, value, count);
		return count;
	}

	void checkForValue(Tree &node, int value, int &count) {
		if (node) {
			if (node->data == value) count++;
			checkForValue(node->left, value, count);
			checkForValue(node->right, value, count);
		}
	}

	//Метод, умножающий значение каждого узла на 2,
	//проходящий по дереву в ширину
	//Обход осуществляется посредством использования очереди, для последовательного
	//прохода по одному уровню за раз
	void multiplyByTwoWithWidthTraverse() {
		queue<Tree> queue;

		Tree node;
		queue.push(Root);

		while (!queue.empty()) {
			node = queue.front();
			queue.pop();
			node->data *= 2;

			if (node->left != nullptr) {
				queue.push(node->left);
			}
			if (node->right != nullptr) {
				queue.push(node->right);
			}
		}
	}

	void print() {
		out(Root, 0);
	};
};