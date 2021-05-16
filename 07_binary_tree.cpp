#include <iostream>
#include <string>

using namespace std;

template <typename T> class Tree;
template <typename T> class TreeNode;

template <typename T>
class TreeNode {
	friend class Tree<T>;
public:
	TreeNode(T d = 0) : data(d), leftChild(0), rightChild(0) {}
	void setLeftChild(TreeNode<T>* L) { leftChild = L; }
	void setRightChild(TreeNode<T>* R) { rightChild = R; }
private:
	T data;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightChild;
};

template <typename T>
class Tree {
public:
	Tree(TreeNode<T>* r) { root = r; }
	void inOrderPrintDataAndSum();	//중위 순회
	void postOrderPrintDataAndSum();	//후위 순회
private:
	TreeNode<T>* root;
	//Stack
	class Stack {
	private:
		TreeNode<T>** stack;
		int top;
	public:
		Stack(int stackCapacity = 32) : top(-1) { stack = new TreeNode<T>*[stackCapacity]; }
		bool isEmpty() const { return top == -1; }		//스택이 비었으면 1, 아니면 0 리턴
		TreeNode<T>* Top() const { return stack[top]; }		//top 원소를 리턴
		void Push(TreeNode<T>* t) { stack[++top] = t; }	//스택을 추가
		void Pop() { top--; }		//top 원소 제거
	};	//Stack
};

int main() {
	string input, * sTree;
	int n = 0;	//입력한 값의 수

	sTree = new string[32];	//최대 깊이가 5인 이진 트리의 배열 표현 (최대 노드 개수 = 2^5 - 1 = 31)
	sTree[n] = "NULL";

	for (cin >> input; input != "#"; cin >> input) {	//이진트리의 배열 표현으로 정수를 입력
		n++;
		sTree[n] = input;
	}

	for (int j = 2; j <= n; j++) {	//NULL이 아닌 노드의 부모가 NULL일경우 예외 처리
		if (sTree[j] != "NULL" && sTree[j / 2] == "NULL") {
			cout << "error" << endl;
			return 0;
		}
	}

	TreeNode<int>* node[32] = { NULL, };	//트리 구성을 위한 노드 배열

	if (n == 0 || sTree[1] == "NULL") {	//입력이 없거나 첫 노드가 NULL일 경우 공백 이진 트리
		node[1] = NULL;
	}
	else {	//공백 이진 트리가 아닐 경우 트리를 구성
		node[1] = new TreeNode<int>(stoi(sTree[1]));	//root노드 생성

		for (int j = 2; j <= n; j++) {	//root의 모든 자식 노드
			if (sTree[j] != "NULL") {	//입력값이 NULL이 아닐 경우
				node[j] = new TreeNode<int>(stoi(sTree[j]));	//노드를 생성

				if (j & 1) {	//홀수 번째일 경우 부모의 RightChild로 추가
					node[j / 2]->setRightChild(node[j]);
				}
				else {	//짝수 번째일 경우 부모의 LeftChild로 추가
					node[j / 2]->setLeftChild(node[j]);
				}
			}
		}
	}

	Tree<int> tree(node[1]);	//트리를 생성

	cout << "\n중위 순회 결과 : ";
	tree.inOrderPrintDataAndSum();

	cout << "\n후위 순회 결과 : ";
	tree.postOrderPrintDataAndSum();

	return 0;
}

template<typename T>
void Tree<T>::inOrderPrintDataAndSum() {
	Tree<T>::Stack stack;
	TreeNode<T>* current = root;	//현재 노드
	int sum = 0;

	while (true) {
		while (current != NULL) {	//NULL이 아닌 동안
			stack.Push(current);	//스택에 현재 노드 삽입
			current = current->leftChild;	//LeftChild로 이동
		}
		if (stack.isEmpty()) {	//스택이 비어있을 경우 (종료 조건)
			cout << "\n트리 내 정수 값의 합 : " << sum << endl;
			return;
		}
		current = stack.Top(); stack.Pop();	//스택에서 꺼낸 노드로 이동
		sum += current->data;	//노드의 데이터 값 누적
		cout << current->data << " ";	//노드의 데이터 값 출력
		current = current->rightChild;	//오른쪽 자식 노드로 이동
	}
}

template<typename T>
void Tree<T>::postOrderPrintDataAndSum() {
	Tree<T>::Stack stack;
	TreeNode<T>* current = root;	//현재 노드
	TreeNode<T>* last = NULL;	//마지막 출력 노드
	int sum = 0;

	while (true) {
		if (current != last &&	//현재 노드가 마지막 출력 노드와 다를 경우
			current != NULL) {	//현재 노드가 NULL이 아닐 경우
			stack.Push(current);	//스택에 현재 노드 삽입

			while (current != NULL) {	//NULL이 아닌 동안
				//스택에 NULL이 아닌 현재 노드의 RightChild 노드 삽입
				if (current->rightChild != NULL) { stack.Push(current->rightChild); }
				//스택에 NULL이 아닌 현재 노드의 LeftChild 노드 삽입
				if (current->leftChild != NULL) { stack.Push(current->leftChild); }
				current = current->leftChild;	//LeftChild로 이동
			}
		}

		if (stack.isEmpty()) {	//스택이 비어있을 경우 (종료 조건)
			cout << "\n트리 내 정수 값의 합 : " << sum << endl;
			return;
		}
		else {	//스택이 비어있지 않을 경우
			current = stack.Top(); stack.Pop();	//스택에서 꺼낸 노드로 이동

			//10 20 30 NULL NULL 40 # 과 같은 입력을 처리하기 위해
			if (current->leftChild != NULL &&	//LeftChild가 NULL이 아닐 경우
				current->rightChild == NULL &&	//RightChild가 NULL인 경우
				current->leftChild != last) {	//LeftChild가 아직 출력되지 않았을 경우
				if (current != NULL) {
					stack.Push(current);	//스택에 현재 노드 삽입
					current = current->leftChild;	//LeftChild로 이동
				}
			}

			if (current->rightChild == last ||	//현재 노드의 RightChild가 이미 출력이 됐을 경우
				current->rightChild == NULL) {	//현재 노드의 RightChild가 NULL일 경우
				sum += current->data;	//노드의 데이터 값 누적
				cout << current->data << " ";	//노드의 데이터 값 출력
				last = current;	//마지막 출력 노드를 현재 노드로 설정
			}
		}
	}
}
