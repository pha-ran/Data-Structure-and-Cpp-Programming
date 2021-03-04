#include <iostream>
#include <string>
#include <ctime>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::remove;

class Date {
public:
	Date(int year_ = 2000, int month_ = 1, int day_ = 1); // 인수가 없을경우 기본값으로 초기화
	~Date() = default;
	void setDate(int year_, int month_, int day_);
	static void coutCurrentDate();
	int getAge();

private:
	int year;
	int month;
	int day;
};

int main() {

	int id, y, m, d;
	string dept, name;
	Date birth_date;

	cout << "환영합니다! 학과명, 학번, 이름, 생년월일(yyyy/mm/dd)을 입력하세요 > ";

	cin >> dept >> id;
	cin.ignore(1, ','); // 입력 버퍼에서 1개 삭제, ','가 나오면 ','삭제 후 중지
	cin >> name >> y;
	cin.ignore(1, '/');
	cin >> m;
	cin.ignore(1, '/');
	cin >> d;

	birth_date.setDate(y, m, d);

	// 문자열에서 ',' 삭제
	dept.erase(remove(dept.begin(), dept.end(), ','), dept.end());
	name.erase(remove(name.begin(), name.end(), ','), name.end());

	cout << ">> " << dept << " " << id << " " << name << "님 " << y << "년" << m << "월" << d << "일생 ";
	Date::coutCurrentDate();
	cout << " 현재 " << birth_date.getAge() << "세입니다." << endl;

	return 0;
}

Date::Date(int year_, int month_, int day_) :
	year(year_),
	month(month_),
	day(day_)
{}

void Date::setDate(int year_, int month_, int day_) {
	year = year_;
	month = month_;
	day = day_;
}

void Date::coutCurrentDate() {
	time_t current_time_sec = time(NULL);
	struct tm current_time;
	localtime_s(&current_time, &current_time_sec);

	cout << current_time.tm_year + 1900 << "년" << current_time.tm_mon + 1 << "월" << current_time.tm_mday << "일";
}

int Date::getAge() {
	time_t current_time_sec = time(NULL);
	struct tm current_time;
	localtime_s(&current_time, &current_time_sec);

	return current_time.tm_year + 1900 - year + 1; //한국 나이 계산
}