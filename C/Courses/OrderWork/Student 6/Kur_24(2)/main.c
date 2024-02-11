#include <stdio.h>
#include <locale.h>
#include <time.h>
#define K 50

//�������� ������������ �������� �������
void user_in_put(int** massive, int N) {
	char temp[K];
	int pomilka = 0;
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
		{
			do {
				pomilka = 0;
				printf("Massive[%d][%d]: ", i, j);
				scanf_s("%s", &temp, K - 1);
				for (int a = 0; a < strlen(temp); a++)
					if (atoi(temp) == 0 && !(('0' <= temp[a]) && (temp[a] <= '9')))
						pomilka = 1;
				if (pomilka == 1)
					printf("�� �� �����!\n");
				else {
					massive[i][j] = atoi(temp);
					break;
				}
			} while (1);
		}
}

//�������� ���������� �������
void auto_in_put(int** massive, int N) {
	srand(time(NULL));
	for (int i = 0; i < N; i++)  
		for (int j = 0; j < N; j++) 
			massive[i][j] = rand() % 21 - 10;
}

//���� �������
void out_matrix(int** massive, int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			printf("%4d", massive[i][j]);
		printf("\n");
	}
}

void out_vektor(int* massive, int N) {
	for (int i = 0; i < N; i++) {
		printf("������ %d = %3d", i, massive[i]);
		printf("\n");
	}
}

//������� ����� ��������
int �hoose_rezum_vvedennya() {
	int choose = 0;
	do {
		printf("�����i�� ����� ������ ������i: \
			  \n1.������������;\
		      \n2.����'������;\
			  \n��� ���i�: ");
		scanf_s("%d", &choose);
	} while (choose != 1 && choose != 2);
	return choose;
}

//��������� ������
int size() {
	int N = 0;
	do {
		printf("�����i�� ����i� ������ N x N(6 <= N <= 10): ");
		scanf_s("%d", &N);
	} while (!(6 <= N && N <= 10));
	return N;
}

//������� �������
void main() {
	setlocale(LC_ALL, "Rus"); //����������
	int N = 0, choose = 0;

	N = size();

	system("cls"); // �������� ������
	
	choose = �hoose_rezum_vvedennya();
	
	//��������� ���������� ������
	int** massive = (int**)malloc(N * sizeof(int*));
	for (int i = 0; i < N; i++)
		massive[i] = (int*)malloc(N * sizeof(int));
	
	int* vektor = (int*)malloc(N * sizeof(int));
	if (choose == 1)
		user_in_put(massive, N); //�������� ������� ������������
	else auto_in_put(massive, N); //����������� ���������� �������

	system("cls"); // �������� ������
	printf("\t�����:\n");
	out_matrix(massive, N); //����� ������

	int min, max;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (j == 0) {
				min = massive[i][0];
				max = massive[i][0];
			}
			else if (min > massive[i][j])
				min = massive[i][j];
			else if (max < massive[i][j])
				max = massive[i][j];
		}
		vektor[i] = max - min;
	}

	printf("\t������:\n");
	out_vektor(vektor, N);

	free(massive); //�������� ���'��
}
/*
��� �������� 2-�� �������� ���������:
1.	����������� ������� ��� ������� �������� �������� ������.
2.	����������� ������� ��� ������������� ���������� ������ � ������ ����� ������������ ���������� ���������� �����.
3.	����������� ������� ������� �� ��� �������� ����� �� ������� �������.

24.	���������� ������ � ������ ��������� �� ��������� ������� �������� �����.
*/