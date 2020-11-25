#include <iostream>
#include <optional>

using namespace std;

template<typename Key, typename Value>
class HashTable {
public:
	HashTable(int default_size = 17) {
		buffer_size = default_size;
		size = 0;
		size_all_non_nullptr = 0;
		array = new Node[buffer_size];
	};

	~HashTable() {
		delete[] array;
	};

	// Метод insert производит запись указанного значение в ячейку с указанным ключом
	void insert(Key key, Value value) {
		if (size + 1 > int(rehash_size * buffer_size)) {
			resize();
			rehash();
		} else if (size_all_non_nullptr > 2 * size) {
			rehash();
		}
		int hash{this->hash(key)};
		int i{1};
		while (i <= buffer_size) {
			Node *node = &array[hash];
			if (node->key == key)
				break;
			if (node->isFree && !node->isDeleted) {
				node->setValue(key, value);
				++size;
				++size_all_non_nullptr;
			} else {
				hash += i;
			}
			++i;
		}
	};

	// Метод удаляющий запись по её ключу
	void remove(Key key) {
		int hash = this->hash(key);
		int i{1};
		while (i <= buffer_size) {
			Node *node = &array[hash];
			if (node->key == key) {
				node->clear();
				--size;
				break;
			} else {
				hash += i;
			}
			++i;
		}
	};

	// Метод нахождения значения по ключу записи
	Value find(Key key) {
		auto node = &array[hash(key)];
		if (!node->isFree && !node->isDeleted) return node->value;
		else return {};
	}

	// Метод, изменяющий размер массива по достижении им коэффициента загрузки (75%)
	void resize() {
		old_buffer_size = buffer_size;
		buffer_size *= 2;
	};

	// Метод, переинициализациющий массив и последующее рехеширование всех его записей
	void rehash() {
		Node *oldArray = array;
		array = new Node[buffer_size];

		for (int i = 0; i < old_buffer_size; i++) {
			int hash = this->hash(oldArray[i].key);
			if (!oldArray[i].isDeleted && !oldArray[i].isFree) array[hash] = oldArray[i];
		}

		size_all_non_nullptr = 0;
	};

	// Метод, реализующий хешеривание ключа
	int hash(Key key) {
		return key % buffer_size;
	}


	// Метод, возвращающий размер массива
	int getBufferSize() {
		return buffer_size;
	}

	// Метод, возвращающий ключ указанного элемента из массива
	Key getKey(int i) {
		return array[i].key;
	}

	// Метод, при помощи которого можно совершить операцию вывода в cout объекта данного класса
	friend ostream &operator<<(ostream &os, HashTable &hashTable) {
		for (int i = 0; i < hashTable.getBufferSize(); i++) {
			Key key{hashTable.getKey(i)};
			if (key != 0) os << key << " – " << hashTable.find(key) << endl;
		}
		return os;
	}

private:
	constexpr static float rehash_size{0.75}; // Коэффициент загрузки
	int size{}; // Количество занятых элементов
	int buffer_size{}; // Общее количество элементов
	int size_all_non_nullptr{}; // Количество занятых элементов, включая удалённые
	int old_buffer_size{}; // Общее количество элементов перед его рехешированием

	// Структура Node, реализующая собою запись в хеш-таблице
	struct Node {
		Key key{0};
		Value value{""};
		bool isFree{true}, isDeleted{false};

		Node() {
			this->key = {};
			this->value = {};
			this->isFree = true;
			this->isDeleted = false;
		}

		void setValue(Key &key, Value &value) {
			this->key = key;
			this->value = value;
			this->isFree = false;
		}

		void clear() {
			this->key = {};
			this->value = {};
			this->isFree = true;
			this->isDeleted = true;
		}

		~Node() = default;
	};

	// Массив всех записей хеш-таблицы
	Node *array;
};

