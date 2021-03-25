#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Polynomial;
class Term;

//다항식(termArray는 Term의 포인터, arraySize == 할당된 Term의 수, count == 저장된 항의 수)
class Polynomial {
  public:
	Polynomial();
	~Polynomial();
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, const Polynomial& p);

  private:
	Term* termArray;	//Term의 포인터
	int arraySize;	//할당된 Term의 수
	int count;		//저장된 항의 수
};

//(c == 계수, exp == 지수)의 쌍
class Term {
	friend Polynomial; //Polynomial이 Term에 접근 가능

  public:
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, const Polynomial& p);

  private:
	float c;		//계수
	int exp;		//지수 (exp >= 0)
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

ostream& operator<<(ostream& os, const Polynomial& p) { // 출력 연산자 << (termArray가 정렬되어있다고 가정)
	for (int i = 0; i < p.count; i++) {
		if (i > 0 && p.termArray[i].c > 0) { os << "+"; } //두번째 항부터는 계수가 양수이면 + 출력

		if (p.termArray[i].c != 1) { //계수가 1이 아니면 계수를 출력 (계수가 0이 아니라고 가정)
			os << p.termArray[i].c;
		}

		if (p.termArray[i].exp > 1) { //지수가 1보다 크면 x^(지수)를 출력 (지수는 0보다 크다고 가정)
			os << "x^" << p.termArray[i].exp;
		}
		else if (p.termArray[i].exp == 1) {	//지수가 1이면 x만 출력
			os << "x";
		}
	}
	return os;
}

istream& operator>>(istream& is, const Polynomial& p) { // 입력 연산자 >>
	//ToDo
	return is;
}

Polynomial::Polynomial() {	// Polynomial 생성자 (5개 크기의 Term 할당)
	arraySize = 5;
	count = 0;
	termArray = new Term[arraySize];
}

Polynomial::~Polynomial() {	// Polynomial 소멸자 (termArray 반환)
	if (termArray != NULL) { delete[] termArray; }
}
