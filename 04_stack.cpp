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

	Stack<char> formula(10), parentheses(10), temp(10);	//각각 수식, 괄호, 임시 저장용 스택
	char c = '#';	//입력값을 받는 변수 초기화
	int chk = 0;	//괄호 입력 여부 확인 변수 초기화

	while (c = getchar()) {		//한 글자씩 대입
		if (c == '#' || c == '\n') { break; }	//대입값이 # 또는 \n이면 입력 종료
		
		formula.Push(c);	//수식 스택에 추가
		
		if (c == '(' ||				//여는 괄호일때
			c == '[' ||
			c == '<' ||
			c == '{'
			) {
			parentheses.Push(c);	//괄호 스택에 추가
			chk++;					//괄호 입력 여부 확인
		}
		else if (					//닫는 괄호일때
			c == ')' ||
			c == ']' ||
			c == '>' ||
			c == '}'
			) {

			if (parentheses.isEmpty()) {	//닫는 괄호인데 괄호 스택이 비었을경우
				for (int i = 0; formula.isEmpty() != 1; i++) {	//임시 스택에 수식 스택의 값 추가
					temp.Push(formula.Top());
					formula.Pop();
				}

				cout << "Error : ";

				for (int i = 0; temp.isEmpty() != 1; i++) {		//수식 스택 출력
					cout << temp.Top();
					temp.Pop();
				}

				cout << endl;
				cout << "Stack : empty";	//빈 스택임을 출력

				return 0;	//프로그램 종료
			}

			if (					//괄호 스택의 top과 매칭이 될 경우
				(parentheses.Top() == '(' && ')' == c) ||
				(parentheses.Top() == '[' && ']' == c) ||
				(parentheses.Top() == '<' && '>' == c) ||
				(parentheses.Top() == '{' && '}' == c)
				) {
				parentheses.Pop();	//매칭된 괄호 제거
			}
			else {					//매칭이 안될 경우
				break;				//반복문 종료
			}
		}
	}

	if (formula.isEmpty() || chk == 0) {	//수식 스택이 비어있거나 괄호 입력이 없을 경우
		cout << "Error" << endl;
		return 0;
	}

	if (parentheses.isEmpty()) {		//수식 스택이 비어있지 않고, 괄호도 입력되었으며 괄호 스택이 비었을 경우 (정상 입력인 경우)

		for (int i = 0; formula.isEmpty() != 1; i++) {	//임시 스택에 수식 스택의 값 추가
			temp.Push(formula.Top());
			formula.Pop();
		}

		cout << "Correct! ";

		for (int i = 0; temp.isEmpty() != 1; i++) {		//수식 스택 출력
			cout << temp.Top();
			temp.Pop();
		}

		cout << endl;
	}
	else {								//수식 스택이 비어있지 않지만 괄호 스택에 값이 있을 경우 (괄호 매칭에 실패한 경우)
		for (int i = 0; formula.isEmpty() != 1; i++) {	//임시 스택에 수식 스택의 값 추가
			temp.Push(formula.Top());
			formula.Pop();
		}

		cout << "Error : ";

		for (int i = 0; temp.isEmpty() != 1; i++) {		//수식 스택의 값 출력
			cout << temp.Top();
			temp.Pop();
		}

		cout << endl;
		
		for (int i = 0; parentheses.isEmpty() != 1; i++) {	//임시 스택에 괄호 스택의 값 추가
			temp.Push(parentheses.Top());
			parentheses.Pop();
		}

		cout << "Stack : ";

		for (int i = 0; temp.isEmpty() != 1; i++) {		//괄호 스택의 값 출력
			cout << temp.Top();
			temp.Pop();
		}
	}

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
