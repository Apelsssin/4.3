
#include <iostream>
#include <exception>

class smart_array {

	int* arr;
	int n;
	int i = 0;

public:
	void add_element(int k) {
		if (i < n) {
			arr[i] = k;
		}
		else {
			//throw std::exception("Количество элементов больше количества элементов, на которую выделена память!");
			int* arr1 = new int[n];
			for (int i = 0; i < n; ++i) {
					arr1[i] = arr[i];
			}
			n *= 2;
			arr = new int[n];
			for (int i = 0; i < (n / 2); ++i) {
				arr[i] = arr1[i];
			}
			delete[] arr1;
			arr[n / 2] = k;
		}
		++i;
	}
	
	int get_element(int j) {
		if (0 <= j < n)
			return arr[j];
		else
			throw std::exception("Некорректный индекс!");
	}
	
	smart_array (int n) {
		this->n = n;
		arr = new int[n];
	}
	
	~smart_array () {
		delete[] arr;
	}
	smart_array(const smart_array&) = delete;
	smart_array& operator=(const smart_array&) = delete;
};

int main()
{
	setlocale(LC_ALL, "Russian");
	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);
		arr.add_element(14);
		arr.add_element(15);
		std::cout << arr.get_element(1) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}
