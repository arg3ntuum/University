#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define K 50

void userSave(int** matrix, int N) {
	char temp[K];
	int error = 0;
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) {
			do {
				error = 0;
				printf("M��c��[%d][%d]: ", i, j);
				scanf_s("%s", &temp, K - 1);
				for (int k = 0; k < strlen(temp); k++)
					if (atoi(temp) == 0 && !(('0' <= temp[k]) && (temp[k] <= '9')))
						error = 1;
				if (error == 1)	puts("������� ����� ������ �����!\n");
				else {
					matrix[i][j] = atoi(temp);
					break;
				}
			} while (1);
		}
}

void autoSave(int** matrix, int N) {
	srand(time(NULL));
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
			matrix[i][j] = rand() % 21 - 10;
}

void seeMassive(int** matrix, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%4d", matrix[i][j]);
		puts("");
	}
}

void changeMassive(int** matrix, int N) {
	int gol_diagonal = 0, druga_diagonal = N;
	for (int i = 0; i < N; i++) {
		druga_diagonal--;
		for (int j = 0, k = 0; j < N; j++)
			if (i < j && druga_diagonal<j){
				matrix[i][j] = 0;
			}
	}
}

int choiseMode() {
	int choise = 0;
	do {
		printf("�������� ������ �������� ����� � ������: \
			  \n1.� ������� ������������;\
		      \n2.� ������� ����������;\
			  \n��� �����: ");
		scanf_s("%d", &choise);
	} while (choise != 1 && choise != 2);
	return choise;
}

int choiseN() {
	int N = 0;
	do {
		printf("�������� ������ ������� N x N(6 <= N <= 10): ");
		scanf_s("%d", &N);
	} while (!(6 <= N && N <= 10));
	return N;
}

void main() {
	setlocale(LC_ALL, "Rus");
	int N = 0, choise = 0;

	N = choiseN();
	choise = choiseMode();
	
	int** matrix = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		matrix[i] = (int*)malloc(N * sizeof(int));

	if (choise == 1)
		userSave(matrix, N); 
	else autoSave(matrix, N);

	printf("\t��c��� �� ���������:\n");
	seeMassive(matrix, N); 

	changeMassive(matrix, N);

	printf("\t��c��� ����� ���������:\n");
	seeMassive(matrix, N);
	free(matrix); //�������� ���'��
}
/*
��� �������� 2-�� �������� ���������:
1.	����������� ������� ��� ������� �������� �������� ������.
2.	����������� ������� ��� ������������� ���������� ������ � ������ ����� ������������ ���������� ���������� �����.
3.	����������� ������� ������� �� ��� �������� ����� �� ������� �������.

15.	������� ������ �� �������� �������, �� ����������� � ������ 4 ���-����, �������� �� ���. �.1).
*/