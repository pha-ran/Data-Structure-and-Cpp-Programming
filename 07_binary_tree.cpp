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
private:
	TreeNode<T>* root;
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

	for (int j = 2; j <= n; j++) {	//�θ� NULL�ϰ�� ���� ó��
		if (sTree[j / 2] == "NULL") {
			cout << "error" << endl;
			return 0;
		}
	}

	TreeNode<int>* node[32] = { NULL, };	//Ʈ�� ������ ���� ��� �迭

	if (n == 0 || sTree[1] == "NULL") {	//�Է��� ���ų� ù ��尡 NULL�� ��� ���� ���� Ʈ��
		node[1] = NULL;
	}
	else {	//���� ���� Ʈ���� �ƴ� ��� Ʈ���� ����
		node[1] = new TreeNode(stoi(sTree[1]));	//root��� ����

		for (int j = 2; j <= n; j++) {	//root�� ��� �ڽ� ���
			if (sTree[j] != "NULL") {	//�Է°��� NULL�� �ƴ� ���
				node[j] = new TreeNode(stoi(sTree[j]));	//��带 ����

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

	return 0;
}
