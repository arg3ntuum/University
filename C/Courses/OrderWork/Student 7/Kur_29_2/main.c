#include <stdio.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#define K 50

//������ ������ � ����������
void userWriting(int** massive, int N) {
	char temp[K];
	int check = 0;
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
		{
			do {
				check = 0;
				printf("Massive[%d][%d] = ", i, j);
				scanf_s("%s", &temp, K - 1);
				for (int a = 0; a < strlen(temp); a++)
					if (atoi(temp) == 0 && !(('0' <= temp[a]) && (temp[a] <= '9')))
						check = 1;
				if (check == 1)
					printf("�� � ������!\n");
				else {
					massive[i][j] = atoi(temp);
					break;
				}
			} while (1);
		}
}

//������ ������ � ������� ����������
void machineWriting(int** massive, int N) {
	srand(time(NULL));
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
			massive[i][j] = rand() % 21 - 10;
}

//����� �����
int sum(int** massive, int N) {
	int massive_leader_diagonal = 0, summa = 0;
	for (int i = 0; i < N; i++) {
		massive_leader_diagonal = i;//����� ���������� �������� � ������� ���������
		for (int j = 0; j < N; j++)
			if (i % 2 == 1 && j > i)
				summa += massive[i][j];
	}
	return summa;
}

//�����
void massiveView(int** massive, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%5d", massive[i][j]);
		puts("");
	}
}

//������� ����� ��������
int choiseWriting() {
	int choise = 0;
	do {
		printf("�������� ����� ���������� ������� �������: \
			  \n1.����������������;\
		      \n2.��������������;\
			  \n��� �����: ");
		scanf_s("%d", &choise);
	} while (choise != 1 && choise != 2);//������� ������ ���� true, ����� ���� ��������. ���� ������������ ���� ���������� ������, �� �������������� ���� � ����������� �� �������
	return choise;
}

//����� ������� �������
int size() {
	int N = 0;
	do {
		printf("�������� ������ ������� N x N(6 <= N <= 10): ");
		scanf_s("%d", &N);
	} while (!(6 <= N && N <= 10));//������� ������ ���� true, ����� ���� ��������. ���� ������������ ���� ���������� ������, �� �������������� ���� � ����������� �� �������
	return N;
}

void main() {
	setlocale(LC_ALL, "Rus"); //�����������
	int N = size(), choose =  choiseWriting();

	//�������� ������������ ������
	int** massive = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		massive[i] = (int*)malloc(N * sizeof(int));
	
	if (choose == 1)
		userWriting(massive, N); //������������ ��������� �������
	else machineWriting(massive, N); //��������� ��������� �������

	printf("\t�����:\n");
	massiveView(massive, N); //����� �������

	printf("\n\nC��� �������i�, �� ������ ��� �������� �i�������� � ������, �� ����������� � ������� ����� ���i����: %d\n\n", sum(massive, N));

	free(massive); //�������� ������
}
/*
��� �������� 2-�� �������� ���������:
1.	����������� ������� ��� ������� �������� �������� ������.
2.	����������� ������� ��� ������������� ���������� ������ � ������ ����� ������������ ���������� ���������� �����.
3.	����������� ������� ������� �� ��� �������� ����� �� ������� �������.
29.	������ ���� ��������, �� ������ ��� �������� ��������� � ������, �� ����������� � ������� �����.
*/