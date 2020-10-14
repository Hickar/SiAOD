#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "hashtable.cpp"

using namespace std;

using Key = int;
using Value = string;

string normalizeString(string& str, char character) {
	string result = str;
	if (result.at(0) == character) result.erase(result.begin());
	if (result.at(result.size() - 1) == character) result.erase(result.end());
	return result;
}

pair<Key, Value> splitLine(string &line, char delimiter) {
	pair<Key, Value> hashEntry{};
	string token;
	istringstream tokenStream(line);
	int i{0};

	while (getline(tokenStream, token, delimiter)) {
		if (i % 2 == 0) hashEntry.first = stoi(token);
		else hashEntry.second = normalizeString(token, ' ');
		i++;
	}

	return hashEntry;
}

vector<pair<Key, Value>> getRecordsFromFile(string filename, const char delimiter) {
	vector<pair<Key, Value>> records{};
	string line{};

	fstream file(filename);
	file.is_open();

	if (file.is_open()) {
		while (getline(file, line)) {
			records.push_back(splitLine(line, delimiter));
		}
	}

	file.close();

	return records;
}

int main() {
	HashTable<Key, Value> hashTable{};
	vector<pair<Key, Value>> records{getRecordsFromFile("testRecords", '-')};

	for (const pair<Key, Value> &record : records) {
		hashTable.insert(record.first, record.second);
	}

	cout << hashTable << endl;

	return 0;
}