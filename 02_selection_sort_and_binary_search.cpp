#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>

#define R 1001
using namespace std;

void print_str(const char* str); //한글 영문 혼합 문자열 한 글자씩 출력
int compare_str(const char* str1, const char* str2); //두 문자열을 비교하여 같으면 0, str1이 크면 1, str2가 크면 2를 리턴
void del_special(char* str); //문자열에서 숫자와 특수문자들을 제거

char WordDataSet[R][R]; // 받은 데이터를 담고있는 2차원 배열입니다.
int index = 0; //입력받은 단어 수

int main() {

	FILE* f = fopen("input.txt", "r"); // 파일을 읽기 형식으로 열기

	if (f == NULL) printf("None file\n"); // 파일이 존재하지 않을 경우

	while (!feof(f)) {
		fscanf(f, "%s", WordDataSet[index]); // 텍스트파일에서 문자열을 받습니다.
		index++;
	}

	for (int i = 0; i < index; i++) { // 저장된 문자열을 출력
		printf("%s ", WordDataSet[i]);
	}

	cout << "\n\n---숫자와 특수문자 제거 후---\n";

	for (int i = 0; i < index; i++) { // 모든 문자열들의 특수문자 제거
		del_special(WordDataSet[i]);
	}

	for (int i = 0; i < index; i++) { // 저장된 문자열을 출력
		printf("%d.\t%s\n", i + 1, WordDataSet[i]);
	}

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

//문자열에서 숫자와 특수문자들을 제거
void del_special(char* str) {
	for (int i = 0; str[i] != NULL; i++) {
		if (str[i] & 0x80) { i++; } //최상위 비트가 1일 경우, 인덱스 + 1
		else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) { continue; } //알파벳일 경우
		else { //특수문자일 경우
			for (int j = i; str[j] != NULL; j++) { //현재 인덱스부터 뒤쪽 문자열을 복사
				str[j] = str[j + 1]; //마지막 글자에서 NULL까지 복사된 후 종료
			}

			i--; //인덱스를 한칸씩 줄여 복사했으므로 이전 인덱스부터 탐색
		}
	}
}
