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
	CircularListNode* link;	//���� ����� ������
public:
	//������
	CircularListNode(int c = 0, int e = 0, CircularListNode* next = 0) {
		data.Set(c, e);
		link = next;
	}
};	//CircularListNode

class CircularListWithHeader {
private:
	CircularListNode* head;
	CircularListNode* tail;
public:
	//������
	CircularListWithHeader() {
		head = new CircularListNode(0, -1, 0);
		head->link = head;
		tail = head;
	}
	//��带 �߰�
	void addNode(int c, int e) {
		tail->link = new CircularListNode(c, e, head);
		tail = tail->link;
	}

	//�ݺ���
	class iterator {
	private:
		CircularListNode* current;	//�ݺ��ڰ� ����Ű�� ����� ������
	public:
		//������
		iterator(CircularListNode* p) : current(p) {}
		//++�����ε� (���� ����)
		iterator& operator++ () {
			current = current->link;	//���� ���� �̵�
			return *this;
		}
		//*�����ε� (����� ������ �ʵ� ����)
		Term& operator* () { return current->data; }
		//!=�����ε�
		bool operator!= (const iterator it) { return current != it.current; }
		//==�����ε�
		bool operator== (const iterator it) { return current == it.current; }
	};	//iterator

	//��� ����� �ݺ��� ��ȯ
	iterator Head() const { return iterator(head); }
	//��� ���� ����� �ݺ��� ��ȯ
	iterator begin() const { return iterator(head->link); }
};	//CircularListWithHeader

class Polynomial {
private:
	CircularListWithHeader* list;
public:
	Polynomial() { list = new CircularListWithHeader(); }
	void addTerm(const int c, const int e) { list->addNode(c, e); }		//���� �߰�
	const bool isEmpty() { return list->begin() == list->Head(); }
	const CircularListNode sMultPoly(const int c, const int e);	//���׽��� ���� ����
	const int evalPoly(const int c);			//���׽��� ���� ���
	//���׽� ���� ����
	const Polynomial operator+(const Polynomial& p);
	const Polynomial operator*(const Polynomial& p);	//���׽��� �� ����
	Polynomial& operator=(const Polynomial& p);			//���׽� ���� ����
	friend ostream& operator<<(ostream& os, const Polynomial& p);	// ��� ������ << �����ε� (��� ���׽��� ���� )
	// �Է� ������ >> �����ε� (�������� (���, ����) ������ �Է°��� �޾Ƽ� ó��, �ܴ̿� ����)
	friend istream& operator>>(istream& is, Polynomial& p);
	void sortList();	//���� ������ ������������ �����ϰ� �������� ����� ����� ����
};	//Polynomial

int main() {

	while (true) {
		Polynomial a, b, c, d, t;
		int x;
		cout << ">Input polynomials a, b, c : ";	//(���, ����)������ �������� �Է°��� ó��, �ܴ̿� ���� (���� ���� ��� ���� ó��)
		cin >> a;									//#�Է½� ���α׷� ����
		cin >> b;
		cin >> c;

		if (a.isEmpty() || b.isEmpty() || c.isEmpty()) { //a, b, c�� �ϳ��� ���� ���� ��� ����
			cout << "error" << endl << endl;
			cin.clear();		//���� ���� �ʱ�ȭ
			fseek(stdin, 0, SEEK_END);	//���� �ʱ�ȭ
			continue;
		}

		cout << "A(x) = " << a << endl;
		cout << "B(x) = " << b << endl;
		cout << "C(x) = " << c << endl;
		/*
		t = a * b;
		d = t + c;
		cout << "T(x) = " << t << endl;
		cout << "D(x) = " << d << endl;
		cout << ">Input x vlaue : ";
		cin >> x;

		if (cin.fail()) {		//X�� ���ڰ� �ƴ� ��� ����
			cout << "error" << endl << endl;
			cin.clear();		//���� ���� �ʱ�ȭ
			fseek(stdin, 0, SEEK_END);	//���� �ʱ�ȭ
			continue;
		}

		cout << "A*B+C = " << d.evalPoly(x);
		cout << endl << endl;
		*/
	}

	return 0;
}

// ��� ������ << �����ε�
ostream& operator<<(ostream& os, const Polynomial& p) {
	for (CircularListWithHeader::iterator it = p.list->begin(); it != p.list->Head(); ++it) {
		if (it != p.list->begin() && (*it).coef > 0) { os << "+"; } //�ι�° �׺��ʹ� ����� ����̸� + ���

		if ((*it).coef != 1 && (*it).exp != -1) { //����� 1�Ǵ� -1�� �ƴϸ� ����� ���
			os << (*it).coef;
		}
		else if ((*it).coef == -1 && (*it).exp > 0) { os << "-"; } //����� -1�̰� ������ 0���� ũ�� -���
		else if ((*it).coef == 1 && (*it).exp == 0) { os << "1"; } //����� 1�̰� ������ 0�̸�(������� 1�̸�) 1���
		else if ((*it).coef == -1 && (*it).exp == 0) { os << "-1"; } //����� -1�̰� ������ 0�̸�(������� -1�̸�) -1���

		if ((*it).exp > 1) { //������ 1���� ũ�� x^(����)�� ��� (������ 0���� ũ�ٰ� ����)
			os << "x^" << (*it).exp;
		}
		else if ((*it).exp == 1) {	//������ 1�̸� x�� ���
			os << "x";
		}
	}

	if (p.list->begin() == p.list->Head()) { os << "0"; }	//���� ���� ��� 0���

	return os;
}

// �Է� ������ >> �����ε� (�������� (���, ����) ������ �Է°��� �޾Ƽ� ó��, �ܴ̿� ����)
istream& operator>>(istream& is, Polynomial& p) {
	int c;	//��� �ӽ� ����
	int i;		//���� �ӽ� ����
	string str;	//�Է� ���ڿ� �ӽ� ����
	smatch sm;	//��Ī�� ��� ����
	regex re("\\((-?[0-9]+),([0-9]+)\\)"); //(���,����) ������ ����ǥ���� (������� ������ �� �� ����)

	cin >> str;

	if (str == "#") { exit(0); } //#�� �Է¹����� ���α׷� ����

	//�Է¹��� ���ڿ��� (���,����)���°� ���� ������ �ݺ�, (���,����)���¸� sm[0]�� ����, ����� sm[1], ������ sm[2]�� ����
	while (regex_search(str, sm, re)) {
		c = stoi(sm[1].str()); //��� �κ��� int ������ ��ȯ
		i = stoi(sm[2].str()); //���� �κ��� int ������ ��ȯ

		if (c != 0 && i >= 0) {	//����� 0�� �ƴϰ�, ������ 0���� Ŭ ��쿡��
			p.addTerm(c, i); //���� �߰�
		}

		str = sm.suffix(); //���ڿ����� ���� (���,����)���� Ž��
	}

	//p.sortList();	//�Է¹��� �׵��� ���� �� ������ ���

	return is;
}

//���׽� ���� ����
Polynomial& Polynomial::operator=(const Polynomial& p) {
	if (this != &p) {	//�ڱ� �ڽ��� �����ϴ°� �ƴ� ���
		list = new CircularListWithHeader();	//���ο� ����Ʈ �Ҵ�

		for (CircularListWithHeader::iterator it = p.list->begin(); it != p.list->Head(); ++it) {
			addTerm((*it).coef, (*it).exp);	//������ �� ����
		}
	}

	return *this;
}
