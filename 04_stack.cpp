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
	  bool isEmpty() const;		//스택이 비었으면 1, 아니면 0 리턴
	  T& Top() const;		//top 원소를 리턴
	  void Push(const T& item);	//스택을 추가
	  void Pop();		//top 원소 제거
};

int main() {

	return 0;
}

template<typename T>
Stack<T>::Stack(int stackCapacity)
	: top(-1) {
	if (stackCapacity < 1) {	//음수나 0일 경우
		stackCapacity = 10;		//10으로 초기화
	}
	capacity = stackCapacity;
	stack = new T[stackCapacity];
}

template<typename T>
Stack<T>::~Stack() {
	if (stack != NULL) {		//NULL이 아닐 경우
		delete[] stack;			//배열 해제
	}
}

template<typename T>
bool Stack<T>::isEmpty() const {	//스택이 비었으면 1, 아니면 0 리턴
	return top == -1;
}

template<typename T>
T& Stack<T>::Top() const {		//top 원소를 리턴
	if (isEmpty()) {			//스택이 비었으면 문자열 리터럴 리턴
		throw "empty stack";
	}
	return stack[top];
}

template<typename T>
void Stack<T>::Push(const T& item) {	//스택을 추가
	if (top + 1 == capacity) {			//용량이 가득 찼을 경우
		int i = capacity * 2;			//임시로 용량 2배 증가
		T* temp = new T[i];				//새로운 용량 할당
		copy(stack, stack + capacity, temp);	//기존 내용 복사
		delete[] stack;					//기존 배열 해제
		stack = temp;					//새로운 배열을 대입
		capacity = i;					//용량을 증가 
	}
	top++;
	stack[top] = item;					//top + 1 위치에 추가
}

template<typename T>
void Stack<T>::Pop() {			//top 원소 제거
	if (isEmpty()) {			//스택이 비었으면 문자열 리터럴 리턴
		throw "empty stack";
	}
	stack[top].~T();			//top 원소를 해제
	top--;						//top을 1 감소
}
