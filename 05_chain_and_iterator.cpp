#include <iostream>

using namespace std;

template<typename T> class ChainNode;
template<typename T> class Chain;

template<typename T> class ChainNode {
	template<typename U> friend class Chain;
  private:
	  T data;			//입력값을 저장
	  ChainNode *link;	//다음 노드의 포인터
  public:
	  ChainNode(T d, ChainNode* l) : data(d), link(l) {}	//노드의 생성자
};

template<typename T> class Chain {
  private:
	  ChainNode<T> *first; //첫 노드의 포인터
  public:
	  Chain() { first = NULL; }	//체인 생성자, 초기값 NULL
	  //체인의 맨 앞에 data 값을 가지는 노드를 생성
	  void push(T data) { first = new ChainNode<T>(data, first); }
	  //체인 반복자
	  class iterator {
	    private:
			ChainNode<T> *current;	//반복자가 현재 가리키는 노드의 포인터
	    public:
			//반복자 생성자
			iterator(ChainNode<T> *p) : current(p) {}
			//++오버로딩 (전위 연산) 후위의 경우 operator++(int) 형식
			iterator& operator++ () {
				current = current->link;
				return *this;
			}
			//*오버로딩 (노드의 데이터 필드 리턴)
			T& operator* () { return current->data; }
			//!=오버로딩
			bool operator!= (const iterator it) { return current != it.current; }
			//==오버로딩
			bool operator== (const iterator it) { return current == it.current; }
	  };
	  //시작 노드의 반복자 반환
	  iterator begin() { return iterator(first); }
	  //마지막 노드의 반복자 반환 (NULL)
	  iterator end() { return iterator(NULL); }
};

int main() {
	Chain<int> a;	//int형 데이터를 가지는 체인 생성

	//데이터를 입력받아 연결리스트 a를 구성 : push() 함수 사용
	cout << "공백으로 구분된 원소 리스트 입력 (종료 기호 # 또는 정수가 아닌 값을 입력 시 입력 종료)\n" << ">>";
	while (true) {
		int x;
		cin >> x;

		if (cin.fail()) {	//x가 # 또는 정수가 아닌 값을 입력받을 경우
			cin.clear();	//오류 상태 초기화
			fseek(stdin, 0, SEEK_END);	//버퍼 초기화
			break;	//입력 종료
		}

		a.push(x);	//체인에 노드를 추가
	}
	if (a.begin() == a.end()) { cout << "error"; return 0; }	//체인이 비었을 경우 예외 처리

	//체인의 모든 데이터 출력
	cout << "체인의 데이터 : ";
	for (Chain<int>::iterator ait = a.begin(); ait != a.end(); ++ait) {	//체인의 시작부터 끝까지
		cout << *ait << " ";	//현재 노드의 데이터 출력
	}
	cout << endl;

	//체인의 최소값 출력
	int minValue = 999999999;	//최소값을 큰 수로 지정
	for (Chain<int>::iterator ait = a.begin(); ait != a.end(); ++ait) {	//체인의 시작부터 끝까지
		if (minValue > *ait) {	//현재 노드의 값이 minValue보다 작을 경우
			minValue = *ait;	//minValue를 현재 노드의 값으로 변경
		}
	}
	cout << "체인의 최소값 : " << minValue << endl;	//체인의 최소값 출력
	return 0;
}
