#include <iostream>
#include <string>

using namespace std;

int main() {

	int id, y, m, d;
	string dept, name;

	cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)을 입력하세요 > ";

	cin >> dept >> id;
	cin.ignore(1, ','); // 입력 버퍼에서 1개 삭제, ','가 나오면 ','삭제 후 중지
	cin >> name >> y;
	cin.ignore(1, '/');
	cin >> m;
	cin.ignore(1, '/');
	cin >> d;

	// 문자열에서 ',' 삭제
	dept.erase(remove(dept.begin(), dept.end(), ','), dept.end());
	name.erase(remove(name.begin(), name.end(), ','), name.end());

	cout << ">> " << dept << " " << id << " " << name << "님 " << y << "년" << m << "월" << d << "일생 " << endl;

	return 0;
}