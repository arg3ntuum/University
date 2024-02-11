#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define K 50

//���������� ������� �������������
void client_input(int** massive, int N) {
	char temp[K];
	int pomilka = 0;
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
		{
			do {
				pomilka = 0;
				printf("�atrix[%d][%d] = ", i, j);
				scanf_s("%s", &temp, K - 1);
				for (int a = 0; a < strlen(temp); a++)
					if (atoi(temp) == 0 && !(('0' <= temp[a]) && (temp[a] <= '9')))
						pomilka = 1;
				if (pomilka == 1)
					printf("������� ������ �����!\n");
				else {
					massive[i][j] = atoi(temp);
					break;
				}
			} while (1);
		}
}

//�������������� ����������
void random_input(int** massive, int N) {
	srand(time(NULL));
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
			massive[i][j] = rand() % 21 - 10;
}

//�������� �������
void out_matrix(int** massive, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%4d", massive[i][j]);
		puts("");
	}
}

//����� �������
void out_vektor(int* massive, int N) {
	printf("\t\t������ ���������� � ������� �� ������:\n");
	for (int i = 0; i < N; i++) {
		printf("������ ���������� � ������� �� ������ %d = %3d", i, massive[i]);
		printf("\n");
	}
}

//��������� �������
void calc_vektor(int** massive, int* vektor, int N) {
	int min;
	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			if (j == 0)
				min = abs(massive[i][j]);
			else if (min > abs(massive[i][j]))
				min = abs(massive[i][j]);
		}
		vektor[j] = min;
	}
}

//C���� ��������
void sum_out(int* massive, int N) {
	puts("");
	int sum = 0;
	for (int i = 0; i < N; i++)
		sum += massive[i];
	printf("C���� �������� = %d", sum);
	puts("");
	puts("");
}

//������� ����� ����������
int choise_mode() {
	int choose = 0;
	do {
		printf("�������� ����� ������� ���������� �������: \
			  \n1.����������������;\
		      \n2.��������������;\
			  \n��� �����: ");
		scanf_s("%d", &choose);
	} while (choose != 1 && choose != 2);
	return choose;
}

//������� N
int choise_N() {
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

	N = choise_N();
	choise = choise_mode();
	
	int** matrix = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		matrix[i] = (int*)malloc(N * sizeof(int));
	int* vektor = (int*)malloc(N * sizeof(int));

	if (choise == 1)
		client_input(matrix, N); 
	else random_input(matrix, N);

	printf("\t��c���:\n");
	out_matrix(matrix, N); 

	calc_vektor(matrix, vektor, N);
	out_vektor(vektor, N);
	sum_out(vektor, N);
	
	free(matrix); //�������� ���'��
}
/*
��� �������� 2-�� �������� ���������:
1.	����������� ������� ��� ������� �������� �������� ������.
2.	����������� ������� ��� ������������� ���������� ������ � ������ ����� ������������ ���������� ���������� �����.
3.	����������� ������� ������� �� ��� �������� ����� �� ������� �������.
6.	������ �������� �� ������� �������� ������� ������� ������� �� �� ����������. 
���������� � ��� �������� ������ �� ��������� ���� �������� �������.
*/