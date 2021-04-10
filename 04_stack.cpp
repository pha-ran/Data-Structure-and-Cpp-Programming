#include <iostream>
#include <algorithm>

using namespace std;

template<typename T>
class Stack {
  private:
	  T* stack;
	  int top;
	  int capacity;
  public:
	  Stack(int stackCapacity = 10);
	  ~Stack();
	  bool isEmpty() const;		//������ ������� 1, �ƴϸ� 0 ����
	  T& Top() const;		//top ���Ҹ� ����
	  void Push(const T& item);	//������ �߰�
	  void Pop();		//top ���� ����
};

int main() {

	return 0;
}

template<typename T>
Stack<T>::Stack(int stackCapacity)
	: top(-1) {
	if (stackCapacity < 1) {	//������ 0�� ���
		stackCapacity = 10;		//10���� �ʱ�ȭ
	}
	capacity = stackCapacity;
	stack = new T[stackCapacity];
}

template<typename T>
Stack<T>::~Stack() {
	if (stack != NULL) {		//NULL�� �ƴ� ���
		delete[] stack;			//�迭 ����
	}
}

template<typename T>
bool Stack<T>::isEmpty() const {	//������ ������� 1, �ƴϸ� 0 ����
	return top == -1;
}

template<typename T>
T& Stack<T>::Top() const {		//top ���Ҹ� ����
	if (isEmpty()) {			//������ ������� ���ڿ� ���ͷ� ����
		throw "empty stack";
	}
	return stack[top];
}

template<typename T>
void Stack<T>::Push(const T& item) {	//������ �߰�
	if (top + 1 == capacity) {			//�뷮�� ���� á�� ���
		int i = capacity * 2;			//�ӽ÷� �뷮 2�� ����
		T* temp = new T[i];				//���ο� �뷮 �Ҵ�
		copy(stack, stack + capacity, temp);	//���� ���� ����
		delete[] stack;					//���� �迭 ����
		stack = temp;					//���ο� �迭�� ����
		capacity = i;					//�뷮�� ���� 
	}
	top++;
	stack[top] = item;					//top + 1 ��ġ�� �߰�
}

template<typename T>
void Stack<T>::Pop() {			//top ���� ����
	if (isEmpty()) {			//������ ������� ���ڿ� ���ͷ� ����
		throw "empty stack";
	}
	stack[top].~T();			//top ���Ҹ� ����
	top--;						//top�� 1 ����
}
