#include <iostream>
#include <ctime>
class A
{
public:
	A();
	~A();

	class el
	{
	public:
		el(double val) { value = val; }
		~el();
		void edit(int val) { value = val; };
		el* next = nullptr;
		int value;

	};

	void add(int val);
	void del(int index);
	void del_with_sort(int index);
	void show();
	void show_info();
	void sort();
	double get(int index);
	double get_data(int val);
	int get_size() { return size; };
	el* get_el(int index);
	void add_with_sort(int val);
	void sent();



private:


	el* top = nullptr;
	el* curr = top;
	int size = 0;
	int general_comparison = 0;
	int general_permutation = 0;
};
void A::sent() {
	int* arr = new int[size];
	curr = top;
	int index = 0;
	for (index; index < size; index++) {
		arr[index] = curr->value;
		curr = curr->next;
		if (curr == nullptr) {
			break;
		}
	}
	int k = 0;
	for (int i = 0; i < size; i++) {
		bool fl = true;
		for (int j = 0; j < size; j++)
			if (i != j && arr[i] == arr[j]) {
				fl = false;
				break;
			}
		if (fl) k++;
	}
	std::cout << k;
	delete[] arr;
}
void A::add(int val)
{

	if (top == nullptr)
	{
		top = new el(val);
		size++;
	}
	else
	{
		el* current = top;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new el(val);
		size++;
	}

}
void A::del(int index)
{
	el* current = top;
	for (int i = 1; i < index; i++)
	{
		if (current == nullptr)
		{
			std::cout << "Error, out of range\n";
			return;
		}
		current = current->next;
	}
	current->next = current->next->next;
	size--;

}
void A::add_with_sort(int val) {
	add(val);
	if (size > 1)
	{
		sort();
	}
}
void A::del_with_sort(int index)
{
	del(index);
	if (size > 1)
	{
		sort();
	}
}
void A::show()
{
	for (el* current = top; current != nullptr; current = current->next)
	{
		std::cout << current->value << " ";
	}
	std::cout << '\n';
}

void A::show_info()
{
	std::cout << "general_comporisons: " << general_comparison << "\ngeneral_permutations: " << general_permutation << "\n";
	general_comparison = 0;
	general_permutation = 0;
}

void A::sort()
{
	int* mas = new int[size];
	curr = top;
	int index = 0;
	for (index; index < size; index++) {
		mas[index] = curr->value;
		curr = curr->next;
		if (curr == nullptr) {
			break;
		}
	}

	for (int i = size - 1; i > 0; i--) {
		int maxind = 1;
		for (int j = 0; j <= i; j++) {
			general_comparison += 1;
			if (mas[j] > mas[maxind])
			{

				maxind = j;
			}
		}
		int tmp = mas[i];
		mas[i] = mas[maxind];
		mas[maxind] = tmp;
		general_permutation += 1;
	}
	curr = top;
	for (index = 0; index < size; index++) {
		curr->value = mas[index];
		curr = curr->next;
		if (curr == nullptr) {
			break;
		}
	}

	delete[] mas;


}


double A::get(int index)
{
	el* current = top;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current->value;
}

double A::get_data(int val)
{
	int i = 0;
	for (el* current = top; current != nullptr; current = current->next)
	{
		if (current->value == val)
		{
			return i;
		}
		i++;
	}
	return -1;
}

A::el* A::get_el(int index)
{
	el* current = top;
	for (int i = 0; i < index; i++)
	{
		current = current->next;
	}

	return current;
}

A::A()
{

}

A::~A()
{
}

int main()
{
	A array;
	std::srand(time(0));
	for (int i = 0; i < 14; i++)
	{
		array.add(rand() % 1000);
	}
	array.show();

	std::cout << "1) to sort array\t2)to delete index\t3)to delete index with sort\n4)to find by index\t5)to find by value\n6) add element\n7) make a task\n";
	int var = 0;
	int index;
	int val;

	while (var < 8)
	{
		std::cin >> var;
		switch (var)
		{
		case 1:
			array.sort();
			array.show();
			array.show_info();
			std::cout << '\n';
			break;
		case 2:
			std::cout << "Enter index: ";

			std::cin >> index;
			array.del(index);
			array.show();
			std::cout << '\n';
			break;
		case 3:
			std::cout << "Enter index: ";

			std::cin >> index;
			array.del_with_sort(index);
			array.show();
			array.show_info();
			std::cout << '\n';
			break;

		case 4:
			std::cout << "Enter index: ";

			std::cin >> index;
			std::cout << array.get(index) << '\n';
			std::cout << '\n';
			break;
		case 5:
			std::cout << "Enter value: ";

			std::cin >> index;
			std::cout << array.get_data(index);
			std::cout << '\n';
			break;
		case 6:
			std::cin >> val;
			array.add_with_sort(val);
			array.show();
			array.show_info();
			std::cout << '\n';
			break;
		case 7:
			array.sent();
			break;
		default:
			break;
		}
	}

	std::cout << array.get(13);
}
