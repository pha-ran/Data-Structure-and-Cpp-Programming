#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

#define R 1001
using namespace std;

void del_special(char* str); //문자열에서 숫자와 특수문자들을 제거
void selection_sort_str(char(*str)[R]); //단어들을 선택 정렬 알고리즘을 이용하여 정렬
void deduplication_str(char(*str)[R]); //중복 단어를 제거
int binary_search_str(char(*str)[R], const char* search); //이진 탐색으로 단어를 검색하여 같은 단어가 있으면 몇 번째 단어인지, 없으면 -1을 리턴

char WordDataSet[R][R]; // 받은 데이터를 담고있는 2차원 배열
int index = 0; //입력받은 단어 수

int main() {

	FILE* f = fopen("input.txt", "r"); // 파일을 읽기 형식으로 열기

	if (f == NULL) printf("None file\n"); // 파일이 존재하지 않을 경우

	while (!feof(f)) {
		fscanf(f, "%s", WordDataSet[index]); // 텍스트파일에서 문자열을 입력
		index++;
	}

	cout << "---입력파일 내용---\n";

	for (int i = 0; i < index; i++) { // 저장된 문자열을 출력
		printf("%s ", WordDataSet[i]);
	}

	cout << "\n\n---문장부호 제거 결과---\n";

	for (int i = 0; i < index; i++) { // 모든 문자열들의 숫자와 특수문자 제거
		del_special(WordDataSet[i]);
	}

	for (int i = 0; i < index; i++) { // 저장된 문자열을 출력
		printf("%s ", WordDataSet[i]);
	}

	cout << "\n\n---단어 정렬 결과---\n";

	selection_sort_str(WordDataSet); //선택 정렬로 정렬

	for (int i = 0; i < index; i++) { // 저장된 문자열을 출력
		printf("%d.\t%s\n", i + 1, WordDataSet[i]);
	}

	cout << "\n\n---중복 제거 결과---\n";

	deduplication_str(WordDataSet); //중복 단어 제거

	for (int i = 0; i < index; i++) { // 저장된 문자열을 출력
		printf("%d.\t%s\n", i + 1, WordDataSet[i]);
	}

	cout << "\n\n---단어 검색---\n";

	while (true) {
		char search[R];

		cin >> search;

		if (search[0] == '.') { //'.'입력시 프로그램 종료
			cout << "프로그램 종료" << endl;
			break;
		}

		cout << binary_search_str(WordDataSet, search) << "\n" << endl; //검색 결과 출력
	}

	return 0;
}

//바이트의 최상위 비트가 1일 경우 그 뒤의 바이트와 합하여 하나의 글자를 나타낸다
//또한 합쳐지는 모든 바이트의 최상위 비트도 1
//ASCII : 0x00 ~ 0x7f (16진수) /  0 ~ 127 (10진수) / 0000 0000 ~ 0111 1111
//( [0x80과 & 연산] 또는 [시프트 연산(>> 7)] 으로 바이트의 최상위 비트 판별 가능 )

//문자열에서 숫자와 특수문자들을 제거
void del_special(char* str) {
	for (int i = 0; str[i] != NULL; i++) {
		if (str[i] & 0x80) { i++; } //최상위 비트가 1일 경우, 인덱스 + 1
		else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) { continue; } //알파벳일 경우
		else { //숫자와 특수문자일 경우
			for (int j = i; str[j] != NULL; j++) { //현재 인덱스부터 뒤쪽 문자열을 복사
				str[j] = str[j + 1]; //마지막 글자에서 NULL까지 복사된 후 종료
			}

			i--; //인덱스를 한칸씩 줄여 복사했으므로 현재 문자부터 탐색
		}
	}
}

//단어들을 선택 정렬 알고리즘을 이용하여 정렬
void selection_sort_str(char(*str)[R]) {
	for (int i = 0; i < index; i++) {

		int min = i;

		for (int j = i + 1; j < index; j++) {
			if (strcmp(str[j], str[min]) < 0) { //str[j]가 더 작을 경우
				min = j;
			}
		}

		swap(str[i], str[min]);
	}
}

//중복 단어를 제거
void deduplication_str(char(*str)[R]) {
	for (int i = 0; i < index; i++) {
		if (strcmp(str[i], str[i + 1]) == 0) {
			for (int j = i; j < index; j++) {
				swap(str[j], str[j + 1]);
			}

			index--; //전체 단어의 수 감소
			i--; //인덱스를 한칸씩 줄여 복사했으므로 현재 단어부터 탐색
		}
	}
}

int binary_search_str(char(*str)[R], const char* search) {
	int left = 0, right = index - 1, middle = (left + right) / 2;

	while (left <= right) {
		if (strcmp(str[middle], search) == 0) { return middle + 1; }
		else if (strcmp(search, str[middle]) < 0) {
			right = middle - 1;
			middle = (left + right) / 2;
		}
		else if (strcmp(search, str[middle]) > 0) {
			left = middle + 1;
			middle = (left + right) / 2;
		}
		else { return -1; }
	}

	return -1; //해당 단어가 없을 경우
}