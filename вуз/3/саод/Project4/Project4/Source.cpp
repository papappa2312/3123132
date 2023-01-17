#include <iostream>
#include <ctime>
#include <fstream>
using namespace std;

class HashTable {
private:
	constexpr static const double rehash_size = 0.75;
	struct Node {
		bool deleted;
		string data;
		Node(const std::string& data) {
			this->data = data;
			deleted = false;
		}
	};
	Node** arr;
	int size, size_non_nullptr, size_buffer;

	int hash_Horner(std::string str) {
		int hash_result = 0;
		for (int i = 0; i < 6; i++)
			hash_result += ((size_buffer / (i + 10)) * hash_result + int(str[i])) % size_buffer;
		return (hash_result * 2) % size_buffer;
	}
public:
	HashTable(int size) {
		size_buffer = size;
		size_non_nullptr = this->size = 0;
		arr = new Node * [size_buffer];

		for (int i = 0; i < size_buffer; i++) {
			arr[i] = nullptr;
		}
	}

	void Create(const int length) {
		for (int i = 0; i < size_buffer; i++) {
			delete arr[i];
		}
		delete[] arr;

		size_buffer = length;
		size_non_nullptr = this->size = 0;
		arr = new Node * [size_buffer];
		for (int i = 0; i < size_buffer; i++) {
			arr[i] = nullptr;
		}
	}

	void Print() {
		cout << "Хеш-таблица:" << endl;
		for (int i = 0; i < size_buffer; i++) {
			if (arr[i] != nullptr && !arr[i]->deleted) {
				cout << i + 1 << ": " << arr[i]->data << endl;
			}
			else {
				cout << i + 1 << ":" << endl;
			}
		}
	}

	bool Find(const std::string data) {
		int index = hash_Horner(data);
		int i = 0;
		while (arr[index] != nullptr && i < size_buffer) {
			if (arr[index]->data == data && !arr[index]->deleted) {
				std::cout << "Введенный ключ имеет индекс " << index << " в хеш-таблице." << std::endl;
				return true;
			}
			index = (index + (i + 3 * i * i)) % size_buffer;
			++i;
		}
		return false;
	}
	void find_el_by_ind() {
		int ind;
		cin >> ind;
		if (arr[ind - 1] != nullptr && !arr[ind - 1]->deleted)
			cout << "Ключ с индексом " << ind << "равен " << arr[ind - 1]->data << endl;
		else
			cout << " ячейка пуста " << endl;
	}

	bool Remove(const std::string data) {
		int index = hash_Horner(data);
		int i = 0;
		while (arr[index] != nullptr && i < size_buffer) {
			if (arr[index]->data == data && !arr[index]->deleted) {
				arr[index]->deleted = true; // Cделать вывод элементов, вызвавших коллизию с удаляемым. Сделано!
				--size;
				i = 1;
				index = (index + (2 * i + 3 * i * i)) % size_buffer;
				while (arr[index] != nullptr) {
					std::cout << "Элемент " << index << ": " << arr[index]->data << " вызывал коллизию с удаленным элементом" << std::endl;
					++i;
					index = (index + (2 * i + 3 * i * i)) % size_buffer;
				}
				return true;
			}
			index = (index + (2 * i + 3 * i * i)) % size_buffer;
			++i;
		}
		return false;
	}

	void Resize() {
		int old_size_buffer = size_buffer;
		size_non_nullptr = size = 0;
		size_buffer *= 2;
		Node** arr2 = new Node * [size_buffer];
		for (int i = 0; i < size_buffer; ++i)
			arr2[i] = nullptr;
		swap(arr, arr2);
		for (int i = 0; i < old_size_buffer; ++i) {
			if (arr2[i] && !arr2[i]->deleted)
				Add(arr2[i]->data); // добавляем элементы в новый массив
		}

		for (int i = 0; i < old_size_buffer; i++) {
			delete arr2[i];
		}
		delete[] arr2;
	}

	void Rehash()
	{
		size_non_nullptr = 0;
		size = 0;
		Node** arr2 = new Node * [size_buffer];
		for (int i = 0; i < size_buffer; ++i)
			arr2[i] = nullptr;
		std::swap(arr, arr2);
		for (int i = 0; i < size_buffer; ++i) {
			if (arr2[i] && !arr2[i]->deleted)
				Add(arr2[i]->data);
		}

		for (int i = 0; i < size_buffer; ++i)
			if (arr2[i])
				delete arr2[i];
		delete[] arr2;
	}

	bool Add(const std::string data) {
		if (size + 1 > int(rehash_size * size_buffer))
			Resize();
		else if (size_non_nullptr > 2 * size)
			Rehash();
		int index = hash_Horner(data);
		int i = 0, first_deleted = -1;
		while (arr[index] != nullptr && i < size_buffer) {
			if (arr[index]->data == data && !arr[index]->deleted)
				return false;
			if (arr[index]->deleted && first_deleted == -1) // находим место для нового элемента
				first_deleted = index;
			index = (index + (2 * i + 3 * i * i)) % size_buffer;
			++i;
		}
		if (first_deleted == -1) {
			arr[index] = new Node(data);
			++size_non_nullptr;
		}
		else {
			arr[first_deleted]->data = data;
			arr[first_deleted]->deleted = false;
		}
		++size;
		return true;
	}

	~HashTable() {
		for (int i = 0; i < size_buffer; i++) {
			delete arr[i];
		}
		delete[] arr;
	}
};

void write(string file_name, const int* arr, const int length) {
	std::fstream file;
	file.open(file_name, fstream::out);
	if (file.is_open())
		for (int i = 0; i < length; i++)
			file << arr[i] << '\n';
	else
		std::cerr << "ERROR!" << std::endl;
	file.close();
}

bool check_key(string key) {
	bool check = true;
	int length = 0;
	for (int i = 0; i < 6; i++) {
		if (i == 0 && (key[i] < 65 || key[i] > 90) || i == 4 && (key[i] < 65 || key[i] > 90) || i == 5 && (key[i] < 65 || key[i] > 90))
			check = true;
		else if (i == 1 && (key[i] < 48 || key[i] > 57) || i == 2 && (key[i] < 48 || key[i] > 57) || i == 3 && (key[i] < 48 || key[i] > 57))
			check = true;

		length++;

	}
	if (length != 6)
		return false;
	if (!check)
		return false;
	else
		return true;
}

string create_key() {
	string key = "";
	for (int i = 0; i < 6; i++) {
		if (i == 0 || i == 4 || i == 5) {
			key += char(rand() % 26 + 65);
		}
		else {
			key += char(rand() % 10 + 48);
		}
	}
	return key;
}

void menu() {
	cout << "\n========MENU========" << endl;
	cout << "0 - Создать таблицу(будет удалена предыдущая)" << endl;
	cout << "1 - Сгенерировать" << endl;
	cout << "2 - Добавить элемент" << endl;
	cout << "3 - Вывести таблицу" << endl;
	cout << "4 - Найти элемент" << endl;
	cout << "5 - Удалить элемент" << endl;
	cout << "6 - найти по индексу" << endl;
	cout << "7 - Выход" << endl;
	cout << "====================" << endl;
}

void select(HashTable& table) {
	while (true) {
		menu();
		int choise;
		cout << "Ваш выбор: ";
		cin >> choise;
		switch (choise) {
		case 0: {
			system("cls");
			int size;
			cout << "Введите размер таблицы: ";
			cin >> size;
			if (size > 3000)
				cout << "Размер таблицы не должен превышать 3000" << endl;
			else
				table.Create(size);
			break;
		}
		case 1: {
			system("cls");
			int number;
			cout << "Введите количество сгенерируемых ключей: ";
			cin >> number;
			if (number > 3000)
				cout << "Количество ключей не должно превышать 3000" << endl;
			else {
				for (int i = 0; i < number; i++) {
					table.Add(create_key());
				}
			}
			break;
		}
		case 2: {
			system("cls");
			string key;
			cout << "Шаблон: БцццББ\nВведите ключ для добавления: ";
			cin >> key;
			if (check_key(key))
				table.Add(key);
			else
				cout << "Введенный ключ некорректен." << endl;
			break;
		}
		case 3: {
			system("cls");
			table.Print();
			break;
		}
		case 4: {
			system("cls");
			string key;
			cout << "Шаблон: БцццББ\nВведите ключ для поиска: ";
			cin >> key;
			if (check_key(key)) {
				if (!table.Find(key))
					cout << "Ключ " << key << " не найден!" << endl;
			}
			else
				cout << "Введенный ключ некорректен." << endl;
			break;
		}
		case 5: {
			system("cls");
			string key;
			cout << "Шаблон: БцццББ\nВведите ключ для удаления и вывода коллизий: ";
			cin >> key;
			if (check_key(key)) {
				if (!table.Remove(key))
					cout << "Ключ " << key << " не найден!" << endl;
			}
			else
				cout << "Введенный ключ некорректен." << endl;
			break;
		}
		case 6: {

			table.find_el_by_ind();
			break;
		}
		case 7: {
			exit(0);
			break;
		}
		}
	}
}

int main() {
	srand(time(NULL));
	setlocale(LC_ALL, "RU");
	HashTable Table(100);
	select(Table);
	return 0;
}

