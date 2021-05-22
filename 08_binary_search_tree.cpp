#include <iostream>

using namespace std;

template <typename T> class Tree;
template <typename T> class TreeNode;

template <typename T>
class TreeNode {
	friend class Tree<T>;
public:
	TreeNode(T d = 0) : data(d), leftChild(0), rightChild(0) {}
private:
	T data;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightChild;
};

template <typename T>
class Tree {
public:
	Tree(TreeNode<T>* r = 0) { root = r; }
	void addNode(T t);	//노드 추가
	void ascendingOrder();	//오름차순 출력
	void descendingOrder();	//내림차순 출력
private:
	TreeNode<T>* root;
	//Stack
	class Stack {
	private:
		TreeNode<T>** stack;
		int top;
	public:
		Stack(int stackCapacity = 256) : top(-1) { stack = new TreeNode<T>*[stackCapacity]; }
		bool isEmpty() const { return top == -1; }		//스택이 비었으면 1, 아니면 0 리턴
		TreeNode<T>* Top() const { return stack[top]; }		//top 원소를 리턴
		void Push(TreeNode<T>* t) { stack[++top] = t; }	//스택을 추가
		void Pop() { top--; }		//top 원소 제거
	};	//Stack
};

int main() {
	Tree<int> bst;	//트리 생성

	while (true) {
		int x;
		cin >> x;

		if (cin.fail()) {	//x가 # 또는 정수가 아닌 값을 입력받을 경우
			cin.clear();	//오류 상태 초기화
			fseek(stdin, 0, SEEK_END);	//버퍼 초기화
			break;	//입력 종료
		}

		bst.addNode(x);//트리에 노드를 추가
	}

	cout << "AO : ";
	bst.ascendingOrder();	//오름차순 출력
	cout << endl;

	cout << "DO : ";
	bst.descendingOrder();	//내림차순 출력
	cout << endl;

	return 0;
}

template <typename T>
void Tree<T>::addNode(T t) {
	TreeNode<T>* current = root;	//현재 노드
	TreeNode<T>* parent = NULL;

	while (current != NULL) {
		parent = current;

		if (t < current->data) {	//현재 데이터보다 작을 경우
			current = current->leftChild;
		}
		else if (current->data < t) {	//현재 데이터보다 클 경우
			current = current->rightChild;
		}
		else {
			cout << "중복 원소 : " << t << endl;
			return;
		}
	}

	current = new TreeNode<T>(t);

	if (root != NULL) {	//노드를 생성
		if (t < parent->data) {	//왼쪽에 생성
			parent->leftChild = current;
		}
		else {	//오른쪽에 생성
			parent->rightChild = current;
		}
	}
	else {	//루트가 NULL, 루트를 생성
		root = current;
	}
}

template <typename T>
void Tree<T>::ascendingOrder() {
	Tree<T>::Stack stack;
	TreeNode<T>* current = root;	//현재 노드

	while (true) {
		while (current != NULL) {	//NULL이 아닌 동안
			stack.Push(current);	//스택에 현재 노드 삽입
			current = current->leftChild;	//왼쪽 자식 노드로 이동
		}
		if (stack.isEmpty()) {	//스택이 비어있을 경우 (종료 조건)
			return;
		}
		current = stack.Top(); stack.Pop();	//스택에서 꺼낸 노드로 이동
		cout << current->data << " ";	//노드의 데이터 값 출력
		current = current->rightChild;	//오른쪽 자식 노드로 이동
	}
}

template <typename T>
void Tree<T>::descendingOrder() {
	Tree<T>::Stack stack;
	TreeNode<T>* current = root;	//현재 노드

	while (true) {
		while (current != NULL) {	//NULL이 아닌 동안
			stack.Push(current);	//스택에 현재 노드 삽입
			current = current->rightChild;	//오른쪽 자식 노드로 이동
		}
		if (stack.isEmpty()) {	//스택이 비어있을 경우 (종료 조건)
			return;
		}
		current = stack.Top(); stack.Pop();	//스택에서 꺼낸 노드로 이동
		cout << current->data << " ";	//노드의 데이터 값 출력
		current = current->leftChild;	//왼쪽 자식 노드로 이동
	}
}
