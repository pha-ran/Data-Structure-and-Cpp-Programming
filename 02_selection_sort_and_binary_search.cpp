#include<iostream>

using namespace std;

void print_str(const char* str); //�ѱ� ���� ȥ�� ���ڿ� �� ���ھ� ���
int compare_str(const char* str1, const char* str2); //�� ���ڿ��� ���Ͽ� ������ 0, str1�� ũ�� 1, str2�� ũ�� 2�� ����

int main() {
		
	return 0;
}

//����Ʈ�� �ֻ��� ��Ʈ�� 1�� ��� �� ���� ����Ʈ�� ���Ͽ� �ϳ��� ���ڸ� ��Ÿ����
//���� �������� ��� ����Ʈ�� �ֻ��� ��Ʈ�� 1
//ASCII : 0x00 ~ 0x7f (16����) /  0 ~ 127 (10����) / 0000 0000 ~ 0111 1111
//( [0x80�� & ����] �Ǵ� [����Ʈ ����(>> 7)] ���� ����Ʈ�� �ֻ��� ��Ʈ �Ǻ� ���� )

//�ѱ� ���� ȥ�� ���ڿ� �� ���ھ� ���
void print_str(const char* str) {
	for (int i = 0; str[i] != NULL; i++) {
		if (str[i] & 0x80) { //�ֻ��� ��Ʈ�� 1�� ���
			cout << str[i] << str[i + 1]; //2����Ʈ ���
			i++;
		}
		else { //�ֻ��� ��Ʈ�� 0�� ���
			cout << str[i]; //1����Ʈ ���
		}
	}
	cout << endl;
}

//�� ���ڿ��� ���Ͽ� ������ 0, str1�� ũ�� 1, str2�� ũ�� 2�� ����
int compare_str(const char* str1, const char* str2) {

	int i = 0, j = 0;

	for (; str1[i] != NULL && str2[j] != NULL; i++, j++) {
		if (str1[i] > str2[j]) { return 1; }
		else if (str1[i] < str2[j]) { return 2; }
		else { //���� ���ڰ� ������
			if (str1[i] & 0x80) { i++; } //�ֻ��� ��Ʈ�� 1�� ���, �ε��� + 1
			if (str2[j] & 0x80) { j++; } //�ֻ��� ��Ʈ�� 1�� ���, �ε��� + 1
		}
	}

	if (str1[i] == NULL && str2[j] == NULL) { return 0; }
	else if (str1[i] == NULL) { return 2; }
	else if (str2[j] == NULL) { return 1; }
	else { return -1; }
}