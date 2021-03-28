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

//다항식(termArray는 Term의 포인터, arraySize == 할당된 Term의 수, count == 저장된 항의 수)
class Polynomial {
  public:
	Polynomial();
	void addTerm(const int c, const int i);		//항을 추가 (arraySize보다 항이 많으면 arraySize + 5의 새로운 배열 할당 후 복사)
	const Polynomial sMultPoly(const int c, const int e);	//다항식의 단항 곱셈
	const int evalPoly(const int c);			//다항식의 값을 계산
	const Polynomial operator+(const Polynomial& p);	//다항식 덧셈 연산
	const Polynomial operator*(const Polynomial& p);	//다항식의 곱 연산
	Polynomial& operator=(const Polynomial& p);			//다항식 대입 연산
	friend ostream& operator<<(ostream& os, const Polynomial& p);	// 출력 연산자 << 오버로딩 (항이 없을 경우 0으로 계산)
	// 입력 연산자 >> 오버로딩 (정상적인 (계수, 지수) 형태의 입력값만 받아서 처리, 이외는 무시, 항이 없을 경우 0으로 계산)
	friend istream& operator>>(istream& is, Polynomial& p);
	const int getCount() { return count; }

  private:
	Term* termArray;	//Term의 포인터
	int arraySize;	//할당된 Term의 수
	int count;		//저장된 항의 수

	void sortTermArray();			//항을 지수의 내림차순으로 정렬하고 동류항을 계산한 결과를 저장
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
		cout << ">Input polynomials a, b, c : ";	//(계수, 지수)형태의 정상정인 입력값만 처리, 이외는 무시 (항이 없을 경우 0으로 계산)
		cin >> a;									//#입력시 프로그램 종료
		cin >> b;
		cin >> c;

		if (a.getCount() == 0 || b.getCount() == 0 || c.getCount() == 0) { //a, b, c중 하나라도 항이 없을 경우 에러
			cout << "error" << endl << endl;
			cin.clear();		//오류 상태 초기화
			fseek(stdin, 0, SEEK_END);	//버퍼 초기화
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

		if (cin.fail()) {		//X가 숫자가 아닐 경우 에러
			cout << "error" << endl << endl;
			cin.clear();		//오류 상태 초기화
			fseek(stdin, 0, SEEK_END);	//버퍼 초기화
			continue;
		}

		cout << "A*B+C = " << d.evalPoly(x);
		cout << endl << endl;
	}

	return 0;
}

// 출력 연산자 << 오버로딩 (항이 없을 경우 0으로 계산)
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

// 입력 연산자 >> 오버로딩 (정상적인 (계수, 지수) 형태의 입력값만 받아서 처리, 이외는 무시, 항이 없을 경우 0으로 계산)
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

	p.sortTermArray();	//입력받은 항들을 정렬 후 동류항 계산

	return is;
}

// Polynomial 생성자 (5개 크기의 Term 할당)
Polynomial::Polynomial() {
	arraySize = 5;
	count = 0;
	termArray = new Term[arraySize];
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
	for (int i = 0; i < count; i++) {	//termArray를 내림차순으로 정렬 (선택 정렬)
		int max = i;

		for (int temp = i + 1; temp < count; temp++) {
			if (termArray[temp].exp > termArray[max].exp) {
				max = temp;
			}
		}

		swap(termArray[i].exp, termArray[max].exp);
		swap(termArray[i].c, termArray[max].c);
	}

	if (count > 0) {	//항이 있을 경우
		Term* tarr = new Term[arraySize];	//결과값을 저장할 변수
		int is = 0;		//tarr의 index

		tarr[is].c = termArray[is].c;		//첫 항을 설정
		tarr[is].exp = termArray[is].exp;

		for (int i = 1; i < count; i++) {	//두번째 항부터 동류항 계산
			if (tarr[is].exp == termArray[i].exp) { //임시 배열의 현재 항 계수가 termArray의 현재 항 계수가 같을 경우 (동류항 계산)
				tarr[is].c += termArray[i].c;
			}
			else {		//항 계수가 다르면 다음 index에 항 추가
				is++;
				tarr[is].c = termArray[i].c;
				tarr[is].exp = termArray[i].exp;
			}
		}

		is++;	//is를 항의 갯수로 사용
		delete[] termArray;		//기존 배열을 해제
		termArray = new Term[arraySize];	//termArray를 초기화
		count = 0;

		for (int i = 0; i < is; i++) {
			if (tarr[i].c) {				//0이 아닌 항을 추가
				addTerm(tarr[i].c, tarr[i].exp);
			}
		}
	}
}

//다항식 덧셈 연산
const Polynomial Polynomial::operator+(const Polynomial& p) {
	Polynomial temp; //결과값을 저장할 변수

	for (int i = 0; i < count; i++) {	//this의 항들을 저장
		temp.addTerm(termArray[i].c, termArray[i].exp);
	}

	for (int i = 0; i < p.count; i++) { //p의 항들을 저장
		temp.addTerm(p.termArray[i].c, p.termArray[i].exp);
	}

	temp.sortTermArray();	//정렬 후 동류항 계산

	return temp;	//결과값 반환
}

//다항식 대입 연산
Polynomial& Polynomial::operator=(const Polynomial& p) {
	if (this != &p) {	//자기 자신을 대입하는게 아닐 경우
		delete[] termArray;	//기존 배열을 해제
		arraySize = 5;
		count = 0;
		termArray = new Term[arraySize]; //새로운 배열 할당

		for (int i = 0; i < p.count; i++) {	//p의 값을 복사
			addTerm(p.termArray[i].c, p.termArray[i].exp);
		}
	}

	return *this;	//결과값 반환
}

//다항식의 단항 곱셈
const Polynomial Polynomial::sMultPoly(const int c, const int e) {
	Polynomial temp;	//결과값을 저장할 변수

	for (int i = 0; i < count; i++) {	//cx^e와 this를 곱한 결과를 temp에 저장
		temp.addTerm(termArray[i].c * c, termArray[i].exp + e);
	}

	temp.sortTermArray();	//정렬 후 동류항 계산

	return temp;
}

//다항식의 곱 연산
const Polynomial Polynomial::operator*(const Polynomial& p) {
	Polynomial temp;	//결과값을 저장할 변수

	for (int i = 0; i < p.count; i++) {	//p의 각 항을 this와 곱한 값을 temp에 더한다.
		temp = temp + sMultPoly(p.termArray[i].c, p.termArray[i].exp);
	}

	temp.sortTermArray();	//정렬 후 동류항 계산

	return temp;	//곱셈 결과 반환
}

//다항식의 값을 계산
const int Polynomial::evalPoly(const int c) {
	int y = 0; //결과값을 저장할 변수

	for (int i = 0; i < count; i++) {	//각 항의 값을 계산하여 결과값에 더한다.
		y += termArray[i].c * (int)pow(c, termArray[i].exp);
	}

	return y; //결과값을 반환
}
