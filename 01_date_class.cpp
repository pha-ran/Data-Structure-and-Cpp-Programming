#include <iostream>
#include <string>

using namespace std;

int main() {

	int id, y, m, d;
	string dept, name;

	cout << "ȯ���մϴ�! �а���, �й�, �̸�, �������(yyyy/mm/dd)�� �Է��ϼ��� > ";

	cin >> dept >> id;
	cin.ignore(1, ','); // �Է� ���ۿ��� 1�� ����, ','�� ������ ','���� �� ����
	cin >> name >> y;
	cin.ignore(1, '/');
	cin >> m;
	cin.ignore(1, '/');
	cin >> d;

	// ���ڿ����� ',' ����
	dept.erase(remove(dept.begin(), dept.end(), ','), dept.end());
	name.erase(remove(name.begin(), name.end(), ','), name.end());

	cout << ">> " << dept << " " << id << " " << name << "�� " << y << "��" << m << "��" << d << "�ϻ� " << endl;

	return 0;
}