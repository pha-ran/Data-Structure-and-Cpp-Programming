#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class Bag;

template <typename T>	//�Ǵ� <class T>, ���� ������ ��쿡�� ���ø� �ۼ�
void sort(T* a, int n);

template <typename T>
void ChangeSize1D(T* &a, const int oldSize, const int newSize);

template <typename T>
class Bag {
public:
	Bag(int bagCapacity = 10);
	~Bag();
	int Size() const { return top + 1; }
	bool IsEmpty() const { return Size() == 0; }
	T& Element() const;
	void Push(const T& x);
	void Pop();
private:
	T* array;
	int capacity;
	int top;
};

int main() {
	

	return 0;
}

template <typename T>	//�Ǵ� <class T>
void sort(T* a, int n) {
	for (int i = 0; i < n; i++) {
		int j = i;

		for (int k = i + 1; k < n; k++) {
			if (a[k] < a[j]) { j = k; }
		}

		swap(a[i], a[j]);
	}
}

template <typename T>
void ChangeSize1D(T* &a, const int oldSize, const int newSize) {
	if (newSize < 0) throw "New Size must be >= 0";

	T* temp = new T[newSize];
	int number = min(oldSize, newSize); //�� �� ���� ��
	copy(a, a + number, temp); //number ���� ����
	delete[] a;
	a = temp;
}

template <typename T>
Bag<T>::Bag(int bagCapacity) {
	if (capacity < 1) throw "Capacity must be > 0";
	capacity = bagCapacity;
	array = new T[capacity];
	top = -1;
}

template <typename T>
Bag<T>::~Bag() { delete[] array; }

template <typename T>
T& Bag<T>::Element() const {
	if (IsEmpty()) throw "Bag is empty";
	return array[0];
}

template <typename T>
void Bag<T>::Push(const T& x) {
	if (capacity == top + 1) {
		ChangeSize1D(array, capacity, 2 * capacity);
		capacity *= 2;
	}
	array[++top] = x;
}

template <typename T>
void Bag<T>::Pop() {
	if (IsEmpty()) throw "Bag is empty, cannot delete";
	int deletePos = top / 2;
	copy(array + deletePos + 1, array + top + 1, array + deletePos); 
		//deletePos + 1 �� ������ ������ ������ ��ĭ�� �̵� (top�� index�̱� ������ top + 1 ����)
	array[top--].~T();
}
