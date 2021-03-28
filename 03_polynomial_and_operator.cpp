#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <cmath>
#include <cstdio>

using namespace std;

class Polynomial;
class Term;
ostream& operator<<(ostream& os, const Polynomial& p);
istream& operator>>(istream& is, Polynomial& p);

//���׽�(termArray�� Term�� ������, arraySize == �Ҵ�� Term�� ��, count == ����� ���� ��)
class Polynomial {
  public:
	Polynomial();
	void addTerm(const int c, const int i);		//���� �߰� (arraySize���� ���� ������ arraySize + 5�� ���ο� �迭 �Ҵ� �� ����)
	const Polynomial sMultPoly(const int c, const int e);	//���׽��� ���� ����
	const int evalPoly(const int c);			//���׽��� ���� ���
	const Polynomial operator+(const Polynomial& p);	//���׽� ���� ����
	const Polynomial operator*(const Polynomial& p);	//���׽��� �� ����
	Polynomial& operator=(const Polynomial& p);			//���׽� ���� ����
	friend ostream& operator<<(ostream& os, const Polynomial& p);	// ��� ������ << �����ε� (���� ���� ��� 0���� ���)
	// �Է� ������ >> �����ε� (�������� (���, ����) ������ �Է°��� �޾Ƽ� ó��, �ܴ̿� ����, ���� ���� ��� 0���� ���)
	friend istream& operator>>(istream& is, Polynomial& p);
	const int getCount() { return count; }

  private:
	Term* termArray;	//Term�� ������
	int arraySize;	//�Ҵ�� Term�� ��
	int count;		//����� ���� ��

	void sortTermArray();			//���� ������ ������������ �����ϰ� �������� ����� ����� ����
};

//(c == ���, exp == ����)�� ��
class Term {
	friend Polynomial; //Polynomial�� Term�� ���� ����
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, Polynomial& p);

  private:
	int c;		//���
	int exp;	//���� (exp >= 0)
};

int main() {

	while (true) {
		Polynomial a, b, c, d, t;
		int x;
		cout << ">Input polynomials a, b, c : ";	//(���, ����)������ �������� �Է°��� ó��, �ܴ̿� ���� (���� ���� ��� 0���� ���)
		cin >> a;									//#�Է½� ���α׷� ����
		cin >> b;
		cin >> c;

		if (a.getCount() == 0 || b.getCount() == 0 || c.getCount() == 0) { //a, b, c�� �ϳ��� ���� ���� ��� ����
			cout << "error" << endl << endl;
			cin.clear();		//���� ���� �ʱ�ȭ
			fseek(stdin, 0, SEEK_END);	//���� �ʱ�ȭ
			continue;
		}

		cout << "A(x) = " << a << endl;
		cout << "B(x) = " << b << endl;
		cout << "C(x) = " << c << endl;
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
	}

	return 0;
}

// ��� ������ << �����ε� (���� ���� ��� 0���� ���)
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

// �Է� ������ >> �����ε� (�������� (���, ����) ������ �Է°��� �޾Ƽ� ó��, �ܴ̿� ����, ���� ���� ��� 0���� ���)
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

	p.sortTermArray();	//�Է¹��� �׵��� ���� �� ������ ���

	return is;
}

// Polynomial ������ (5�� ũ���� Term �Ҵ�)
Polynomial::Polynomial() {
	arraySize = 5;
	count = 0;
	termArray = new Term[arraySize];
}

//���� �߰� (arraySize���� ���� ������ arraySize + 5�� ���ο� �迭 �Ҵ� �� ����)
void Polynomial::addTerm(const int c, const int i) {
	if (arraySize == count) { //�Ҵ�� Term�� ���� ����� Term�� ���� ������
		arraySize += 5;	//arraySize�� 5 ����
		Term* tarr = new Term[arraySize];	//5��ŭ �þ ũ���� �ӽ� �迭 �Ҵ�
		copy(termArray, termArray + count, tarr);	//�ӽ� �迭�� �� ����
		delete[] termArray;	//���� �迭�� ����
		termArray = tarr;	//�ӽ� �迭�� �ּҰ� ����
	}
	termArray[count].c = c;	//��� �߰�
	termArray[count].exp = i;	//���� �߰�
	count++;	//����� ���� �� ����
}

//���� ������ ������������ �����ϰ� �������� ����� ����� ����
void Polynomial::sortTermArray() {
	for (int i = 0; i < count; i++) {	//termArray�� ������������ ���� (���� ����)
		int max = i;

		for (int temp = i + 1; temp < count; temp++) {
			if (termArray[temp].exp > termArray[max].exp) {
				max = temp;
			}
		}

		swap(termArray[i].exp, termArray[max].exp);
		swap(termArray[i].c, termArray[max].c);
	}

	if (count > 0) {	//���� ���� ���
		Term* tarr = new Term[arraySize];	//������� ������ ����
		int is = 0;		//tarr�� index

		tarr[is].c = termArray[is].c;		//ù ���� ����
		tarr[is].exp = termArray[is].exp;

		for (int i = 1; i < count; i++) {	//�ι�° �׺��� ������ ���
			if (tarr[is].exp == termArray[i].exp) { //�ӽ� �迭�� ���� �� ����� termArray�� ���� �� ����� ���� ��� (������ ���)
				tarr[is].c += termArray[i].c;
			}
			else {		//�� ����� �ٸ��� ���� index�� �� �߰�
				is++;
				tarr[is].c = termArray[i].c;
				tarr[is].exp = termArray[i].exp;
			}
		}

		is++;	//is�� ���� ������ ���
		delete[] termArray;		//���� �迭�� ����
		termArray = new Term[arraySize];	//termArray�� �ʱ�ȭ
		count = 0;

		for (int i = 0; i < is; i++) {
			if (tarr[i].c) {				//0�� �ƴ� ���� �߰�
				addTerm(tarr[i].c, tarr[i].exp);
			}
		}
	}
}

//���׽� ���� ����
const Polynomial Polynomial::operator+(const Polynomial& p) {
	Polynomial temp; //������� ������ ����

	for (int i = 0; i < count; i++) {	//this�� �׵��� ����
		temp.addTerm(termArray[i].c, termArray[i].exp);
	}

	for (int i = 0; i < p.count; i++) { //p�� �׵��� ����
		temp.addTerm(p.termArray[i].c, p.termArray[i].exp);
	}

	temp.sortTermArray();	//���� �� ������ ���

	return temp;	//����� ��ȯ
}

//���׽� ���� ����
Polynomial& Polynomial::operator=(const Polynomial& p) {
	if (this != &p) {	//�ڱ� �ڽ��� �����ϴ°� �ƴ� ���
		delete[] termArray;	//���� �迭�� ����
		arraySize = 5;
		count = 0;
		termArray = new Term[arraySize]; //���ο� �迭 �Ҵ�

		for (int i = 0; i < p.count; i++) {	//p�� ���� ����
			addTerm(p.termArray[i].c, p.termArray[i].exp);
		}
	}

	return *this;	//����� ��ȯ
}

//���׽��� ���� ����
const Polynomial Polynomial::sMultPoly(const int c, const int e) {
	Polynomial temp;	//������� ������ ����

	for (int i = 0; i < count; i++) {	//cx^e�� this�� ���� ����� temp�� ����
		temp.addTerm(termArray[i].c * c, termArray[i].exp + e);
	}

	temp.sortTermArray();	//���� �� ������ ���

	return temp;
}

//���׽��� �� ����
const Polynomial Polynomial::operator*(const Polynomial& p) {
	Polynomial temp;	//������� ������ ����

	for (int i = 0; i < p.count; i++) {	//p�� �� ���� this�� ���� ���� temp�� ���Ѵ�.
		temp = temp + sMultPoly(p.termArray[i].c, p.termArray[i].exp);
	}

	temp.sortTermArray();	//���� �� ������ ���

	return temp;	//���� ��� ��ȯ
}

//���׽��� ���� ���
const int Polynomial::evalPoly(const int c) {
	int y = 0; //������� ������ ����

	for (int i = 0; i < count; i++) {	//�� ���� ���� ����Ͽ� ������� ���Ѵ�.
		y += termArray[i].c * (int)pow(c, termArray[i].exp);
	}

	return y; //������� ��ȯ
}
