#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
using namespace std;
class Array
{
	std::vector <int> arr;
public:
	Array();
	void Find_max();
	void show();
	void replace();
	void erase();
};




int min0(int value)
{
	return value < 0;
}

Array::Array()
{
	srand(time(NULL));
	arr.resize(10);

	std::generate(arr.begin(), arr.end(), []()->int { return rand() % 10 - 5; });
}


void Array::show()
{
	for (auto i = arr.begin(); i != arr.end(); i++)
	{
		std::cout << *i << "  ";
	}
	std::cout << std::endl;
}


void Array::replace()
{
	std::replace_if(arr.begin(), arr.end(), min0, 0);
}

void Array::Find_max()
{
	int max;
	max = *max_element(arr.begin(), arr.end());
	cout << max << endl;
}

void Array::erase()
{
	std::sort(arr.begin(), arr.end());
	std::cout << "Array with sort" << endl;
	show();
	std::cout << endl;
	std::cout << "Delete all duplicate elements\n";
	auto last = std::unique(arr.begin(), arr.end());
	arr.resize(std::distance(arr.begin(), last));
}

int main()
{
	system("color F0");
	Array arr;
	std::cout << "Array\n";
	arr.show();

	std::cout << std::endl;
	std::cout << "Max element of vector\n";
	arr.Find_max();


	std::cout << std::endl;
	std::cout << "Replace all elements to zero, which less than 0 \n";
	arr.replace();
	arr.show();

	std::cout << std::endl;

	arr.erase();
	arr.show();

	return 0;
}

