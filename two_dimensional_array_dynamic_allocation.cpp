#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {

	{
		//1���� �迭�� 2���� �迭ó�� ���

		int M, N;

		cin >> M >> N;

		int *arr;

		arr = new int[M * N];

		// arr[ y * N + x ] �� arr[y][x] ó�� ���

		delete[] arr;
	}

	{
		//�迭������ �̿�(������ �� N�� ����� ��쿡�� ��� ����, 3�����ϰ��( [L][M][N] ) M�� N�� ��� ... �� )
	
		const int M = 3, N = 4;

		int (*arr)[N] = new int[M][N];
		//auto arr = new int[M][N]; <- C++11 �̻�

		delete[] arr;
	}
	
	{
		//�����͹迭 �̿�(�޸� �ּҰ� �ҿ����̹Ƿ� ������ ��ȿ����)

		int M, N;

		cin >> M >> N;

		int** arr;

		arr = new int* [M];

		for (int i = 0; i < M; i++) {
			arr[i] = new int[N];
		}

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cin >> arr[i][j];
			}
		}

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				cout << arr[i][j];
			}
			cout << endl;
		}

		for (int i = 0; i < M; i++) {
			delete[] arr[i];
		}

		delete[] arr;
	}

	return 0;
}