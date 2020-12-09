#include <iostream>
#include "binaryTree.cpp"

using namespace std;

int main() {
	try {
		int size{};
		cout << "Введите количество элементов бинарного дерева: " << endl;
		cin >> size;
		cout << "Вводите значения узлов дерева построчно: " << endl;

		BinaryTree binaryTree{size};
		cout << endl << "Исходное бинарное дерево:" << endl;
		binaryTree.print();

		cout << endl << "Количество листьев с положительным значением: "
		<< binaryTree.getPositiveLeafsCount();

		cout << endl << "Количество узлов со значением \"2\": "
				 << binaryTree.includeValueCount(2);

		binaryTree.multiplyByTwoWithWidthTraverse();
		cout << endl << "Бинарное дерево после умножения значений всех узлов на 2:" << endl;
		binaryTree.print();
	} catch (length_error &err) {
		cerr << err.what() << endl;
	}

	return 0;
}