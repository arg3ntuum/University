#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#define K 50

void userSave(int** massive, int N) {
	char temp[K];
	int error = 0;
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) {
			do {
				error = 0;
				printf("�������[%d][%d] = ", i, j);
				scanf_s("%s", &temp, K - 1);
				for (int a = 0; a < strlen(temp); a++)
					if (atoi(temp) == 0 && !(('0' <= temp[a]) && (temp[a] <= '9')))
						error = 1;
				if (error == 1)
					printf("������� ����i��� ���� �����!\n");
				else {
					massive[i][j] = atoi(temp);
					break;
				}
			} while (1);
		}
}

void computerSave(int** massive, int N) {
	srand(time(NULL));
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
			massive[i][j] = rand() % 21 - 10;
}

void view(int** massive, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%5d", massive[i][j]);
		puts("");
	}
}

int choise() {
	int choise = 0;
	do {
		printf("�����i�� �����: \
			  \n1.�������� ������������;\
		      \n2.�������� ����'������;\
			  \n��� ���i�: ");
		scanf_s("%d", &choise);
	} while (choise != 1 && choise != 2);
	return choise;
}

int choiseN() {
	int N = 0;
	do {
		printf("�����i�� ����i� N x N(6 <= N <= 10): ");
		scanf_s("%d", &N);
	} while (!(6 <= N && N <= 10));
	return N;
}

void progress(int** massive, int N) {
	for (int i = 0, temp = 0; i < N; i++) {
		for (int j = 0; j < N; j++)	{
			if (i == j) {
				temp = massive[i][j];
				massive[i][j] = massive[i][N - 1 - i];
				massive[i][N - 1 - i] = temp;
			}
		}
	}
}

void main() {
	setlocale(LC_ALL, "Rus"); 
	int N = choiseN(), choose =  choise();

	int** massive = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		massive[i] = (int*)malloc(N * sizeof(int));
	
	if (choose == 1)
		userSave(massive, N); 
	else 
		computerSave(massive, N);

	printf("\t����� ��:\n");
	view(massive, N);

	progress(massive, N);

	printf("\t����� �I���:\n");
	view(massive, N);

	free(massive);
}
/*
��� �������� 2-�� �������� ���������:
1.	����������� ������� ��� ������� �������� �������� ������.
2.	����������� ������� ��� ������������� ���������� ������ � ������ ����� ������������ ���������� ���������� �����.
3.	����������� ������� ������� �� ��� �������� ����� �� ������� �������.
16.	������� ������ �������� ��������, �� ������ �� ������� �� ����-�� ���������.
*/