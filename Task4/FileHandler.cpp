#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

template<class Key, class Value>
class FileHandler {
private:
//Функция, нормализующая строку, убирая из неё проблелы в начале и в конце
//при присутствии таковых
	string normalizeString(string &str, char character) {
		string result = str;
		if (result.at(0) == character) result.erase(result.begin());
		if (result.at(result.size() - 1) == character) result.erase(result.end());
		return result;
	}

//Функция, разделяющая строку на несколько подстрок, разделённых указанным символом
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

public:
	FileHandler() = default;
	~FileHandler() = default;

//Функция, осуществляющая считывание записей из текстового файла
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
};
