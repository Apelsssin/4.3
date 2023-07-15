
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
			[&]() {
				int* arr1 = std::move(arr);
				n *= 2;
				arr = new int[n];
				for (int i = 0; i < (n / 2); ++i) {
					arr[i] = arr1[i];
				}
				delete[] arr1;
				arr[n / 2] = k;
			}();
		}
		++i;
	}

	int get_element(int j) {
		if (j < n)
			return arr[j];
		else
			throw std::exception("Некорректный индекс!");
	}

	smart_array(int n) {
		this->n = n;
		arr = new int[n];
	}

	~smart_array() {
		delete[] arr;
	}
	smart_array& operator=(const smart_array& arr2) {
		if (this != &arr2) {
			delete[] arr;
			n = arr2.n;
			arr = new int[arr2.n];
			for (int i = 0; i < n; ++i) {
				arr[i] = arr2.arr[i];
				//std::cout << arr[i] << " ";
			}
		}
		return  *this;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	try {
		smart_array arr(5);
		arr.add_element(1);
		arr.add_element(4);
		arr.add_element(155);

		smart_array new_array(2);
		new_array.add_element(44);
		new_array.add_element(34);

		arr = new_array;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
}
