#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#define K 50
//�������� ����� � ������� � �������
int randomRange(int min, int max) {
	return rand() % (max - min + 1) + min;
}

//������� �������� ������������ �������� �������
void userInput(int** A, int N) {
	char temp[K];
	int error = 0;
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
		{
			do {
				error = 0;
				printf("Massive[%d][%d]: ", i, j);
				scanf_s("%s", &temp, K - 1);
				for (int a = 0; a < strlen(temp); a++)
					if (atoi(temp) == 0 || !('0' <= temp[a] && temp[a] <= '9'  ))
						error = 1;
				if (error == 1)
					printf("�� ����� �� ������������� ��������!\n");
				else {
					A[i][j] = atoi(temp);
					break;
				}
			} while (1);
		}
}

//������� ���������� ���������� �������
void autoInput(int** A, int N) {
	srand(time(NULL));
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
			A[i][j] = randomRange(-10, 10); //����� ������ � ������� � ������� �� (-10; 10)
}

//������� ������ �������
void outPut(int** A, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%5d", A[i][j]);
		printf("\n");
	}
}

//������� ������� �������
void processing(int** A, int N) {
	for (int temp, i = 0, k = N - 1; i != round(N / 2); i++, k--)
		for (int j = 0; j < N; j++) {
			temp = A[j][i];
			A[j][i] = A[j][k];
			A[j][k] = temp;
		}
}

//���� ������ ��������
int �hooseMode() {
	int choose = 0;
	do {
		printf("�����i�� ����� �������� �������: \
			  \n1.�������� ������������;\
		      \n2.����������� ��������;\
			  \n��� ���i�: ");
		scanf_s("%d", &choose);
	} while (choose != 1 && choose != 2);
	return choose;
}

//��������� ������
int dimension() {
	int N = 0;
	do {
		printf("����i�� ����i� ������ N x N(6 <= N <= 10): ");
		scanf_s("%d", &N);
	} while (!(6 <= N && N <= 10));
	return N;
}

//������� �������
void main() {
	setlocale(LC_ALL, "Rus"); //����������

	int N = dimension();
	system("cls"); // �������� ������
	int choose = �hooseMode();
	
	//��������� ���������� ������
	int** A = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		A[i] = (int*)malloc(N * sizeof(int));
	
	if (choose == 1)
		userInput(A, N); //�������� ������� ������������
	else autoInput(A, N); //����������� ���������� �������

	system("cls"); // �������� ������
	printf("\t����� ��:\n");
	outPut(A, N); //����� ������

	processing(A, N);//������� ������

	printf("\n\t����� �I���:\n"); 
	outPut(A, N); //����� ������

	free(A); //�������� ���'��
}
/*
��� �������� 2-�� �������� ���������:
1.	����������� ������� ��� ������� �������� �������� ������.
2.	����������� ������� ��� ������������� ���������� ������ � ������ ����� ������������ ���������� ���������� �����.
3.	����������� ������� ������� �� ��� �������� ����� �� ������� �������.

18.	������� ������ ������� �������, �� �������� �� ���. �.2 (�).
*/