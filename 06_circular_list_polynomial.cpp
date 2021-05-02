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
	int coef;	//계수
	int exp;	//지수

	//계수와 지수 설정
	Term Set(int c, int e) {
		coef = c;
		exp = e;
		return *this;
	}
};	//Term

class CircularListNode {
	friend class CircularListWithHeader;
private:
	Term data;	//계수와 지수값
	CircularListNode* link;	//다음 노드의 포인터
public:
	//생성자
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
	//생성자
	CircularListWithHeader() {
		head = new CircularListNode(0, -1, 0);
		head->link = head;
		tail = head;
	}
	//노드를 추가
	void addNode(int c, int e) {
		tail->link = new CircularListNode(c, e, head);
		tail = tail->link;
	}

	//반복자
	class iterator {
	private:
		CircularListNode* current;	//반복자가 가리키는 노드의 포인터
	public:
		//생성자
		iterator(CircularListNode* p) : current(p) {}
		//++오버로딩 (전위 연산)
		iterator& operator++ () {
			current = current->link;	//다음 노드로 이동
			return *this;
		}
		//*오버로딩 (노드의 데이터 필드 리턴)
		Term& operator* () { return current->data; }
		//!=오버로딩
		bool operator!= (const iterator it) { return current != it.current; }
		//==오버로딩
		bool operator== (const iterator it) { return current == it.current; }
	};	//iterator

	//헤드 노드의 반복자 반환
	iterator Head() const { return iterator(head); }
	//헤드 다음 노드의 반복자 반환
	iterator begin() const { return iterator(head->link); }
};	//CircularListWithHeader

class Polynomial {
private:
	CircularListWithHeader* list;
public:
	Polynomial() { list = new CircularListWithHeader(); }
	void addTerm(const int c, const int e) { list->addNode(c, e); }		//항을 추가
	const bool isEmpty() { return list->begin() == list->Head(); }
	const Polynomial sMultPoly(const int c, const int e);	//다항식의 단항 곱셈
	const int evalPoly(const int c);			//다항식의 값을 계산
	const Polynomial operator+(const Polynomial& p);	//다항식 덧셈 연산
	const Polynomial operator*(const Polynomial& p);	//다항식의 곱 연산
	Polynomial& operator=(const Polynomial& p);			//다항식 대입 연산
	friend ostream& operator<<(ostream& os, const Polynomial& p);	// 출력 연산자 << 오버로딩 (모든 다항식은 항이 )
	// 입력 연산자 >> 오버로딩 (정상적인 (계수, 지수) 형태의 입력값만 받아서 처리, 이외는 무시)
	friend istream& operator>>(istream& is, Polynomial& p);
	void sortList();	//항을 지수의 내림차순으로 정렬하고 동류항을 계산한 결과를 저장
};	//Polynomial

int main() {

	while (true) {
		Polynomial a, b, c, d, t;
		int x;
		cout << ">Input polynomials a, b, c : ";
		//(계수, 지수)형태의 정상정인 입력값만 처리, 이외는 무시
		//정상적인 입력과 비정상적인 입력이 혼합 시 정상적인 입력값만 처리, 항이 없을 경우 예외 처리
		cin >> a;									//#입력시 프로그램 종료
		cin >> b;
		cin >> c;

		if (a.isEmpty() || b.isEmpty() || c.isEmpty()) { //a, b, c중 하나라도 항이 없을 경우 에러
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

// 출력 연산자 << 오버로딩
ostream& operator<<(ostream& os, const Polynomial& p) {
	for (CircularListWithHeader::iterator it = p.list->begin(); it != p.list->Head(); ++it) {
		if (it != p.list->begin() && (*it).coef > 0) { os << "+"; } //두번째 항부터는 계수가 양수이면 + 출력

		if ((*it).coef != 1 && (*it).coef != -1) { //계수가 1또는 -1이 아니면 계수를 출력
			os << (*it).coef;
		}
		else if ((*it).coef == -1 && (*it).exp > 0) { os << "-"; } //계수가 -1이고 지수가 0보다 크면 -출력
		else if ((*it).coef == 1 && (*it).exp == 0) { os << "1"; } //계수가 1이고 지수가 0이면(상수항이 1이면) 1출력
		else if ((*it).coef == -1 && (*it).exp == 0) { os << "-1"; } //계수가 -1이고 지수가 0이면(상수항이 -1이면) -1출력

		if ((*it).exp > 1) { //지수가 1보다 크면 x^(지수)를 출력 (지수는 0보다 크다고 가정)
			os << "x^" << (*it).exp;
		}
		else if ((*it).exp == 1) {	//지수가 1이면 x만 출력
			os << "x";
		}
	}

	if (p.list->begin() == p.list->Head()) { os << "0"; }	//항이 없을 경우 0출력

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

	p.sortList();	//입력받은 항들을 정렬 후 동류항 계산

	return is;
}

//다항식 대입 연산
Polynomial& Polynomial::operator=(const Polynomial& p) {
	if (this != &p) {	//자기 자신을 대입하는게 아닐 경우
		list = new CircularListWithHeader();	//새로운 리스트 할당

		for (CircularListWithHeader::iterator it = p.list->begin(); it != p.list->Head(); ++it) {
			addTerm((*it).coef, (*it).exp);	//데이터 값 복사
		}
	}

	return *this;
}

//항을 지수의 내림차순으로 정렬하고 동류항을 계산한 결과를 저장
void Polynomial::sortList() {
	CircularListWithHeader* sort = new CircularListWithHeader();
	int max = 0;

	for (CircularListWithHeader::iterator it = list->begin(); it != list->Head(); ++it) {
		if ((*it).exp > max) { max = (*it).exp; }
	}

	max++;	//max는 최대 차수보다 항상 큼

	for (CircularListWithHeader::iterator i = list->begin(); i != list->Head(); ++i) {	//항을 지수의 내림차순으로 정렬
		int k = -1;

		for (CircularListWithHeader::iterator j = list->begin(); j != list->Head(); ++j) {	//max보다 작은 최대 차수를 탐색
			if ((*j).exp > k && (*j).exp < max) {
				k = (*j).exp;
			}
		}

		for (CircularListWithHeader::iterator j = list->begin(); j != list->Head(); ++j) {	//지수가 k인 모든 항을 sort에 추가
			if (k == (*j).exp) {
				sort->addNode((*j).coef, (*j).exp);
			}
		}

		max = k;
	}

	CircularListWithHeader* temp = new CircularListWithHeader();

	int sum = 0;	//임시 계수

	for (CircularListWithHeader::iterator i = sort->begin(); i != sort->Head(); ++i) {	//sort의 모든 동류항을 계산
		CircularListWithHeader::iterator j = i;
		++j;

		if (j != sort->Head()) {	//j가 헤드가 아닌 경우
			if ((*i).exp == (*j).exp) {	//다음 노드가 동류항일 경우
				sum += (*i).coef;	//임시 계수 증가
			}
			else {	//다음 노드가 동류항이 아닐 경우
				if (sum + (*i).coef) {	//계수가 0이 아닐 경우
					temp->addNode(sum + (*i).coef, (*i).exp);	//temp에 노드 추가
					sum = 0;
				}
			}
		}
		else {	//j가 헤드인경우 (i가 마지막 노드인 경우)
			if (sum + (*i).coef) {	//계수가 0이 아닐 경우
				temp->addNode(sum + (*i).coef, (*i).exp);	//temp에 노드 추가
			}
		}
	}

	list = temp;	//정렬후 동류항이 계산된 다항식을 list에 대입
}

//다항식 덧셈 연산
const Polynomial Polynomial::operator+(const Polynomial& p) {
	Polynomial temp;

	for (CircularListWithHeader::iterator it = list->begin(); it != list->Head(); ++it) {
		temp.addTerm((*it).coef, (*it).exp);	//this의 모든 항 추가
	}

	for (CircularListWithHeader::iterator it = p.list->begin(); it != p.list->Head(); ++it) {
		temp.addTerm((*it).coef, (*it).exp);	//p의 모든 항 추가
	}

	temp.sortList();	//정렬 후 동류항 계산

	return temp;
}

//다항식의 단항 곱셈
const Polynomial Polynomial::sMultPoly(const int c, const int e) {
	Polynomial temp;	//결과값을 저장할 변수

	for (CircularListWithHeader::iterator it = list->begin(); it != list->Head(); ++it) {
		temp.addTerm((*it).coef * c, (*it).exp + e);	//cx^e와 this를 곱한 결과를 temp에 저장
	}

	temp.sortList();	//정렬 후 동류항 계산

	return temp;
}

//다항식의 곱 연산
const Polynomial Polynomial::operator*(const Polynomial& p) {
	Polynomial temp;	//결과값을 저장할 변수

	for (CircularListWithHeader::iterator it = p.list->begin(); it != p.list->Head(); ++it) {
		temp = temp + sMultPoly((*it).coef, (*it).exp);		//p의 각 항들을 this와 단항 곱셈 후 temp와 덧셈
	}

	temp.sortList();	//정렬 후 동류항 계산

	return temp;
}

//다항식의 값을 계산
const int Polynomial::evalPoly(const int c) {
	int y = 0; //결과값을 저장할 변수

	for (CircularListWithHeader::iterator it = list->begin(); it != list->Head(); ++it) {
		y += (*it).coef * (int)pow(c, (*it).exp);	//각 항의 값을 계산하여 결과값에 더한다.
	}

	return y; //결과값을 반환
}
