#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <cmath>

using namespace std;

class Polynomial;
class Term;

//���׽�(termArray�� Term�� ������, arraySize == �Ҵ�� Term�� ��, count == ����� ���� ��)
class Polynomial {
  public:
	Polynomial();
	~Polynomial();
	void addTerm(const float f, const int i);
	Polynomial sMultPoly(const float c, const int e);
	Polynomial evalPoly(const int c);
	Polynomial operator+(const Polynomial& p);
	Polynomial operator*(const Polynomial& p);
	Polynomial& operator=(const Polynomial& p);
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, Polynomial& p);

  private:
	Term* termArray;	//Term�� ������
	int arraySize;	//�Ҵ�� Term�� ��
	int count;		//����� ���� ��

	void sortTermArray(Polynomial& p);
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
	//int x;
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

// ��� ������ << �����ε� (termArray�� ���ĵǾ��ִٰ� ����)
ostream& operator<<(ostream& os, const Polynomial& p) {
	for (int i = 0; i < p.count; i++) {
		if (i > 0 && p.termArray[i].c > 0) { os << "+"; } //�ι�° �׺��ʹ� ����� ����̸� + ���

		if (p.termArray[i].c != 1 && p.termArray[i].c != -1) { //����� 1�Ǵ� -1�� �ƴϸ� ����� ���
			os << p.termArray[i].c;
		}
		else if (p.termArray[i].c == -1 && p.termArray[i].exp > 0) { os << "-"; } //����� -1�̰� ������ 0���� ũ�� -���
		else if (p.termArray[i].c == 1 && p.termArray[i].exp == 0) { os << "1"; } //����� 1�̰� ������ 0�̸�(������� 1�̸�) 1���
		else if (p.termArray[i].c == -1 && p.termArray[i].exp == 0) { os << "-1"; } //����� -1�̰� ������ 0�̸�(������� -1�̸�) -1���

		if (p.termArray[i].exp > 1) { //������ 1���� ũ�� x^(����)�� ��� (������ 0���� ũ�ٰ� ����)
			os << "x^" << p.termArray[i].exp;
		}
		else if (p.termArray[i].exp == 1) {	//������ 1�̸� x�� ���
			os << "x";
		}
	}

	if (p.count == 0) { os << 0; } //���� ���� ��� 0���

	return os;
}

// �Է� ������ >> �����ε� (�������� (���, ����) ������ �Է°��� �޾Ƽ� ó��, �ܴ̿� ����)
istream& operator>>(istream& is, Polynomial& p) {
	float f;	//��� �ӽ� ����
	int i;		//���� �ӽ� ����
	string str;	//�Է� ���ڿ� �ӽ� ����
	smatch sm;	//��Ī�� ��� ����
	regex re("\\((-*[0-9]+),([0-9]+)\\)"); //(���,����) ������ ����ǥ���� (������� ������ �� �� ����)

	cin >> str;

	if (str == "#") { exit(0); }

	//�Է¹��� ���ڿ��� (���,����)���°� ���� ������ �ݺ�, (���,����)���¸� sm[0]�� ����, ����� sm[1], ������ sm[2]�� ����
	while (regex_search(str, sm, re)) {
		f = stof(sm[1].str()); //��� �κ��� float ������ ��ȯ
		i = stoi(sm[2].str()); //���� �κ��� int ������ ��ȯ

		if (f != 0 && i >= 0) {	//����� 0�� �ƴϰ�, ������ 0���� Ŭ ��쿡��
			p.addTerm(f, i); //���� �߰�
		}

		str = sm.suffix(); //���ڿ����� ���� (���,����)���� Ž��
	}

	return is;
}

// Polynomial ������ (5�� ũ���� Term �Ҵ�)
Polynomial::Polynomial() {
	arraySize = 5;
	count = 0;
	termArray = new Term[arraySize];
}

// Polynomial �Ҹ��� (termArray ��ȯ)
Polynomial::~Polynomial() {
	if (termArray != NULL) { delete[] termArray; }
}

//���� �߰� (arraySize���� ���� ������ arraySize + 5�� ���ο� �迭 �Ҵ�)
void Polynomial::addTerm(const float f, const int i) {
	if (arraySize == count) { //�Ҵ�� Term�� ���� ����� Term�� ���� ������
		arraySize += 5;	//arraySize�� 5 ����
		Term* tarr = new Term[arraySize];	//5��ŭ �þ ũ���� �ӽ� �迭 �Ҵ�
		copy(termArray, termArray + count, tarr);	//�ӽ� �迭�� �� ����
		delete[] termArray;	//���� �迭�� ����
		termArray = tarr;	//�ӽ� �迭�� �ּҰ� ����
	}
	termArray[count].c = f;
	termArray[count].exp = i;
	count++;
}
