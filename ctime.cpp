#include <iostream>
#include <ctime>

#define KST (+9) // �ѱ� �ð� (UTC +9)

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main() {

	time_t time_sec = time(NULL);
	/*
	���н� Ÿ��
	1970/1/1 0:0:0 (UTC, ���� �����) ���� ������� �帥 �ʴ��� �ð��� ���ڿ� �����ϰ� ����
	time(&time_sec) �� ����
	*/

	struct tm time_struct, k_time;
	/*
	�ð� ����ü (struct tm) �� ��� ������ �ǹ�, ���� ����
	*��� ����	*�ǹ�					*���� ����
	tm_sec		���� �ð��� �� �� ����	[ 0 - 59 ]	// ���� ������ 60 �Ǵ� 61�� �� �� ����
	tm_min		���� �ð��� �� �� ����	[ 0 - 59 ]
	tm_hour		���� �ð��� �� �� ����	[ 0 - 23 ]
	tm_mday		������ �� �� ����		[ 1 - 31 ]
	tm_mon		������ �� �� ����		[ 0 - 11 ]	// 1�� ( 0 ) - 12�� ( 11 )
	tm_year		������ �� �� ����					// 1900�⵵ ���� ��� �� �� (2020���� ��� 120)
	tm_wday		������ ���� ���� ����	[ 0 - 6 ]	// �� ( 0 ) - �� ( 6 )
	tm_yday		1�� 1�� ���� ��� �� ��	[ 0-365 ]	// 1�� 1�� ( 0 ), 1�� 2�� ( 1 ) ...
	tm_isdst	���� Ÿ���� �ǽ� ����				// > 0 �ǽ�, = 0 �̽ǽ�, < 0 �� �� ����
	*/

	localtime_s(&time_struct, &time_sec);	// ���� �ð� ����
	gmtime_s(&k_time, &time_sec);	// UTC ����
	/*
	�ð� ����ü�� time_t�� �ð��� ���� ��ȯ�Ͽ� ����
	���� �� NULL ����, ���� ������ errno�� ���� Ȯ��
	�������� ��� localtime_r, gmtime_r ���
	*/

	cout << time_struct.tm_year + 1900 << "��"	// tm_year�� 1900�⵵ ���� ��� �� ��
		 << time_struct.tm_mon + 1 << "��"		// tm_mon�� ������ 0 - 11
		 << time_struct.tm_mday << "��"
		 << time_struct.tm_hour << ":" << time_struct.tm_min << ":" << time_struct.tm_sec << endl;

	cout << k_time.tm_year + 1900 << "��" << k_time.tm_mon + 1 << "��" << k_time.tm_mday << "��"
		 << ( k_time.tm_hour + KST + 24 ) % 24 // �ѱ� �ð� ���� (UTC +9)
		 << ":" << k_time.tm_min << ":" << k_time.tm_sec << endl;

	cout << endl;

	/*-------------------------------------------------------------------------------------------*/

	string w[] = { "��", "��", "ȭ", "��", "��", "��", "��" };

	time_t current_time, input_time;

	time(&current_time); // ���� �ð�
	localtime_s(&time_struct, &current_time); //�ð� ����ü�� ���� �ð����� ����

	cout << "���� " << time_struct.tm_year + 1900 << "��" << time_struct.tm_mon + 1 << "��"
		 << time_struct.tm_mday << "��" << w[time_struct.tm_wday] << "����"
		 << time_struct.tm_hour << ":" << time_struct.tm_min << ":" << time_struct.tm_sec << endl;

	cout << "���� ��¥ �Է� : ";
	int i;
	cin >> i;
	time_struct.tm_mday += i;

	input_time = mktime(&time_struct);
	/*
	�ð� ����ü�� ��¥�� �ð��� time_t �������� ���� (wday�� yday�� ����)
	�ð� ����ü�� ��¥�� �ð��� �˸´� wday�� yday�� �缳��
	*/

	double n = difftime(input_time, current_time);
	// (���� �ð�, ���� �ð�) �� time_t������ ���ڷ� �޾Ƽ� �� �ð��� ���̸� ���� ( double �� )

	cout << (int)n / 60 / 60 / 24 << "�� ���" << endl;
	// �ʴ��� n�� �� ������ ����

	cout << "���� " << time_struct.tm_year + 1900 << "��" << time_struct.tm_mon + 1 << "��"
		 << time_struct.tm_mday << "��" << w[time_struct.tm_wday] << "����"
		 << time_struct.tm_hour << ":" << time_struct.tm_min << ":" << time_struct.tm_sec << endl;

	return 0;
}