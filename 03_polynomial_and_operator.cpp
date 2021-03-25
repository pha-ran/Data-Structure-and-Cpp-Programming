#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Polynomial;
class Term;

//���׽�(termArray�� Term�� ������, arraySize == �Ҵ�� Term�� ��, count == ����� ���� ��)
class Polynomial {
  public:
	Polynomial();
	~Polynomial();
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, const Polynomial& p);

  private:
	Term* termArray;	//Term�� ������
	int arraySize;	//�Ҵ�� Term�� ��
	int count;		//����� ���� ��
};

//(c == ���, exp == ����)�� ��
class Term {
	friend Polynomial; //Polynomial�� Term�� ���� ����

  public:
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, const Polynomial& p);

  private:
	float c;		//���
	int exp;		//���� (exp >= 0)
};

int main() {

	Polynomial a, b, c, d, t;
	int x;

	//cout << ">Input polynomials a, b, c : ";
	//cin >> a;
	//cin >> b;
	//cin >> c;
	//cout << "A(x) = " << a << endl;
	//cout << "B(x) = " << b << endl;
	//cout << "C(x) = " << c << endl;
	//t = a * b;
	//d = t + c;
	//cout << "T(x) = " << t << endl;
	//cout << "D(x) = " << d << endl;
	//cout << ">Input x vlaue : ";
	//cin >> x;
	//cout << "A*B+C = " << d.evalPoly(x) << endl;

	return 0;
}

ostream& operator<<(ostream& os, const Polynomial& p) { // ��� ������ << (termArray�� ���ĵǾ��ִٰ� ����)
	for (int i = 0; i < p.count; i++) {
		if (i > 0 && p.termArray[i].c > 0) { os << "+"; } //�ι�° �׺��ʹ� ����� ����̸� + ���

		if (p.termArray[i].c != 1) { //����� 1�� �ƴϸ� ����� ��� (����� 0�� �ƴ϶�� ����)
			os << p.termArray[i].c;
		}

		if (p.termArray[i].exp > 1) { //������ 1���� ũ�� x^(����)�� ��� (������ 0���� ũ�ٰ� ����)
			os << "x^" << p.termArray[i].exp;
		}
		else if (p.termArray[i].exp == 1) {	//������ 1�̸� x�� ���
			os << "x";
		}
	}
	return os;
}

istream& operator>>(istream& is, const Polynomial& p) { // �Է� ������ >>
	//ToDo
	return is;
}

Polynomial::Polynomial() {	// Polynomial ������ (5�� ũ���� Term �Ҵ�)
	arraySize = 5;
	count = 0;
	termArray = new Term[arraySize];
}

Polynomial::~Polynomial() {	// Polynomial �Ҹ��� (termArray ��ȯ)
	if (termArray != NULL) { delete[] termArray; }
}
