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
	void inOrderPrintDataAndSum();	//���� ��ȸ
	void postOrderPrintDataAndSum();	//���� ��ȸ
private:
	TreeNode<T>* root;
	//Stack
	class Stack {
	private:
		TreeNode<T>** stack;
		int top;
	public:
		Stack(int stackCapacity = 32) : top(-1) { stack = new TreeNode<T>*[stackCapacity]; }
		bool isEmpty() const { return top == -1; }		//������ ������� 1, �ƴϸ� 0 ����
		TreeNode<T>* Top() const { return stack[top]; }		//top ���Ҹ� ����
		void Push(TreeNode<T>* t) { stack[++top] = t; }	//������ �߰�
		void Pop() { top--; }		//top ���� ����
	};	//Stack
};

int main() {
	string input, * sTree;
	int n = 0;	//�Է��� ���� ��

	sTree = new string[32];	//�ִ� ���̰� 5�� ���� Ʈ���� �迭 ǥ�� (�ִ� ��� ���� = 2^5 - 1 = 31)
	sTree[n] = "NULL";

	for (cin >> input; input != "#"; cin >> input) {	//����Ʈ���� �迭 ǥ������ ������ �Է�
		n++;
		sTree[n] = input;
	}

	for (int j = 2; j <= n; j++) {	//NULL�� �ƴ� ����� �θ� NULL�ϰ�� ���� ó��
		if (sTree[j] != "NULL" && sTree[j / 2] == "NULL") {
			cout << "error" << endl;
			return 0;
		}
	}

	TreeNode<int>* node[32] = { NULL, };	//Ʈ�� ������ ���� ��� �迭

	if (n == 0 || sTree[1] == "NULL") {	//�Է��� ���ų� ù ��尡 NULL�� ��� ���� ���� Ʈ��
		node[1] = NULL;
	}
	else {	//���� ���� Ʈ���� �ƴ� ��� Ʈ���� ����
		node[1] = new TreeNode<int>(stoi(sTree[1]));	//root��� ����

		for (int j = 2; j <= n; j++) {	//root�� ��� �ڽ� ���
			if (sTree[j] != "NULL") {	//�Է°��� NULL�� �ƴ� ���
				node[j] = new TreeNode<int>(stoi(sTree[j]));	//��带 ����

				if (j & 1) {	//Ȧ�� ��°�� ��� �θ��� RightChild�� �߰�
					node[j / 2]->setRightChild(node[j]);
				}
				else {	//¦�� ��°�� ��� �θ��� LeftChild�� �߰�
					node[j / 2]->setLeftChild(node[j]);
				}
			}
		}
	}

	Tree<int> tree(node[1]);	//Ʈ���� ����

	cout << "\n���� ��ȸ ��� : ";
	tree.inOrderPrintDataAndSum();

	cout << "\n���� ��ȸ ��� : ";
	tree.postOrderPrintDataAndSum();

	return 0;
}

template<typename T>
void Tree<T>::inOrderPrintDataAndSum() {
	Tree<T>::Stack stack;
	TreeNode<T>* current = root;	//���� ���
	int sum = 0;

	while (true) {
		while (current != NULL) {	//NULL�� �ƴ� ����
			stack.Push(current);	//���ÿ� ���� ��� ����
			current = current->leftChild;	//LeftChild�� �̵�
		}
		if (stack.isEmpty()) {	//������ ������� ��� (���� ����)
			cout << "\nƮ�� �� ���� ���� �� : " << sum << endl;
			return;
		}
		current = stack.Top(); stack.Pop();	//���ÿ��� ���� ���� �̵�
		sum += current->data;	//����� ������ �� ����
		cout << current->data << " ";	//����� ������ �� ���
		current = current->rightChild;	//������ �ڽ� ���� �̵�
	}
}

template<typename T>
void Tree<T>::postOrderPrintDataAndSum() {
	Tree<T>::Stack stack;
	TreeNode<T>* current = root;	//���� ���
	TreeNode<T>* last = NULL;	//������ ��� ���
	int sum = 0;

	while (true) {
		if (current != last &&	//���� ��尡 ������ ��� ���� �ٸ� ���
			current != NULL) {	//���� ��尡 NULL�� �ƴ� ���
			stack.Push(current);	//���ÿ� ���� ��� ����

			while (current != NULL) {	//NULL�� �ƴ� ����
				//���ÿ� NULL�� �ƴ� ���� ����� RightChild ��� ����
				if (current->rightChild != NULL) { stack.Push(current->rightChild); }
				//���ÿ� NULL�� �ƴ� ���� ����� LeftChild ��� ����
				if (current->leftChild != NULL) { stack.Push(current->leftChild); }
				current = current->leftChild;	//LeftChild�� �̵�
			}
		}

		if (stack.isEmpty()) {	//������ ������� ��� (���� ����)
			cout << "\nƮ�� �� ���� ���� �� : " << sum << endl;
			return;
		}
		else {	//������ ������� ���� ���
			current = stack.Top(); stack.Pop();	//���ÿ��� ���� ���� �̵�

			//10 20 30 NULL NULL 40 # �� ���� �Է��� ó���ϱ� ����
			if (current->leftChild != NULL &&	//LeftChild�� NULL�� �ƴ� ���
				current->rightChild == NULL &&	//RightChild�� NULL�� ���
				current->leftChild != last) {	//LeftChild�� ���� ��µ��� �ʾ��� ���
				if (current != NULL) {
					stack.Push(current);	//���ÿ� ���� ��� ����
					current = current->leftChild;	//LeftChild�� �̵�
				}
			}

			if (current->rightChild == last ||	//���� ����� RightChild�� �̹� ����� ���� ���
				current->rightChild == NULL) {	//���� ����� RightChild�� NULL�� ���
				sum += current->data;	//����� ������ �� ����
				cout << current->data << " ";	//����� ������ �� ���
				last = current;	//������ ��� ��带 ���� ���� ����
			}
		}
	}
}
