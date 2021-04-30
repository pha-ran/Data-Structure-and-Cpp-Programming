#include <iostream>
#include <string>
#include <regex>
#include <cmath>

using namespace std;

struct Term;
class CircularListNode;
class CircularListWithHeader;
class Polynomial;

struct Term {
	int coef;	//���
	int exp;	//����

	//����� ���� ����
	Term Set(int c, int e) {
		coef = c;
		exp = e;
		return *this;
	}
};	//Term

class CircularListNode {
	friend class CircularListWithHeader;
private:
	Term data;	//����� ������
	CircularListNode *link;	//���� ����� ������
public:
	//������
	CircularListNode(int c = 0, int e = 0, CircularListNode* next = 0) {
		data.Set(c, e);
		link = next;
	}
};	//CircularListNode

class CircularListWithHeader {
	friend class Polynomial;
private:
	CircularListNode* head;
public:
	//������
	CircularListWithHeader() {
		head = new CircularListNode(0, -1, 0);
		head->link = head;
	}

	//�ݺ���
	class iterator {
	private:
	public:
		//++�����ε� (���� ����)
		iterator& operator++ ();
		//*�����ε� (����� ������ �ʵ� ����)
		Term& operator* ();
		//!=�����ε�
		bool operator!= (const iterator it);
		//==�����ε�
		bool operator== (const iterator it);
	};	//iterator

	//��� ����� �ݺ��� ��ȯ
	iterator begin();
};	//CircularListWithHeader

class Polynomial {
private:
	CircularListWithHeader poly;
public:
	void addTerm(const int c, const int i);		//���� �߰�
	const Polynomial sMultPoly(const int c, const int e);	//���׽��� ���� ����
	const int evalPoly(const int c);			//���׽��� ���� ���
	const Polynomial operator+(const Polynomial& p);	//���׽� ���� ����
	const Polynomial operator*(const Polynomial& p);	//���׽��� �� ����
	Polynomial& operator=(const Polynomial& p);			//���׽� ���� ����
	friend ostream& operator<<(ostream& os, const Polynomial& p);	// ��� ������ << �����ε�
	// �Է� ������ >> �����ε� (�������� (���, ����) ������ �Է°��� �޾Ƽ� ó��)
	friend istream& operator>>(istream& is, Polynomial& p);
};	//Polynomial

int main() {
	

	return 0;
}