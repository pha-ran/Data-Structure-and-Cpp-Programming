#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {

	{
		//1차원 배열을 2차원 배열처럼 사용

		int M, N;

		cin >> M >> N;

		int *arr;

		arr = new int[M * N];

		// arr[ y * N + x ] 를 arr[y][x] 처럼 사용

		delete[] arr;
	}

	{
		//배열포인터 이용(컴파일 시 N이 상수일 경우에만 사용 가능, 3차원일경우( [L][M][N] ) M과 N이 상수 ... 등 )
	
		const int M = 3, N = 4;

		int (*arr)[N] = new int[M][N];
		//auto arr = new int[M][N]; <- C++11 이상

		delete[] arr;
	}
	
	{
		//포인터배열 이용(메모리 주소가 불연속이므로 느리고 비효율적)

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