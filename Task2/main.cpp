#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "hashtable.cpp"

using namespace std;

using Key = int;
using Value = string;

// Функция, нормализующая строку, убирая из неё проблелы в начале и в конце
// при присутствии таковых
string normalizeString(string& str, char character) {
	string result = str;
	if (result.at(0) == character) result.erase(result.begin());
	if (result.at(result.size() - 1) == character) result.erase(result.end());
	return result;
}

// Функция, разделяющая строку на несколько подстрок, разделённых указанным символом
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

// Функция, осуществляющая считывание записей из текстового файла
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

	cout << "Изначальная хеш-таблица: " << endl;
	cout << hashTable << endl;

	//TEST: removing some elements
	hashTable.remove(1000003);
	hashTable.remove(1000009);
	hashTable.remove(1000021);

	cout << "Хеш-таблица после удаления элементов со следующими ключами: 1000003, 1000009, 1000021" << endl;
	cout << hashTable << endl;

	//TEST: finding elements
	cout << "Поиск значений элементов по следующим ключам: " << endl;
	cout << "1000005: " << hashTable.find(1000005) << endl;
	cout << "1000000: " << hashTable.find(1000000) << endl;
	cout << "1000030: " << hashTable.find(1000030) << endl;

	return 0;
}