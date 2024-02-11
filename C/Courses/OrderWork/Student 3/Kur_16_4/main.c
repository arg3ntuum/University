#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#define	N 50
#define TIRE  puts("---------------------------------------------------------------------------------------------------------")
#define TABLE puts("|  #  |    ������    |     ���  �������     |  ���� ������  | �������� �������� | ������� ������������� |")
typedef struct {
	char group[N];
	int day;
	int view;
	char name_subject[N];
	char surname[N];
} NP;
void checkFiles(char file[]) {
	FILE* data;
	fopen_s(&data, file, "rb+");
	if (!data) {
		printf("���� %s �� ��� ������!\n", file);
		exit(0);
	}
	else {
		printf("���� %s ��� ��������! ������ ���������� � ������!\n", file);
		fclose(data);
	}
}
void saveTo(char a[], char b[]) {
	for (int i = 0; i < N; i++)
		a[i] = b[i];
}
int check(char file[]) {
	int i;
	NP np;
	FILE* data;
	fopen_s(&data, file, "r");//������
	if (!data) {
		puts("���� �� ��� ������.\n");
		exit(1);
	}
	for (i = 0;; i++) {
		fscanf_s(data, "%s ", np.group, N);
		fscanf_s(data, "%d ", &np.day);
		fscanf_s(data, "%d ", &np.view);
		fscanf_s(data, "%s ", np.name_subject, N);
		fscanf_s(data, "%s ", np.surname, N);
		if (np.day == 0 && np.view == 0)
			break;
	}
	fclose(data);
	return i;
}
NP initNP(FILE* data) {
	NP np;
	fscanf_s(data, "%s ", np.group, N);
	fscanf_s(data, "%d ", &np.day);
	fscanf_s(data, "%d ", &np.view);
	fscanf_s(data, "%s ", np.name_subject, N);
	fscanf_s(data, "%s ", np.surname, N);
	return np;
}
NP* initArr(int dimension, char dataName[]) {
	NP* massive = (NP*)malloc(dimension * sizeof(NP));
	if (massive == NULL)
		return NULL;
	int vubor = 0;
	FILE* data;
	fopen_s(&data, dataName, "r");
	if (!data) {
		puts("���� �� ��� ������.\n");
		exit(1);
	}
	for (int i = 0; i < dimension; i++)
		massive[i] = initNP(data);
	fclose(data);
	return massive;
}
void displayNP(NP np, int i) {
	printf("|%3d. | %12s | ", i + 1, np.group);
	switch (np.view) {
	case 1: printf(" ���������� ������� "); break;
	case 2: printf("������������ �������"); break;
	case 3: printf("������������ �������"); break;
	}
	printf(" | ");
	switch (np.day) {
	case 1: printf(" ����������� "); break;
	case 2: printf("   �������   "); break;
	case 3: printf("    �����    "); break;
	case 4: printf("   �������   "); break;
	case 5: printf("   �������   "); break;
	case 6: printf("   �������   "); break;
	case 7: printf(" ����������� "); break;
	}
	printf(" | %17s | %21s |\n", np.name_subject, np.surname);
	TIRE;
}
void displayAll(NP* massive, int dimension) {
	TIRE;
	TABLE;
	TIRE;
	for (int i = 0; i < dimension; i++)
		displayNP(massive[i], i);
}
int chooseSize(int dimension) {
	int size = 0;
	do {
		printf("��� ��������� ������� ��������� ������� �� ����� ��������: ");
		scanf_s("%d", &size);
		if (size > dimension)
			printf("������ �� ����� ���� ���� ��� ����� '%d'!\n", dimension);
		else if (size <= 0)
			puts("������ �� ����� ���� ������ ���� ��� ����� ����!", dimension);
	} while (!(size > 0 && size <= dimension));
	return size;
}
void saveNP(NP NP, FILE* data) {
	fprintf(data, "%s ", NP.group);
	fprintf(data, "%d ", NP.day);
	fprintf(data, "%d ", NP.view);
	fprintf(data, "%s ", NP.name_subject);
	fprintf(data, "%s ", NP.surname);
}
void saveArr(NP* massive, int dimension, char fileName[]) {
	FILE* data;
	fopen_s(&data, fileName, "w");
	if (!data) {
		puts("���� �� ��� ������.\n");
		exit(1);
	}
	for (int i = 0; i < dimension; i++)
		saveNP(massive[i], data);
	fprintf(data, "- 0 0 - -\n");
	fclose(data);
}
void noPractise(NP* massive, int dimension) {
	int checkToWrite = 0, first = 0, check = 0;

	for (int i = 0, nomer = 1; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (strcmp(massive[i].surname, massive[j].surname) == 0 && (massive[i].view == 2 || massive[j].view == 2)) {
					checkToWrite = 1;
			}
				
		}
		if (checkToWrite != 1) {
			if (first == 0) {
				puts("������� ��������������, ��� �� �������� ��������:");
				first = 1;
			}
			printf("%d. %s;\n", nomer++, massive[i].surname);

		}
		checkToWrite = 0;
	}
	if (first == 0)
		puts("��� ������������� �������� ��������.");
}
void swap(NP *a, NP *b) {
	NP temp = *a;
	*a = *b;
	*b = temp;
}
void quicksort(NP* massive, int length) {
	int i, piv = 0;
	if (length <= 1)
		return;

	for (i = 0; i < length; i++) {
		if (strcmp(massive[i].surname, massive[length - 1].surname) < 0)
			swap(&massive[i], &massive[piv++]);
	}

	swap(&massive[piv], &massive[length - 1]);

	quicksort(massive, piv++);
	quicksort(massive + piv, length - piv);
}
void lineFound(NP* massive, int dimension, char groupFind[]) {
	int first = 0;
	for (int i = 0, nomer = 0; i < dimension; i++) {
		if (strstr(massive[i].group, groupFind)) {
			if (first == 0) {
				TIRE;
				TABLE;
				TIRE;
				first = 1;
			}
			displayNP(massive[i], nomer++);
		}
	}
}
void BinareWhileUp(NP* massive, int dimension, char groupFind[], int center, int nomer) {
	for (int i = center; i < dimension; i++)
		if (strstr(massive[i].group, groupFind)) {
			if (nomer == 0) {
				TIRE;
				TABLE;
				TIRE;
			}
			displayNP(massive[i], nomer++);
		}
}
void BinareWhileDown(NP* massive, int dimension, char groupFind[], int center, int nomer) {
	for (int i = center; i >= 0; i--)
		if (strstr(massive[i].group, groupFind)) {
			if (nomer == 0) {
				TIRE;
				TABLE;
				TIRE;
			}
			displayNP(massive[i], nomer++);
		}
}
void sortGroup(NP* massive, int dimension) {
	NP temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].group, massive[j - 1].group) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void Binare(NP* massive, int dimension, char groupFind[]) {
	int center = round(dimension / 2);
	static nomer = 0;
	sortGroup(massive, dimension);
	if (strcmp(massive[center].group, groupFind) < 0)
		BinareWhileUp(massive, dimension, groupFind, center, nomer);
	else if (strcmp(massive[center].group, groupFind) > 0)
		BinareWhileDown(massive, dimension, groupFind, center, nomer);
	else if (strcmp(massive[center].group, groupFind) == 0) {
		if (dimension == 1) {
			TIRE;
			TABLE;
			TIRE;
			displayNP(massive[0], nomer++);
		}
		else if (dimension == 2) {
			nomer++;
			lineFound(massive, dimension, groupFind);
		}
		else if (dimension >= 3) {
			if (strcmp(massive[center].group, groupFind) == 0 && strcmp(massive[center - 1].group, groupFind) != 0 && strcmp(massive[center].group, groupFind) != 0) {
				TIRE;
				TABLE;
				TIRE;
				displayNP(massive[0], nomer++);
			}
			else if (strcmp(massive[center].group, groupFind) == 0 && strcmp(massive[center - 1].group, groupFind) == 0 && strcmp(massive[center + 1].group, groupFind) != 0)
				BinareWhileDown(massive, dimension, groupFind, center, nomer);
			else if (strcmp(massive[center].group, groupFind) == 0 && strcmp(massive[center - 1].group, groupFind) != 0 && strcmp(massive[center + 1].group, groupFind) == 0)
				BinareWhileUp(massive, dimension, groupFind, center, nomer);
			else if (strcmp(massive[center].group, groupFind) == 0 && strcmp(massive[center - 1].group, groupFind) == 0 && strcmp(massive[center + 1].group, groupFind) == 0) {
				nomer++;
				lineFound(massive, dimension, groupFind);
			}
		}
	}
}
int checkGroup(char groupFind[], NP* massive, int dimension) {
	int checking = 1;
	for (int i = 0; i < dimension; i++)
		if (strcmp(massive[i].group, groupFind) == 0)
			checking = 0;
	return checking;
}
int choiseGroup(char groupFind[], NP* massive, int dimension) {
	char group[N] = { 0 };
	printf("������� ������ ��� ������: ");
	scanf_s("%s", group, N - 1);
	saveTo(groupFind, group);
	return checkGroup(group, massive, dimension);
}
void choise(NP* massive, int dimension) {
	char group[N] = { 0 };
	int choose = 0, checking = choiseGroup(group, massive, dimension);
	do {
		printf("�������� ������ ������ �� ������:\n1.�������� �����;\n2.�������� �����;\n0.�����;\n��� �����: ");
		scanf_s("%d", &choose);
		if (choose == 1 && checking == 0)
			lineFound(massive, dimension, group);
		else if (choose == 2 && checking == 0)
			Binare(massive, dimension, group);
		else if (checking != 0)
			puts("������ �� �������!");
	} while (choose != 0);
}
void main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	char dataName[N] = {0};
	if (argc == 2) {
		printf("���� �������� ����� ��������!\n");
		saveTo(dataName, argv[1]);
		checkFiles(dataName);
	}
	else {
		printf("����� ���������� ���� ������, ������� ��� ��������(��������, data.txt): ");
		scanf_s("%s", dataName, N - 1);
		checkFiles(dataName);
	}
	int dimension = check(dataName), choose = 0;
	NP* massiveStruct = initArr(dimension, dataName);
	do {
		puts("\t� � � �\
		 \n1.������ ���� �������;\
		 \n2.�������� ������ ������� ��������;\
		 \n3.���������� �� ������� (Quick Sort);\
		 \n4.����� �� ������;\
		 \n5.������ ������� ��������������, ��� �� �������� ��������;\
		 \n0.�����;\
		 \n��� �����: ");
		scanf_s("%d", &choose);
		if (choose == 1)
			displayAll(massiveStruct, dimension);
		else if (choose == 2) {
			dimension = chooseSize(check(dataName));
			massiveStruct = initArr(dimension, dataName);
		}
		else if (choose == 3)
			quicksort(massiveStruct, dimension);
		else if (choose == 4)
			choise(massiveStruct, dimension);
		else if (choose == 5)
			noPractise(massiveStruct, dimension);
	} while (choose != 0);
	saveArr(massiveStruct, dimension, dataName);
	free(massiveStruct);
}
/*
		+1.	��� ����� �������� � ���������� �����. ���� ���� ��� �� ���� ������, �� ���� ���������� ������ ��������� ������������.
		+2.	��������������� �������� �������� ����� (����� ������ �������� ������������ ���� ���������� ������). 
		+ϳ��� ������������ ������ ��� ���������� �������� ������.
		3.	����� ���������� ���������� ����� �������� � ������ �� �������.
		+4.	������� ���������� �������� � ������ ������� � ���������� �� �����.
		5.	���������� ��� ������ ��� ������� � ���������.

		+16.	� ���������� ��� ���������� ������: 
		+����� ����� (���������, ʲ-19-1), 
		+���� �����,
		+��� ������� (������, �������� �� ���������� ������), 
		+����� ����-����, 
		+������� ���������. 
		+������ ������� ����������, �� �� ��������� ����-������ ������. 
		+������������ ���������� �� �������� ��������� ������� �������� ���������� (Quick Sort). 
		+����������� ����� �� ������� �����.
*/