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

	Stack<char> formula(10), parentheses(10), temp(10);	//���� ����, ��ȣ, �ӽ� ����� ����
	char c = '#';	//�Է°��� �޴� ���� �ʱ�ȭ
	int chk = 0;	//��ȣ �Է� ���� Ȯ�� ���� �ʱ�ȭ

	while (c = getchar()) {		//�� ���ھ� ����
		if (c == '#' || c == '\n') { break; }	//���԰��� # �Ǵ� \n�̸� �Է� ����
		
		formula.Push(c);	//���� ���ÿ� �߰�
		
		if (c == '(' ||				//���� ��ȣ�϶�
			c == '[' ||
			c == '<' ||
			c == '{'
			) {
			parentheses.Push(c);	//��ȣ ���ÿ� �߰�
			chk++;					//��ȣ �Է� ���� Ȯ��
		}
		else if (					//�ݴ� ��ȣ�϶�
			c == ')' ||
			c == ']' ||
			c == '>' ||
			c == '}'
			) {

			if (parentheses.isEmpty()) {	//�ݴ� ��ȣ�ε� ��ȣ ������ ��������
				for (int i = 0; formula.isEmpty() != 1; i++) {	//�ӽ� ���ÿ� ���� ������ �� �߰�
					temp.Push(formula.Top());
					formula.Pop();
				}

				cout << "Error : ";

				for (int i = 0; temp.isEmpty() != 1; i++) {		//���� ���� ���
					cout << temp.Top();
					temp.Pop();
				}

				cout << endl;
				cout << "Stack : empty";	//�� �������� ���

				return 0;	//���α׷� ����
			}

			if (					//��ȣ ������ top�� ��Ī�� �� ���
				(parentheses.Top() == '(' && ')' == c) ||
				(parentheses.Top() == '[' && ']' == c) ||
				(parentheses.Top() == '<' && '>' == c) ||
				(parentheses.Top() == '{' && '}' == c)
				) {
				parentheses.Pop();	//��Ī�� ��ȣ ����
			}
			else {					//��Ī�� �ȵ� ���
				break;				//�ݺ��� ����
			}
		}
	}

	if (formula.isEmpty() || chk == 0) {	//���� ������ ����ְų� ��ȣ �Է��� ���� ���
		cout << "Error" << endl;
		return 0;
	}

	if (parentheses.isEmpty()) {		//���� ������ ������� �ʰ�, ��ȣ�� �ԷµǾ����� ��ȣ ������ ����� ��� (���� �Է��� ���)

		for (int i = 0; formula.isEmpty() != 1; i++) {	//�ӽ� ���ÿ� ���� ������ �� �߰�
			temp.Push(formula.Top());
			formula.Pop();
		}

		cout << "Correct! ";

		for (int i = 0; temp.isEmpty() != 1; i++) {		//���� ���� ���
			cout << temp.Top();
			temp.Pop();
		}

		cout << endl;
	}
	else {								//���� ������ ������� ������ ��ȣ ���ÿ� ���� ���� ��� (��ȣ ��Ī�� ������ ���)
		for (int i = 0; formula.isEmpty() != 1; i++) {	//�ӽ� ���ÿ� ���� ������ �� �߰�
			temp.Push(formula.Top());
			formula.Pop();
		}

		cout << "Error : ";

		for (int i = 0; temp.isEmpty() != 1; i++) {		//���� ������ �� ���
			cout << temp.Top();
			temp.Pop();
		}

		cout << endl;
		
		for (int i = 0; parentheses.isEmpty() != 1; i++) {	//�ӽ� ���ÿ� ��ȣ ������ �� �߰�
			temp.Push(parentheses.Top());
			parentheses.Pop();
		}

		cout << "Stack : ";

		for (int i = 0; temp.isEmpty() != 1; i++) {		//��ȣ ������ �� ���
			cout << temp.Top();
			temp.Pop();
		}
	}

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
