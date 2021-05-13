#include <iostream>
#include <string>

using namespace std;

template <typename T> class Tree;
template <typename T> class TreeNode;

template <typename T>
class TreeNode {
	friend class Tree<T>;
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
	string input, *Tree;
	int c = 256, i = 0;

	Tree = new string[c];
	Tree[i] == "NULL";
	i++;

	for (cin >> input; input != "#"; cin >> input) {
		Tree[i] = input;
		i++;
	}

	if (Tree[1] == "NULL") {
		cout << "error" << endl;
		return 0;
	}

	for (int j = 2; j < i; j++) {
		//부모 노드가 NULL인지 확인
	}

	return 0;
}
