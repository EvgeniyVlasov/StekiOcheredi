/*
������:
������ �������������� ��������� � �������� �������� ������
��������� ������������ ������ � ������� �������� ���������.

� ���� ����� ����������� ���� � �������� �������� �������� ������, � ����� ���������� ��������� ���. ���������.

������ ������� ���-13��.

*/

#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define N 50
#define M 2

//������� ����� � �������� �������� �������� ������.
int* EnteringAndCheckingNotation(int n) {
	//������ � �������.
	float A[N];
	//������ � ��������������� ���������.
	char B[N];
	//���������� ������� ����� ���������
	//��� ����� ������, ��� ������ 2 ����� ����� ���� ������ ��������, �� �� ����� ���-�� ��������. ��������, 1234
	printf_s("1-st number of notation: ");
	if (!scanf_s("%f", &A[0])) {
		printf_s("Wrong number\n");
		system("pause");
		exit(0);
	}
	//����������� �������� ������ ���� ��-��� ������� B[N], �.�. ��� ����� �� ���.
	B[0] = '.';
	B[1] = '.';
	//���� �������� �������� ������.
	printf_s("Reverse Polish notation: ");
	int i = 1;
	while (i < n) {
		//���������� �����.
		if (!scanf_s("%f", &A[i])) {
			printf_s("Wrong number\n");
			system("pause");
			exit(0);
		}
		//������ ������ ������� �� ���. => �� =0.
		i++;
		A[i] = 0;
		//���������� �������.
		if (!scanf_s("%c", &B[i])) {
			printf_s("Wrong symbol\n");
			system("pause");
			exit(0);
		}
		//���� ��� ������ ���. ������, �� ��������� � ������ �������� ������ �� ���. => �� ='.',
		//����� ������ ������� � ����� �� ���������.
		if (B[i] == '+' || B[i] == '-' || B[i] == '*' || B[i] == '/') {
			i++;
			B[i] = '.';
			continue;
		}
		else {
			printf_s("Wrong symbol\n");
			system("pause");
			exit(0);
		}
	}

	/*
	int e = SolveNotation(&A, B, n);
	return;
}
int* SolveNotation(float A[N], char B[N], int n) {
*/

//C[N] - ����, ������� ������ ����� ��� ���. ��������.
	float C[N];
	//���������� a - �������� �����.
	float a = 0;
	//�������������� ������ C[N] � ������� ��� ����������� � ��� ������.
	for (int i = 0; i <= n + 1; i++)
		C[i] = 0;
	//������� �������� � �����, �.�. ��� �������� ����� ������� ���������.
	for (int i = 2; i < n; i = i + 2) {
		if (B[i] == '*') {
			//���� ����� ���� ������������� �����, �� ����������� � ����� ����. �����.
			if (C[i - 2] != 0) {
				C[i] = a * A[i - 1];
				a = C[i];
			}
			//���� ����� ��� �������������� ������ � ��� �� ������ ����, �� ����������� � ����� ����. �����.
			if (C[i - 2] == 0 && B[i - 2] != '.') {
				C[i] = A[i - 3] * A[i - 1];
				a = C[i];
			}
			//���� ����� ��� �������������� ������ � ��� ������ ����, �� ����������� � ����� ����. �����.
			if (C[i - 2] == 0 && B[i - 2] == '.') {
				C[i] = A[i - 2] * A[i - 1];
				a = C[i];
			}
		}
		if (B[i] == '/') {
			//���� ��������� ������� �� 0, �� �������������� � ���������� ������ ���������.
			if (A[i - 1] == 0) {
				printf_s("You can't divide by 0");
				system("pause");
				exit(0);
			}
				//���� ����� ��� ���� ������������� �����, �� �������� � ����� ����. �����.
			if (C[i - 2] != 0) {
				C[i] = a / A[i - 1];
				a = C[i];
			}
				//���� ����� ���� ������������� ����� � ��� ������ ����, �� ��������� � ����� ����. �����.
			if (C[i - 2] == 0 && B[i - 2] != '.') {
				C[i] = A[i - 3] / A[i - 1];
				a = C[i];
			}
				//���� ����� ��� �������������� ������ � ��� ������ ����, �� ��������� � ����� ����. �����.
			if (C[i - 2] == 0 && B[i - 2] == '.') {
				C[i] = A[i - 2] / A[i - 1];
				a = C[i];
			}
		}
	}

	//������ ���������� � ��������, �.�. ��� �������� ����� ������� ���������.
	for (int i = 2; i < n; i = i + 2) {
		if (B[i] == '+') {
			//���� ��� �� ������ ������.
			if (B[i - 2] != '.') {
				//���� ����. ����� ������ ��������� C[i +- 2], ��
				if (C[i - 2] != 0 && C[i + 2] != 0 && C[i - 2] != a && C[i + 2] != a) {
					//k - ����������� ��� �������� ������� ������� � �����, j - ����������� ������.
					int k = 0, j = i;
					//���� ����. ����� ���. ������ � �� '+' ��� '-', �� ���������� � ����� ����. �����.
					for (int j = i + 2; B[j - 1] != '+' && B[j - 1] != '-' && j < n; j++) {
						if (C[j] == a) {
							C[i] = C[i - 2] + a;
							a = C[i];
							k++;
							break;
						}
					}
					//���� ����. ����� ���. ����� � �� '+' ��� '-', �� ���������� � ����� ����. �����.
					for (int j = i - 2; B[j + 1] != '+' && B[j + 1] != '-' && j >= 0; j--) {
						if (C[j] == a) {
							C[i] = C[i + 2] + a;
							a = C[i];
							k++;
							break;
						}
					}
					//���� ����. ������ �� �������, �� ���������� � ����� ����. �����.
					if (k == 0) {
						C[i] = C[i - 2] - C[i + 2];
						a = C[i];
					}
				}
				//���� ������ ������ ��� � ����. ����� ���. �����, �� ���������� � ����� ����. �����.
				if (C[i - 2] != 0 && C[i + 2] == 0) {
					C[i] = a + A[i - 1];
					a = C[i];
				}
				//���� ����� ������ ��� � ����. ����� ���. ������, �� ���������� � ����� ����. �����.
				if (C[i - 2] == 0 && C[i + 2] != 0) {
					C[i] = A[i - 1] + a;
					a = C[i];
				}
				//���� � ����� ������ ���� ����� � ����. ����� ���. �����, �� ���������� � ����� ����. �����.
				if (C[i - 2] != 0 && C[i + 2] != 0 && C[i - 2] == a) {
					C[i] = a + A[i - 1];
					a = C[i];
				}
				//���� � ����� ������ ���� ����� � ����. ����� ���. ������, �� ���������� � ����� ����. �����.
				if (C[i - 2] != 0 && C[i + 2] != 0 && C[i + 2] == a) {
					C[i] = A[i - 1] + a;
					a = C[i];
				}
			}
			//���� ��� ������ ������.
			else {
				//���� ������ ������ ���, �� ���������� � ����� ����. �����.
				if (C[i + 2] == 0) {
					C[i] = A[i - 2] + A[i - 1];
					a = C[i];
				}
				//���� ������ ���� �����, �� �� ����. �����, �� ���������� � ����� ����. �����.
				if (C[i + 2] != a && C[i + 2] != 0) {
					C[i] = A[i - 2] + a;
					a = C[i];
				}
				//���� ������ ����. �����, �� ���������� � ����� ����. �����.
				if (C[i + 2] == a) {
					C[i] = a + A[i - 2];
					a = C[i];
				}
			}
		}
		if (B[i] == '-') {
			//���� ��� �� ������ ������.
			if (B[i - 2] != '.') {
				//���� ����. ����� ������ ��������� C[i +- 2], ��
				if (C[i - 2] != 0 && C[i + 2] != 0 && C[i - 2] != a && C[i + 2] != a) {
					//k - ����������� ��� �������� ������� ������� � �����, j - ����������� ������.
					int k = 0, j = i;
					//���� ����. ����� ���. ������ � �� '+' ��� '-', �� �������� � ����� ����. �����.
					for (int j = i + 2; B[j - 1] != '+' && B[j - 1] != '-' && j < n; j++) {
						if (C[j] == a) {
							C[i] = C[i - 2] - a;
							a = C[i];
							k++;
							break;
						}
					}
					//���� ����. ����� ���. ����� � �� '+' ��� '-', �� �������� � ����� ����. �����.
					for (int j = i - 2; B[j + 1] != '+' && B[j + 1] != '-' && j >= 0; j--) {
						if (C[j] == a) {
							C[i] = C[i + 2] - a;
							a = C[i];
							k++;
							break;
						}
					}
					//���� ����. ������ �� �������, �� �������� � ����� ����. �����.
					if (k == 0) {
						C[i] = C[i - 2] - C[i + 2];
						a = C[i];
					}
				}
				//���� ������ ������ ��� � ����. ����� ���. �����, �� �������� � ����� ����. �����.
				if (C[i - 2] != 0 && C[i + 2] == 0) {
					C[i] = a - A[i - 1];
					a = C[i];
				}
				//���� ����� ������ ��� � ����. ����� ���. ������, �� �������� � ����� ����. �����.
				if (C[i - 2] == 0 && C[i + 2] != 0) {
					C[i] = A[i - 1] - a;
					a = C[i];
				}
				//���� � ����� ������ ���� ����� � ����. ����� ���. �����, �� �������� � ����� ����. �����.
				if (C[i - 2] != 0 && C[i + 2] != 0 && C[i - 2] == a) {
					C[i] = a - A[i - 1];
					a = C[i];
				}
				//���� � ����� ������ ���� ����� � ����. ����� ���. ������, �� �������� � ����� ����. �����.
				if (C[i - 2] != 0 && C[i + 2] != 0 && C[i + 2] == a) {
					C[i] = A[i - 1] - a;
					a = C[i];
				}
			}
			//���� ��� ������ ������.
			else {
				//���� ������ ������ ���, �� �������� � ����� ����. �����.
				if (C[i + 2] == 0) {
					C[i] = A[i - 2] - A[i - 1];
					a = C[i];
				}
				//���� ������ ���� �����, �� �� ����. �����, �� �������� � ����� ����. �����.
				if (C[i + 2] != a  && C[i + 2] != 0) {
					C[i] = A[i - 2] - a;
					a = C[i];
				}
				//���� ������ ����. �����, �� �������� � ����� ����. �����.
				if (C[i + 2] == a) {
					C[i] = a - A[i - 2];
					a = C[i];
				}
			}
		}
	}
	//����� ������.
	printf_s("Answer: %.3f\n", a);
	system("pause");
	return;
}