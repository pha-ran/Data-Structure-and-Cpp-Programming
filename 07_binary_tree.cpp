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
	void setLeftChild(TreeNode<T>* l) { leftChild = l; }
	void setRightChild(TreeNode<T>* r) { rightChild = r; }
private:
	T data;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightChild;
};

template <typename T>
class Tree {
public:
	//ToDo
private:
	TreeNode<T>* root;
};

int main() {
	string input, * sTree;
	int c = 256, i = 0;

	sTree = new string[c];
	sTree[i] == "NULL";
	i++;

	for (cin >> input; input != "#"; cin >> input) {
		sTree[i] = input;
		i++;
	}

	for (int j = 2; j < i; j++) {	//何葛啊 NULL老版快 抗寇 贸府
		if (sTree[j / 2] == "NULL") {
			cout << j << " error" << endl;
			return 0;
		}
	}

	//捞柳飘府 备己

	return 0;
}
