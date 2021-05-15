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
	int n = 0;	//입력한 값의 수

	sTree = new string[32];	//최대 깊이가 5인 이진 트리의 배열 표현 (최대 노드 개수 = 2^5 - 1 = 31)
	sTree[n] = "NULL";

	for (cin >> input; input != "#"; cin >> input) {	//이진트리의 배열 표현으로 정수를 입력
		n++;
		sTree[n] = input;
	}

	for (int j = 2; j <= n; j++) {	//부모가 NULL일경우 예외 처리
		if (sTree[j / 2] == "NULL") {
			cout << "error" << endl;
			return 0;
		}
	}

	TreeNode<int>* node[32] = { NULL, };	//트리 구성을 위한 노드 배열

	if (n == 0 || sTree[1] == "NULL") {	//입력이 없거나 첫 노드가 NULL일 경우 공백 이진 트리
		node[1] = NULL;
	}
	else {	//공백 이진 트리가 아닐 경우 트리를 구성
		node[1] = new TreeNode(stoi(sTree[1]));	//root노드 생성

		for (int j = 2; j <= n; j++) {	//root의 모든 자식 노드
			if (sTree[j] != "NULL") {	//입력값이 NULL이 아닐 경우
				node[j] = new TreeNode(stoi(sTree[j]));	//노드를 생성

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

	return 0;
}
