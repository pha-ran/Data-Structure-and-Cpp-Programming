#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <cmath>

using namespace std;

class Polynomial;
class Term;

//다항식(termArray는 Term의 포인터, arraySize == 할당된 Term의 수, count == 저장된 항의 수)
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
	Term* termArray;	//Term의 포인터
	int arraySize;	//할당된 Term의 수
	int count;		//저장된 항의 수

	void sortTermArray(Polynomial& p);
};

//(c == 계수, exp == 지수)의 쌍
class Term {
	friend Polynomial; //Polynomial이 Term에 접근 가능
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, Polynomial& p);

  private:
	float c;		//계수
	int exp;		//지수 (exp >= 0)
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

// 출력 연산자 << 오버로딩 (termArray가 정렬되어있다고 가정)
ostream& operator<<(ostream& os, const Polynomial& p) {
	for (int i = 0; i < p.count; i++) {
		if (i > 0 && p.termArray[i].c > 0) { os << "+"; } //두번째 항부터는 계수가 양수이면 + 출력

		if (p.termArray[i].c != 1 && p.termArray[i].c != -1) { //계수가 1또는 -1이 아니면 계수를 출력
			os << p.termArray[i].c;
		}
		else if (p.termArray[i].c == -1 && p.termArray[i].exp > 0) { os << "-"; } //계수가 -1이고 지수가 0보다 크면 -출력
		else if (p.termArray[i].c == 1 && p.termArray[i].exp == 0) { os << "1"; } //계수가 1이고 지수가 0이면(상수항이 1이면) 1출력
		else if (p.termArray[i].c == -1 && p.termArray[i].exp == 0) { os << "-1"; } //계수가 -1이고 지수가 0이면(상수항이 -1이면) -1출력

		if (p.termArray[i].exp > 1) { //지수가 1보다 크면 x^(지수)를 출력 (지수는 0보다 크다고 가정)
			os << "x^" << p.termArray[i].exp;
		}
		else if (p.termArray[i].exp == 1) {	//지수가 1이면 x만 출력
			os << "x";
		}
	}

	if (p.count == 0) { os << 0; } //항이 없을 경우 0출력

	return os;
}

// 입력 연산자 >> 오버로딩 (정상적인 (계수, 지수) 형태의 입력값만 받아서 처리, 이외는 무시)
istream& operator>>(istream& is, Polynomial& p) {
	float f;	//계수 임시 저장
	int i;		//지수 임시 저장
	string str;	//입력 문자열 임시 저장
	smatch sm;	//매칭된 결과 저장
	regex re("\\((-*[0-9]+),([0-9]+)\\)"); //(계수,지수) 형태의 정규표현식 (계수에만 음수가 올 수 있음)

	cin >> str;

	if (str == "#") { exit(0); }

	//입력받은 문자열에 (계수,지수)형태가 없을 때까지 반복, (계수,지수)형태를 sm[0]에 저장, 계수를 sm[1], 지수를 sm[2]에 저장
	while (regex_search(str, sm, re)) {
		f = stof(sm[1].str()); //계수 부분을 float 형으로 변환
		i = stoi(sm[2].str()); //지수 부분을 int 형으로 변환

		if (f != 0 && i >= 0) {	//계수가 0이 아니고, 지수가 0보다 클 경우에만
			p.addTerm(f, i); //항을 추가
		}

		str = sm.suffix(); //문자열에서 다음 (계수,지수)형태 탐색
	}

	return is;
}

// Polynomial 생성자 (5개 크기의 Term 할당)
Polynomial::Polynomial() {
	arraySize = 5;
	count = 0;
	termArray = new Term[arraySize];
}

// Polynomial 소멸자 (termArray 반환)
Polynomial::~Polynomial() {
	if (termArray != NULL) { delete[] termArray; }
}

//항을 추가 (arraySize보다 항이 많으면 arraySize + 5의 새로운 배열 할당)
void Polynomial::addTerm(const float f, const int i) {
	if (arraySize == count) { //할당된 Term의 수와 저장된 Term의 수가 같을때
		arraySize += 5;	//arraySize를 5 증가
		Term* tarr = new Term[arraySize];	//5만큼 늘어난 크기의 임시 배열 할당
		copy(termArray, termArray + count, tarr);	//임시 배열에 값 복사
		delete[] termArray;	//기존 배열은 해제
		termArray = tarr;	//임시 배열의 주소값 대입
	}
	termArray[count].c = f;
	termArray[count].exp = i;
	count++;
}
