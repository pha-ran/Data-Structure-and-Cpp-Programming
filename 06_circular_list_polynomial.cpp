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
	CircularListNode *link;	//다음 노드의 포인터
public:
	//생성자
	CircularListNode(int c = 0, int e = 0, CircularListNode* next = 0) {
		data.Set(c, e);
		link = next;
	}
};	//CircularListNode

class CircularListWithHeader {
	friend class Polynomial;
private:
	CircularListNode* head;
public:
	//생성자
	CircularListWithHeader() {
		head = new CircularListNode(0, -1, 0);
		head->link = head;
	}

	//반복자
	class iterator {
	private:
	public:
		//++오버로딩 (전위 연산)
		iterator& operator++ ();
		//*오버로딩 (노드의 데이터 필드 리턴)
		Term& operator* ();
		//!=오버로딩
		bool operator!= (const iterator it);
		//==오버로딩
		bool operator== (const iterator it);
	};	//iterator

	//헤드 노드의 반복자 반환
	iterator begin();
};	//CircularListWithHeader

class Polynomial {
private:
	CircularListWithHeader poly;
public:
	void addTerm(const int c, const int i);		//항을 추가
	const Polynomial sMultPoly(const int c, const int e);	//다항식의 단항 곱셈
	const int evalPoly(const int c);			//다항식의 값을 계산
	const Polynomial operator+(const Polynomial& p);	//다항식 덧셈 연산
	const Polynomial operator*(const Polynomial& p);	//다항식의 곱 연산
	Polynomial& operator=(const Polynomial& p);			//다항식 대입 연산
	friend ostream& operator<<(ostream& os, const Polynomial& p);	// 출력 연산자 << 오버로딩
	// 입력 연산자 >> 오버로딩 (정상적인 (계수, 지수) 형태의 입력값만 받아서 처리)
	friend istream& operator>>(istream& is, Polynomial& p);
};	//Polynomial

int main() {
	

	return 0;
}