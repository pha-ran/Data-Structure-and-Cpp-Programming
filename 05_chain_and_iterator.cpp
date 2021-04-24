#include <iostream>

using namespace std;

template<typename T> class ChainNode;
template<typename T> class Chain;

template<typename T> class ChainNode {
	template<typename U> friend class Chain;
  private:
	  T data;			//�Է°��� ����
	  ChainNode *link;	//���� ����� ������
  public:
	  ChainNode(T d, ChainNode* l) : data(d), link(l) {}	//����� ������
};

template<typename T> class Chain {
  private:
	  ChainNode<T> *first; //ù ����� ������
  public:
	  Chain() { first = NULL; }	//ü�� ������, �ʱⰪ NULL
	  //ü���� �� �տ� data ���� ������ ��带 ����
	  void push(T data) { first = new ChainNode<T>(data, first); }
	  //ü�� �ݺ���
	  class iterator {
	    private:
			ChainNode<T> *current;	//�ݺ��ڰ� ���� ����Ű�� ����� ������
	    public:
			//�ݺ��� ������
			iterator(ChainNode<T> *p) : current(p) {}
			//++�����ε� (���� ����) ������ ��� operator++(int) ����
			iterator& operator++ () {
				current = current->link;
				return *this;
			}
			//*�����ε� (����� ������ �ʵ� ����)
			T& operator* () { return current->data; }
			//!=�����ε�
			bool operator!= (const iterator it) { return current != it.current; }
			//==�����ε�
			bool operator== (const iterator it) { return current == it.current; }
	  };
	  //���� ����� �ݺ��� ��ȯ
	  iterator begin() { return iterator(first); }
	  //������ ����� �ݺ��� ��ȯ (NULL)
	  iterator end() { return iterator(NULL); }
};

int main() {
	Chain<int> a;	//int�� �����͸� ������ ü�� ����

	//�����͸� �Է¹޾� ���Ḯ��Ʈ a�� ���� : push() �Լ� ���
	cout << "�������� ���е� ���� ����Ʈ �Է� (���� ��ȣ # �Ǵ� ������ �ƴ� ���� �Է� �� �Է� ����)\n" << ">>";
	while (true) {
		int x;
		cin >> x;

		if (cin.fail()) {	//x�� # �Ǵ� ������ �ƴ� ���� �Է¹��� ���
			cin.clear();	//���� ���� �ʱ�ȭ
			fseek(stdin, 0, SEEK_END);	//���� �ʱ�ȭ
			break;	//�Է� ����
		}

		a.push(x);	//ü�ο� ��带 �߰�
	}
	if (a.begin() == a.end()) { cout << "error"; return 0; }	//ü���� ����� ��� ���� ó��

	//ü���� ��� ������ ���
	cout << "ü���� ������ : ";
	for (Chain<int>::iterator ait = a.begin(); ait != a.end(); ++ait) {	//ü���� ���ۺ��� ������
		cout << *ait << " ";	//���� ����� ������ ���
	}
	cout << endl;

	//ü���� �ּҰ� ���
	int minValue = 999999999;	//�ּҰ��� ū ���� ����
	for (Chain<int>::iterator ait = a.begin(); ait != a.end(); ++ait) {	//ü���� ���ۺ��� ������
		if (minValue > *ait) {	//���� ����� ���� minValue���� ���� ���
			minValue = *ait;	//minValue�� ���� ����� ������ ����
		}
	}
	cout << "ü���� �ּҰ� : " << minValue << endl;	//ü���� �ּҰ� ���
	return 0;
}
