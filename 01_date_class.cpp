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
	bool setDate(int year_, int month_, int day_);
	static void coutCurrentDate();
	int getAge();

  private:
	int year;
	int month;
	int day;
	static const int leap[2][12];
};

const int Date::leap[2][12] = {
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main() {

	int id, y, m, d;
	string dept, name;
	Date birth_date;

	cout << "ȯ���մϴ�! �а���, �й�, �̸�, �������(yyyy/mm/dd)�� �Է��ϼ���> ";

	cin >> dept >> id;
	cin.ignore(1, ','); // �Է� ���ۿ��� 1�� ����, ','�� ������ ','���� �� ����
	cin >> name >> y;
	cin.ignore(1, '/');
	cin >> m;
	cin.ignore(1, '/');
	cin >> d;

	if (id < 0) { cout << "�Է� ����" << endl; return 0; };

	//�Է°��� �����϶�
	if (birth_date.setDate(y, m, d)) {

		// ���ڿ����� ',' ����
		dept.erase(remove(dept.begin(), dept.end(), ','), dept.end());
		name.erase(remove(name.begin(), name.end(), ','), name.end());

		cout << ">> " << dept << " " << id << " " << name << "�� " << y << "��" << m << "��" << d << "�ϻ� ";
		Date::coutCurrentDate();
		cout << " ���� " << birth_date.getAge() << "���Դϴ�." << endl;
	}
	else {
		cout << "�Է� ����" << endl;
	}

	return 0;
}

Date::Date(int year_, int month_, int day_) :
	year(year_),
	month(month_),
	day(day_)
{}

bool Date::setDate(int year_, int month_, int day_) {

	time_t current_time_sec = time(NULL);
	struct tm current_time;
	localtime_s(&current_time, &current_time_sec);

	//�Է� ��¥�� ���� ��¥���� Ŭ ���
	if (year_ > current_time.tm_year + 1900 ||
		(year_ == current_time.tm_year + 1900 && month_ > current_time.tm_mon + 1) ||
		(year_ == current_time.tm_year + 1900 && month_ == current_time.tm_mon + 1 && day_ > current_time.tm_mday)
		) {
		return false;
	}

	//���� �Ǻ�
	bool leap_ = ((year_ % 4 == 0) && (year_ % 100 != 0)) || (year_ % 400 == 0);

	//��¥�� ���� �������� �Ǻ�
	if (year_ >= 1900 &&
		(month_ >= 1 && month_ <= 12) &&
		(day_ >= 1 && day_ <= leap[leap_][month_ - 1])
		) {
		year = year_;
		month = month_;
		day = day_;

		return true;
	}
	else {
		return false;
	}
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

	bool birth = (current_time.tm_mon + 1 > month || (current_time.tm_mon + 1 == month && current_time.tm_mday >= day));

	return current_time.tm_year + 1900 - year - 1 + birth; //�� ���� ���
}
