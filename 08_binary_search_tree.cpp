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
	void addNode(T t);	//��� �߰�
	void ascendingOrder();	//�������� ���
	void descendingOrder();	//�������� ���
private:
	TreeNode<T>* root;
	//Stack
	class Stack {
	private:
		TreeNode<T>** stack;
		int top;
	public:
		Stack(int stackCapacity = 256) : top(-1) { stack = new TreeNode<T>*[stackCapacity]; }
		bool isEmpty() const { return top == -1; }		//������ ������� 1, �ƴϸ� 0 ����
		TreeNode<T>* Top() const { return stack[top]; }		//top ���Ҹ� ����
		void Push(TreeNode<T>* t) { stack[++top] = t; }	//������ �߰�
		void Pop() { top--; }		//top ���� ����
	};	//Stack
};

int main() {
	Tree<int> bst;	//Ʈ�� ����

	while (true) {
		int x;
		cin >> x;

		if (cin.fail()) {	//x�� # �Ǵ� ������ �ƴ� ���� �Է¹��� ���
			cin.clear();	//���� ���� �ʱ�ȭ
			fseek(stdin, 0, SEEK_END);	//���� �ʱ�ȭ
			break;	//�Է� ����
		}

		bst.addNode(x);//Ʈ���� ��带 �߰�
	}

	cout << "AO : ";
	bst.ascendingOrder();	//�������� ���
	cout << endl;

	cout << "DO : ";
	bst.descendingOrder();	//�������� ���
	cout << endl;

	return 0;
}

template <typename T>
void Tree<T>::addNode(T t) {
	TreeNode<T>* current = root;	//���� ���
	TreeNode<T>* parent = NULL;

	while (current != NULL) {
		parent = current;

		if (t < current->data) {	//���� �����ͺ��� ���� ���
			current = current->leftChild;
		}
		else if (current->data < t) {	//���� �����ͺ��� Ŭ ���
			current = current->rightChild;
		}
		else {
			cout << "�ߺ� ���� : " << t << endl;
			return;
		}
	}

	current = new TreeNode<T>(t);

	if (root != NULL) {	//��带 ����
		if (t < parent->data) {	//���ʿ� ����
			parent->leftChild = current;
		}
		else {	//�����ʿ� ����
			parent->rightChild = current;
		}
	}
	else {	//��Ʈ�� NULL, ��Ʈ�� ����
		root = current;
	}
}

template <typename T>
void Tree<T>::ascendingOrder() {
	Tree<T>::Stack stack;
	TreeNode<T>* current = root;	//���� ���

	while (true) {
		while (current != NULL) {	//NULL�� �ƴ� ����
			stack.Push(current);	//���ÿ� ���� ��� ����
			current = current->leftChild;	//���� �ڽ� ���� �̵�
		}
		if (stack.isEmpty()) {	//������ ������� ��� (���� ����)
			return;
		}
		current = stack.Top(); stack.Pop();	//���ÿ��� ���� ���� �̵�
		cout << current->data << " ";	//����� ������ �� ���
		current = current->rightChild;	//������ �ڽ� ���� �̵�
	}
}

template <typename T>
void Tree<T>::descendingOrder() {
	Tree<T>::Stack stack;
	TreeNode<T>* current = root;	//���� ���

	while (true) {
		while (current != NULL) {	//NULL�� �ƴ� ����
			stack.Push(current);	//���ÿ� ���� ��� ����
			current = current->rightChild;	//������ �ڽ� ���� �̵�
		}
		if (stack.isEmpty()) {	//������ ������� ��� (���� ����)
			return;
		}
		current = stack.Top(); stack.Pop();	//���ÿ��� ���� ���� �̵�
		cout << current->data << " ";	//����� ������ �� ���
		current = current->leftChild;	//���� �ڽ� ���� �̵�
	}
}
