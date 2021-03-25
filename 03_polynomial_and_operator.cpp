#include <iostream>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

class Polynomial;
class Term;

//���׽�(termArray�� Term�� ������, arraySize == �Ҵ�� Term�� ��, count == ����� ���� ��)
class Polynomial {
public:
	Polynomial();
	~Polynomial();
	void addTerm(const float f, const int i);
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, Polynomial& p);

private:
	Term* termArray;	//Term�� ������
	int arraySize;	//�Ҵ�� Term�� ��
	int count;		//����� ���� ��
};

//(c == ���, exp == ����)�� ��
class Term {
	friend Polynomial; //Polynomial�� Term�� ���� ����
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, Polynomial& p);

private:
	float c;		//���
	int exp;		//���� (exp >= 0)
};

int main() {
	Polynomial a, b, c, d, t;
	int x;

	cout << ">Input polynomials a, b, c : ";
	cin >> a;
	cin >> b;
	cin >> c;
	cout << "A(x) = " << a << endl;
	cout << "B(x) = " << b << endl;
	cout << "C(x) = " << c << endl;
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
		else if (p.termArray[i].c == 1 && p.termArray[i].exp == 0) { os << "1"; } //����� 1�̰� ������ 0�̸�(������̸�) 1���

		if (p.termArray[i].exp > 1) { //������ 1���� ũ�� x^(����)�� ��� (������ 0���� ũ�ٰ� ����)
			os << "x^" << p.termArray[i].exp;
		}
		else if (p.termArray[i].exp == 1) {	//������ 1�̸� x�� ���
			os << "x";
		}
	}
	return os;
}

istream& operator>>(istream& is, Polynomial& p) { // �Է� ������ >>
	float f;	//��� �ӽ� ����
	int i;		//���� �ӽ� ����
	string str;	//�Է� ���ڿ� �ӽ� ����
	smatch sm;	//��Ī�� ��� ����
	regex re("\\((-*[0-9]+),([0-9]+)\\)"); //(���,����) ������ ����ǥ���� (������� -��ȣ ó��)

	cin >> str;

	if (str == "#") { exit(0); }

	while (regex_search(str, sm, re)) {
		f = stof(sm[1].str());
		i = stoi(sm[2].str());

		p.addTerm(f, i);

		str = sm.suffix(); //���� ���ڿ� Ž��
	}

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

void Polynomial::addTerm(const float f, const int i) {
	termArray[count].c = f;
	termArray[count].exp = i;
	count++;
}
