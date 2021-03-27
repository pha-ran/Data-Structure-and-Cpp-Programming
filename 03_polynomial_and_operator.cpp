#include <iostream>
#include <string>
#include <algorithm>
#include <regex>
#include <cmath>

using namespace std;

class Polynomial;
class Term;
ostream& operator<<(ostream& os, const Polynomial& p);
istream& operator>>(istream& is, Polynomial& p);

//다항식(termArray는 Term의 포인터, arraySize == 할당된 Term의 수, count == 저장된 항의 수)
class Polynomial {
public:
	Polynomial();
	~Polynomial();
	void addTerm(const int c, const int i);
	const Polynomial sMultPoly(const int c, const int e);
	const int evalPoly(const int c);
	const Polynomial operator+(const Polynomial& p);
	const Polynomial operator*(const Polynomial& p);
	Polynomial& operator=(const Polynomial& p);
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, Polynomial& p);

private:
	Term* termArray;	//Term의 포인터
	int arraySize;	//할당된 Term의 수
	int count;		//저장된 항의 수

	void sortTermArray();
};

//(c == 계수, exp == 지수)의 쌍
class Term {
	friend Polynomial; //Polynomial이 Term에 접근 가능
	friend ostream& operator<<(ostream& os, const Polynomial& p);
	friend istream& operator>>(istream& is, Polynomial& p);

private:
	int c;		//계수
	int exp;	//지수 (exp >= 0)
};

int main() {

	while (true) {
		Polynomial a, b, c, d, t;
		int x;
		cout << ">Input polynomials a, b, c : ";
		cin >> a;
		cin >> b;
		cin >> c;
		cout << "A(x) = " << a << endl;
		cout << "B(x) = " << b << endl;
		cout << "C(x) = " << c << endl;
		t = a * b;
		d = t + c;
		cout << "T(x) = " << t << endl;
		cout << "D(x) = " << d << endl;
		cout << ">Input x vlaue : ";
		cin >> x;
		cout << "A*B+C = " << d.evalPoly(x) << endl;
		cout << endl;
	}

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
	int c;	//계수 임시 저장
	int i;		//지수 임시 저장
	string str;	//입력 문자열 임시 저장
	smatch sm;	//매칭된 결과 저장
	regex re("\\((-?[0-9]+),([0-9]+)\\)"); //(계수,지수) 형태의 정규표현식 (계수에만 음수가 올 수 있음)

	cin >> str;

	if (str == "#") { exit(0); } //#을 입력받으면 프로그램 종료

	//입력받은 문자열에 (계수,지수)형태가 없을 때까지 반복, (계수,지수)형태를 sm[0]에 저장, 계수를 sm[1], 지수를 sm[2]에 저장
	while (regex_search(str, sm, re)) {
		c = stoi(sm[1].str()); //계수 부분을 int 형으로 변환
		i = stoi(sm[2].str()); //지수 부분을 int 형으로 변환

		if (c != 0 && i >= 0) {	//계수가 0이 아니고, 지수가 0보다 클 경우에만
			p.addTerm(c, i); //항을 추가
		}

		str = sm.suffix(); //문자열에서 다음 (계수,지수)형태 탐색
	}

	p.sortTermArray();	//입력받은 항들을 정렬

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

//항을 추가 (arraySize보다 항이 많으면 arraySize + 5의 새로운 배열 할당 후 복사)
void Polynomial::addTerm(const int c, const int i) {
	if (arraySize == count) { //할당된 Term의 수와 저장된 Term의 수가 같을때
		arraySize += 5;	//arraySize를 5 증가
		Term* tarr = new Term[arraySize];	//5만큼 늘어난 크기의 임시 배열 할당
		copy(termArray, termArray + count, tarr);	//임시 배열에 값 복사
		delete[] termArray;	//기존 배열은 해제
		termArray = tarr;	//임시 배열의 주소값 대입
	}
	termArray[count].c = c;	//계수 추가
	termArray[count].exp = i;	//지수 추가
	count++;	//저장된 항의 수 증가
}

//항을 지수의 내림차순으로 정렬하고 동류항을 계산한 결과를 저장
void Polynomial::sortTermArray() {
	for (int i = 0; i < count; i++) {	//termArray를 내림차순으로 정렬
		int max = i;

		for (int temp = i + 1; temp < count; temp++) {
			if (termArray[temp].exp > termArray[max].exp) {
				max = temp;
			}
		}

		swap(termArray[i].exp, termArray[max].exp);
		swap(termArray[i].c, termArray[max].c);
	}

	if (count > 0) {
		Term* tarr = new Term[arraySize];
		int is = 0;

		tarr[is].c = termArray[is].c;		//첫 항을 설정
		tarr[is].exp = termArray[is].exp;

		for (int i = 1; i < count; i++) {
			if (tarr[is].exp == termArray[i].exp) { //임시 배열의 현재 항 계수가 termArray의 현재 항 계수가 같을 경우 (동류항 계산)
				tarr[is].c += termArray[i].c;
			}
			else {
				is++;
				tarr[is].c = termArray[i].c;
				tarr[is].exp = termArray[i].exp;
			}
		}

		is++;
		delete[] termArray;
		termArray = new Term[arraySize];	//termArray를 초기화
		count = 0;

		for (int i = 0; i < is; i++) {
			if (tarr[i].c) {				//0이 아닌 항을 추가
				addTerm(tarr[i].c, tarr[i].exp);
			}
		}
	}
}

const Polynomial Polynomial::operator+(const Polynomial& p) {
	Polynomial temp;

	for (int i = 0; i < count; i++) {
		temp.addTerm(termArray[i].c, termArray[i].exp);
	}

	for (int i = 0; i < p.count; i++) {
		temp.addTerm(p.termArray[i].c, p.termArray[i].exp);
	}

	temp.sortTermArray();

	return temp;
}

Polynomial& Polynomial::operator=(const Polynomial& p) {
	if (this != &p) {
		delete[] termArray;
		arraySize = 5;
		count = 0;
		termArray = new Term[arraySize];

		for (int i = 0; i < p.count; i++) {
			addTerm(p.termArray[i].c, p.termArray[i].exp);
		}
	}

	return *this;
}

//다항식의 곱셈
const Polynomial Polynomial::sMultPoly(const int c, const int e) {
	Polynomial temp;

	for (int i = 0; i < count; i++) {
		temp.addTerm(termArray[i].c * c, termArray[i].exp + e);
	}

	temp.sortTermArray();

	return temp;
}

const Polynomial Polynomial::operator*(const Polynomial& p) {
	Polynomial temp;

	for (int i = 0; i < p.count; i++) {
		temp = temp + sMultPoly(p.termArray[i].c, p.termArray[i].exp);
	}

	temp.sortTermArray();

	return temp;
}

//다항식의 값을 계산
const int Polynomial::evalPoly(const int c) {
	int y = 0; //결과값을 저장할 변수

	for (int i = 0; i < count; i++) {	//각 항의 값을 계산하여 결과값에 더한다.
		y += termArray[i].c * (int)pow(c, termArray[i].exp);
	}

	return y;
}
