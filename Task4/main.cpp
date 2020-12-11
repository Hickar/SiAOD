#include <iostream>
#include <string>
#include "BST.cpp"
#include "FileHandler.cpp"

using namespace std;
using Key = int;
using Value = string;

int main() {
	try {
		BST<Key, Value> binarySearchTree;
		FileHandler<Key, Value> fileHandler;

		vector<pair<Key, Value>> records = fileHandler.getRecordsFromFile("testRecords", '-');
		for (const pair<Key, Value>& record : records) {
			binarySearchTree.insert(record.first, record.second);
		}

		binarySearchTree.print();
	} catch (exception &e) {
		cerr << e.what() << endl;
	}
	return 0;
}