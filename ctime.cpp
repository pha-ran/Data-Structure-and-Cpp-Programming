#include <iostream>
#include <ctime>

#define KST (+9) // 한국 시간 (UTC +9)

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main() {

	time_t time_sec = time(NULL);
	/*
	유닉스 타임
	1970/1/1 0:0:0 (UTC, 협정 세계시) 기준 현재까지 흐른 초단위 시간을 인자에 전달하고 리턴
	time(&time_sec) 와 같음
	*/

	struct tm time_struct, k_time;
	/*
	시간 구조체 (struct tm) 의 멤버 변수와 의미, 값의 범위
	*멤버 변수	*의미					*값의 범위
	tm_sec		현재 시각이 몇 초 인지	[ 0 - 59 ]	// 윤초 설정시 60 또는 61이 될 수 있음
	tm_min		현재 시각이 몇 분 인지	[ 0 - 59 ]
	tm_hour		현재 시각이 몇 시 인지	[ 0 - 23 ]
	tm_mday		지금이 몇 일 인지		[ 1 - 31 ]
	tm_mon		지금이 몇 월 인지		[ 0 - 11 ]	// 1월 ( 0 ) - 12월 ( 11 )
	tm_year		지금이 몇 년 인지					// 1900년도 기준 경과 년 수 (2020년의 경우 120)
	tm_wday		지금이 무슨 요일 인지	[ 0 - 6 ]	// 일 ( 0 ) - 토 ( 6 )
	tm_yday		1월 1일 기준 경과 일 수	[ 0-365 ]	// 1월 1일 ( 0 ), 1월 2일 ( 1 ) ...
	tm_isdst	서머 타임제 실시 여부				// > 0 실시, = 0 미실시, < 0 알 수 없음
	*/

	localtime_s(&time_struct, &time_sec);	// 지역 시간 기준
	gmtime_s(&k_time, &time_sec);	// UTC 기준
	/*
	시간 구조체에 time_t형 시간을 단위 변환하여 전달
	실패 시 NULL 전달, 에러 원인은 errno를 통해 확인
	리눅스의 경우 localtime_r, gmtime_r 사용
	*/

	cout << time_struct.tm_year + 1900 << "년"	// tm_year는 1900년도 기준 경과 년 수
		 << time_struct.tm_mon + 1 << "월"		// tm_mon의 범위는 0 - 11
		 << time_struct.tm_mday << "일"
		 << time_struct.tm_hour << ":" << time_struct.tm_min << ":" << time_struct.tm_sec << endl;

	cout << k_time.tm_year + 1900 << "년" << k_time.tm_mon + 1 << "월" << k_time.tm_mday << "일"
		 << ( k_time.tm_hour + KST + 24 ) % 24 // 한국 시간 설정 (UTC +9)
		 << ":" << k_time.tm_min << ":" << k_time.tm_sec << endl;

	cout << endl;

	/*-------------------------------------------------------------------------------------------*/

	string w[] = { "일", "월", "화", "수", "목", "금", "토" };

	time_t current_time, input_time;

	time(&current_time); // 현재 시간
	localtime_s(&time_struct, &current_time); //시간 구조체를 현재 시간으로 설정

	cout << "현재 " << time_struct.tm_year + 1900 << "년" << time_struct.tm_mon + 1 << "월"
		 << time_struct.tm_mday << "일" << w[time_struct.tm_wday] << "요일"
		 << time_struct.tm_hour << ":" << time_struct.tm_min << ":" << time_struct.tm_sec << endl;

	cout << "더할 날짜 입력 : ";
	int i;
	cin >> i;
	time_struct.tm_mday += i;

	input_time = mktime(&time_struct);
	/*
	시간 구조체의 날짜와 시각을 time_t 형식으로 리턴 (wday와 yday는 무시)
	시간 구조체의 날짜와 시각에 알맞는 wday와 yday를 재설정
	*/

	double n = difftime(input_time, current_time);
	// (나중 시간, 이전 시간) 을 time_t형태의 인자로 받아서 두 시간의 차이를 리턴 ( double 형 )

	cout << (int)n / 60 / 60 / 24 << "일 경과" << endl;
	// 초단위 n을 일 단위로 변경

	cout << "이후 " << time_struct.tm_year + 1900 << "년" << time_struct.tm_mon + 1 << "월"
		 << time_struct.tm_mday << "일" << w[time_struct.tm_wday] << "요일"
		 << time_struct.tm_hour << ":" << time_struct.tm_min << ":" << time_struct.tm_sec << endl;

	return 0;
}