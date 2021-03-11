#include<iostream>

using namespace std;

void print_str(const char* str); //한글 영문 혼합 문자열 한 글자씩 출력
int compare_str(const char* str1, const char* str2); //두 문자열을 비교하여 같으면 0, str1이 크면 1, str2가 크면 2를 리턴

int main() {
		
	return 0;
}

//바이트의 최상위 비트가 1일 경우 그 뒤의 바이트와 합하여 하나의 글자를 나타낸다
//또한 합쳐지는 모든 바이트의 최상위 비트도 1
//ASCII : 0x00 ~ 0x7f (16진수) /  0 ~ 127 (10진수) / 0000 0000 ~ 0111 1111
//( [0x80과 & 연산] 또는 [시프트 연산(>> 7)] 으로 바이트의 최상위 비트 판별 가능 )

//한글 영문 혼합 문자열 한 글자씩 출력
void print_str(const char* str) {
	for (int i = 0; str[i] != NULL; i++) {
		if (str[i] & 0x80) { //최상위 비트가 1일 경우
			cout << str[i] << str[i + 1]; //2바이트 출력
			i++;
		}
		else { //최상위 비트가 0일 경우
			cout << str[i]; //1바이트 출력
		}
	}
	cout << endl;
}

//두 문자열을 비교하여 같으면 0, str1이 크면 1, str2가 크면 2를 리턴
int compare_str(const char* str1, const char* str2) {

	int i = 0, j = 0;

	for (; str1[i] != NULL && str2[j] != NULL; i++, j++) {
		if (str1[i] > str2[j]) { return 1; }
		else if (str1[i] < str2[j]) { return 2; }
		else { //현재 글자가 같을때
			if (str1[i] & 0x80) { i++; } //최상위 비트가 1일 경우, 인덱스 + 1
			if (str2[j] & 0x80) { j++; } //최상위 비트가 1일 경우, 인덱스 + 1
		}
	}

	if (str1[i] == NULL && str2[j] == NULL) { return 0; }
	else if (str1[i] == NULL) { return 2; }
	else if (str2[j] == NULL) { return 1; }
	else { return -1; }
}