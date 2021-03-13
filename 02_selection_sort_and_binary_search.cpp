#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>

#define R 1001
using namespace std;

void del_special(char* str); //���ڿ����� ���ڿ� Ư�����ڵ��� ����
void selection_sort_str(char(*str)[R]); //�ܾ���� ���� ���� �˰����� �̿��Ͽ� ����
void deduplication_str(char(*str)[R]); //�ߺ� �ܾ ����
int binary_search_str(char(*str)[R], const char* search); //���� Ž������ �ܾ �˻��Ͽ� ���� �ܾ ������ �� ��° �ܾ�����, ������ -1�� ����

char WordDataSet[R][R]; // ���� �����͸� ����ִ� 2���� �迭
int index = 0; //�Է¹��� �ܾ� ��

int main() {

	FILE* f = fopen("input.txt", "r"); // ������ �б� �������� ����

	if (f == NULL) printf("None file\n"); // ������ �������� ���� ���

	while (!feof(f)) {
		fscanf(f, "%s", WordDataSet[index]); // �ؽ�Ʈ���Ͽ��� ���ڿ��� �Է�
		index++;
	}

	cout << "---�Է����� ����---\n";

	for (int i = 0; i < index; i++) { // ����� ���ڿ��� ���
		printf("%s ", WordDataSet[i]);
	}

	cout << "\n\n---�����ȣ ���� ���---\n";

	for (int i = 0; i < index; i++) { // ��� ���ڿ����� ���ڿ� Ư������ ����
		del_special(WordDataSet[i]);
	}

	for (int i = 0; i < index; i++) { // ����� ���ڿ��� ���
		printf("%s ", WordDataSet[i]);
	}

	cout << "\n\n---�ܾ� ���� ���---\n";

	selection_sort_str(WordDataSet); //���� ���ķ� ����

	for (int i = 0; i < index; i++) { // ����� ���ڿ��� ���
		printf("%d.\t%s\n", i + 1, WordDataSet[i]);
	}

	cout << "\n\n---�ߺ� ���� ���---\n";

	deduplication_str(WordDataSet); //�ߺ� �ܾ� ����

	for (int i = 0; i < index; i++) { // ����� ���ڿ��� ���
		printf("%d.\t%s\n", i + 1, WordDataSet[i]);
	}

	cout << "\n\n---�ܾ� �˻�---\n";

	while (true) {
		char search[R];

		cin >> search;

		if (search[0] == '.') { //'.'�Է½� ���α׷� ����
			cout << "���α׷� ����" << endl;
			break;
		}

		cout << binary_search_str(WordDataSet, search) << "\n" << endl; //�˻� ��� ���
	}

	return 0;
}

//����Ʈ�� �ֻ��� ��Ʈ�� 1�� ��� �� ���� ����Ʈ�� ���Ͽ� �ϳ��� ���ڸ� ��Ÿ����
//���� �������� ��� ����Ʈ�� �ֻ��� ��Ʈ�� 1
//ASCII : 0x00 ~ 0x7f (16����) /  0 ~ 127 (10����) / 0000 0000 ~ 0111 1111
//( [0x80�� & ����] �Ǵ� [����Ʈ ����(>> 7)] ���� ����Ʈ�� �ֻ��� ��Ʈ �Ǻ� ���� )

//���ڿ����� ���ڿ� Ư�����ڵ��� ����
void del_special(char* str) {
	for (int i = 0; str[i] != NULL; i++) {
		if (str[i] & 0x80) { i++; } //�ֻ��� ��Ʈ�� 1�� ���, �ε��� + 1
		else if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) { continue; } //���ĺ��� ���
		else { //���ڿ� Ư�������� ���
			for (int j = i; str[j] != NULL; j++) { //���� �ε������� ���� ���ڿ��� ����
				str[j] = str[j + 1]; //������ ���ڿ��� NULL���� ����� �� ����
			}

			i--; //�ε����� ��ĭ�� �ٿ� ���������Ƿ� ���� ���ں��� Ž��
		}
	}
}

//�ܾ���� ���� ���� �˰����� �̿��Ͽ� ����
void selection_sort_str(char(*str)[R]) {
	for (int i = 0; i < index; i++) {

		int min = i;

		for (int j = i + 1; j < index; j++) {
			if (strcmp(str[j], str[min]) < 0) { //str[j]�� �� ���� ���
				min = j;
			}
		}

		swap(str[i], str[min]);
	}
}

//�ߺ� �ܾ ����
void deduplication_str(char(*str)[R]) {
	for (int i = 0; i < index; i++) {
		if (strcmp(str[i], str[i + 1]) == 0) {
			for (int j = i; j < index; j++) {
				swap(str[j], str[j + 1]);
			}

			index--; //��ü �ܾ��� �� ����
			i--; //�ε����� ��ĭ�� �ٿ� ���������Ƿ� ���� �ܾ���� Ž��
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

	return -1; //�ش� �ܾ ���� ���
}