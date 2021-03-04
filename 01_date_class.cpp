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
	Date(int year_ = 2000, int month_ = 1, int day_ = 1); // �μ��� ������� �⺻������ �ʱ�ȭ
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

	cout << "ȯ���մϴ�! �а���, �й�, �̸�, �������(yyyy/mm/dd)�� �Է��ϼ��� > ";

	cin >> dept >> id;
	cin.ignore(1, ','); // �Է� ���ۿ��� 1�� ����, ','�� ������ ','���� �� ����
	cin >> name >> y;
	cin.ignore(1, '/');
	cin >> m;
	cin.ignore(1, '/');
	cin >> d;

	birth_date.setDate(y, m, d);

	// ���ڿ����� ',' ����
	dept.erase(remove(dept.begin(), dept.end(), ','), dept.end());
	name.erase(remove(name.begin(), name.end(), ','), name.end());

	cout << ">> " << dept << " " << id << " " << name << "�� " << y << "��" << m << "��" << d << "�ϻ� ";
	Date::coutCurrentDate();
	cout << " ���� " << birth_date.getAge() << "���Դϴ�." << endl;

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

	cout << current_time.tm_year + 1900 << "��" << current_time.tm_mon + 1 << "��" << current_time.tm_mday << "��";
}

int Date::getAge() {
	time_t current_time_sec = time(NULL);
	struct tm current_time;
	localtime_s(&current_time, &current_time_sec);

	return current_time.tm_year + 1900 - year + 1; //�ѱ� ���� ���
}