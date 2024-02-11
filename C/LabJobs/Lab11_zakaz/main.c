#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#define RAVNO puts("=========================================")
#define F 50
#define Y 10
/*

�������� 1. ������ ��������� ������� � ��������� M*N.
� ����������� ����� � �������� �������� ������� �, �� � ���������� � ������.

�������� 2. ���� ������ ����-���� ������. ���������� �� �
���������� �������. �������� ������ ��� ���������� �����
�����, � �������������� ���� ����� ���������.

�������� 3. �������� ��������, ��� �������, �� �����������
�������� ����� Q � �������� ����� S (�� �������, � ������� ��
���������). ����� S �� Q ��� ������� ����� ��������� �����.
*/
//��������� ����� � ���������
int quest1_getRandNum(int min, int max) {
	return rand() % (max - min + 1) + min;
}
int quest1_processing(int* massive, int N){
	int min = 0;
	for (int i = 0; i < N; i++){
		if (i == 0)
			min = *(massive +i );
		else if (min > *(massive + i))
			min = *(massive + i);
	}
	return min;
}
void quest1_userInput(int** massive, int M, int N) {
	char temp[F] = { 0 };
	puts("������� ����� �����--->");
	for (int i = 0; i < M; i++)  //  ���� �� ������
		for (int j = 0; j < N; j++)  // ���� �� ��������
		{
			printf("Massive[%d][%d] = ", i, j);
			scanf_s("%s", &temp, F - 1);
			*(*(massive + i) + j) = atoi(temp);
		}
}
void quest1_autoInput(int** massive, int M, int N) {
	for (int i = 0; i < M; i++)  // ���� �� �������
		for (int j = 0; j < N; j++)  // ���� �� ��������
			*(*(massive +i )+j) = quest1_getRandNum(-10, 10); //���������� ������� ������� ��������� ������ � ��������� (-10; 10)
}
void quest1() {
	int N = 0, M = 0, choose = 0;
	RAVNO;
	srand(time(NULL));
	printf("\n������� ����������� ���������� ������� M x N(������������ ������������� ������):");
	printf("\n������� M: ");
	scanf_s("%d", &M);
	printf("\n������� N: ");
	scanf_s("%d", &N);

	//ĳ������ �������� ���'��
	int* massiveMIN = (int*)malloc(M * sizeof(int));
	int** massive = (int**)malloc(M* sizeof(int*));
	if (massive == NULL) {
		printf("\n�� ������������������ ������");
		return 0;
	}
	for (int i = 0; i < M; i++)
		*(massive +i) = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < M; i++)
		if (*(massive + i) == NULL) {
			printf("\n�� ������������������ ������ � ����� �� ���������");
			return 0;
		}
	do {
		printf("\n�������� ����� ������ ���������:\n1.���� �� ������������.\n2.�������������� ��������.\n��� �����: ");
		scanf_s("%d", &choose);
	} while (choose != 1 && choose != 2);
	if (choose == 1)
		quest1_userInput(massive, M, N);
	else if (choose == 2)
		quest1_autoInput(massive, M, N);
	//�������
	for (int i = 0; i < M;i++) {
		*(massiveMIN + i) = quest1_processing(massive[i], N);
	}
	puts("");
	for (int i = 0; i < M; i++) {  // ���� �� �������
		for (int j = 0; j < N; j++)  // ���� �� ��������
			printf("%4d", *( *(massive + i) + j));
		printf("\n");
	}
	//����� ������
	for (int i = 0; i < M; i++) {
		printf("\n����������� �������� � ������ %d = %d", i, *(massiveMIN + i));
	}
	puts("");
}
void quest2() {
	int choose = 0;
	char surname[Y][F] =
	{
		{"Ivanov"},
		{"Smirnov"},
		{"Kuznecov"},
		{"Popov"},
		{"Vasilev"},
		{"Petrov"},
		{"Cokolov"},
		{"Mihaylov"},
		{"Zaycev"},
		{"Bogdanov"}
	};
	do {
		printf("\n�������� ����� ������ ���������:\n1.���� �� ������������.\n2.�������������� ��������.\n��� �����: ");
		scanf_s("%d", &choose);
	} while (choose != 1 && choose != 2);
	if (choose == 1)
	{
		puts("������� �������--->");
		for (int i = 0; i < Y; i++) { //  ���� �� ������
			printf("�������[%d] = ", i);
			scanf_s("%s", &*(surname +i), F - 1);
		}
	}
	puts("������ �������:");
	for (int i = 0; i < Y; i++)
		printf("\n�������[%d] = %s;",i, *(surname + i));
	puts("");
	void* temp;
	char* ptrSurname[Y] = { 
		*surname,
		* (surname + 1),
		* (surname + 2),
		* (surname + 3),
		* (surname + 4),
		* (surname + 5),
		* (surname + 6),
		* (surname + 7),
		* (surname + 8),
		* (surname + 9),
	};
	
	//Sort
	for (int i = 0; i <= Y; i++)
		for (int j = Y - 1; j > i; j--)
			if (strcmp(*(ptrSurname+j), *(ptrSurname + j - 1)) < 0) {
				temp = *(ptrSurname + j);
				*(ptrSurname + j) = *(ptrSurname + j - 1);
				*(ptrSurname + j - 1) = temp;
			}
	printf("\n\n��������������� ������:");
	for (int i = 0; i < Y; i++)
		printf("\n�������[%d] = %s;", i, *( ptrSurname+i));
	puts("");
}
void quest3()
{
	RAVNO;
	char str1[F] = { 0 }, str2[F] = { 0 };
	int n = 0;

	printf("\n������� ������ ��������:");
	getchar();
	gets(str1, F);

	printf("\n������� ������� ������:");
	gets(str2, F);

	for (char* ptr = strstr(str1, str2); ptr != 0; ptr = strstr(ptr + 1, str2))
		n = ptr - str1 + 1;
	printf("n = %d", n);
	if (n == 0)
		printf("��������� ������.\n");
	else if (n == 1)
		printf("� ������ ������ ������� ��������� � ������� %d.\n", n);
	else if (str1[n + strlen(str2)] == '\0')
		printf("� ����� ������ ������� ��������� � ������� %d.\n", n);
	else printf("� �������� ������ ������� ��������� � ������� %d.\n", n);
	
}
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	//C:\Users\tftfj\source\repos\Lab11_zakaz\Debug\Lab11_zakaz.exe z2
	int choose = 0;
	do {
		RAVNO;
		printf("������� ����� �������, ������� ������ ���������:(1, 2, ��� 3).\n������� 0 ��� ����������.\n");
		scanf_s("%d", &choose);
		if (choose == 0)
			break;
		else if (choose == 1)
			quest1();
		else if (choose == 2)
			quest2();
		else if (choose == 3)
			quest3();
	} while (1);
	/*for (int i = 1;i < argc;i++)
		for (int j = 0; j <	F; j++)
		{
			if (argv[i][j] == 'z' && argv[i][j + 1] == '1')
				choose = 1;
			else if (argv[i][j] == 'z' && argv[i][j + 1] == '2')
				choose = 2;
			else if (argv[i][j] == 'z' && argv[i][j + 1] == '3')
				choose = 3;
		}
	if (choose == 1)
		quest1();
	else if (choose == 2)
		quest2();
	else if (choose == 3)
		quest3();*/
	
	RAVNO;
	puts("��������� ������.");
	RAVNO;
	return 0;
}