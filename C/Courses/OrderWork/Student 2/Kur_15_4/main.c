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
} NavchProcc;
void checkFiles(char file[]) {
	FILE* data;
	fopen_s(&data, file, "rb+");
	if (!data) {
		printf("���� %s �� ������!\n", file);
		exit(0);
	}
	else {
		printf("���� %s ���������!\n", file);
		fclose(data);
	}
}
void saveTo(char a[], char b[]) {
	for (int i = 0; i < N; i++)
		a[i] = b[i];
}
int check(char file[]) {
	int i;
	NavchProcc np;
	FILE* data;
	fopen_s(&data, file, "r");//������
	if (!data) {
		puts("���� �� ��������.\n");
		exit(1);
	}
	for (i = 0;; i++) {
		fscanf_s(data, "%s ", np.group, N);
		fscanf_s(data, "%d ", &np.day);
		fscanf_s(data, "%d ", &np.view);
		fscanf_s(data, "%s ", np.name_subject, N);
		fscanf_s(data, "%s ", np.surname, N);
		if ( np.day == 0 && np.view == 0)
			break;
	}
	fclose(data);
	return i;
}
NavchProcc initNP(FILE* data) {
	NavchProcc np;
	fscanf_s(data, "%s ", np.group, N);
	fscanf_s(data, "%d ", &np.day);
	fscanf_s(data, "%d ", &np.view);
	fscanf_s(data, "%s ", np.name_subject, N);
	fscanf_s(data, "%s ", np.surname, N);
	return np;
}
NavchProcc* initArr(int dimension, char dataName[]) {
	NavchProcc* massive = (NavchProcc*)malloc(dimension * sizeof(NavchProcc));//������� ����� �������
	if (massive == NULL)
		return NULL;
	int vubor = 0;
	FILE* data;
	fopen_s(&data, dataName, "r");
	if (!data) {
		puts("���� �� ��i� �i��������.\n");
		exit(1);
	}
	for (int i = 0; i < dimension; i++)
		massive[i] = initNP(data);
	fclose(data);
	return massive;
}
void displayNP(NavchProcc np, int i) {
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
void displayAll(NavchProcc* massive, int dimension) {
	TIRE;
	TABLE;
	TIRE;
	for (int i = 0; i < dimension; i++)
		displayNP(massive[i], i);
}
int chooseSize(int dimension) {
	int size = 0;
	do {
		printf("�������� ������ ��� ��������: ");
		scanf_s("%d", &size);
		if (size > dimension)
			printf("������ �� ����� ���� ��������� ����� '%d'!\n", dimension);
		else if (size <= 0)
			puts("������ �� ����� ���� ������ ��� ����� ����!", dimension);
	} while (!(size > 0 && size <= dimension));
	return size;
}
void saveNP(NavchProcc NP, FILE* data) {
	fprintf(data, "%s ", NP.group);
	fprintf(data, "%d ", NP.day);
	fprintf(data, "%d ", NP.view);
	fprintf(data, "%s ", NP.name_subject);
	fprintf(data, "%s ", NP.surname);
}
void saveArr(NavchProcc* massive, int dimension, char fileName[]) {
	FILE* data;
	fopen_s(&data, fileName, "w");
	if (!data) {
		puts("Failed to open file \n");
		exit(1);
	}
	for (int i = 0; i < dimension; i++)
		saveNP(massive[i], data);
	fprintf(data, "- 0 0 0 0 0 0 - - -\n");
	fclose(data);
}
void shellSort(NavchProcc* massive, int dimension) {
	for (int interval = dimension / 2; interval > 0; interval /= 2) {
		for (int i = interval, j; i < dimension; i += 1) {
			NavchProcc temp = massive[i];
			for (j = i; j >= interval && strcmp(massive[j - interval].group, temp.group) > 0 ; j -= interval) {
				massive[j] = massive[j - interval];
			}
			massive[j] = temp;
		}
	}
}
void sortGroup(NavchProcc* massive, int dimension) {
	NavchProcc temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].group, massive[j - 1].group) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
int checkPrizvishe(char prizvisheFind[], NavchProcc* massive, int dimension) {
	int checking = 1;
	for (int i = 0; i < dimension; i++)
		if (strcmp(massive[i].surname, prizvisheFind) == 0)
			checking = 0;
	return checking;
}
int choisePrizvishe(char prizvisheFind[], NavchProcc* massive, int dimension) {
	char prizvishe[N] = {0};
	printf("������� ������� �������������: ");
	scanf_s("%s", prizvishe, N - 1);
	saveTo(prizvisheFind, prizvishe);
	return checkPrizvishe(prizvishe, massive, dimension);
}
void lineFound(NavchProcc* massive, int dimension, char prizvisheFind[]) {
	int first = 0;
	for (int i = 0, nomer = 0; i < dimension; i++) {
		if (strstr(massive[i].surname, prizvisheFind)) {
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
void BinareWhileUp(NavchProcc* massive, int dimension, char prizvisheFind[], int center, int nomer) {
	for (int i = center; i < dimension; i++)
		if (strstr(massive[i].surname, prizvisheFind)) {
			if (nomer == 0) {
				TIRE;
				TABLE;
				TIRE;
			}
			displayNP(massive[i], nomer++);
		}
}
void BinareWhileDown(NavchProcc* massive, int dimension, char prizvisheFind[], int center, int nomer) {
	for (int i = center; i >= 0; i--)
		if (strstr(massive[i].surname, prizvisheFind)) {
			if (nomer == 0) {
				TIRE;
				TABLE;
				TIRE;
			}
			displayNP(massive[i], nomer++);
		}
}
void Binare(NavchProcc* massive, int dimension, char prizvisheFind[]) {
	int center = round(dimension / 2);
	static nomer = 0;
	sortGroup(massive, dimension);
	if (strcmp(massive[center].surname, prizvisheFind) < 0)
		BinareWhileUp(massive, dimension, prizvisheFind, center, nomer);
	else if (strcmp(massive[center].surname, prizvisheFind) > 0)
		BinareWhileDown(massive, dimension, prizvisheFind, center, nomer);
	else if (strcmp(massive[center].surname, prizvisheFind) == 0) {
		if (dimension == 1) {
			TIRE;
			TABLE;
			TIRE;
			displayNP(massive[0], nomer++);
		}
		else if (dimension == 2) {
			nomer++;
			lineFound(massive, dimension, prizvisheFind);
		}
		else if (dimension >= 3) {
			if (strcmp(massive[center].surname, prizvisheFind) == 0 && strcmp(massive[center - 1].surname, prizvisheFind) != 0 && strcmp(massive[center].surname, prizvisheFind) != 0) {
				TIRE;
				TABLE;
				TIRE;
				displayNP(massive[0], nomer++);
			}
			else if (strcmp(massive[center].surname, prizvisheFind) == 0 && strcmp(massive[center - 1].surname, prizvisheFind) == 0 && strcmp(massive[center + 1].surname, prizvisheFind) != 0)
				BinareWhileDown(massive, dimension, prizvisheFind, center, nomer);
			else if (strcmp(massive[center].surname, prizvisheFind) == 0 && strcmp(massive[center - 1].surname, prizvisheFind) != 0 && strcmp(massive[center + 1].surname, prizvisheFind) == 0)
				BinareWhileUp(massive, dimension, prizvisheFind, center, nomer);
			else if (strcmp(massive[center].surname, prizvisheFind) == 0 && strcmp(massive[center - 1].surname, prizvisheFind) == 0 && strcmp(massive[center + 1].surname, prizvisheFind) == 0) {
				nomer++;
				lineFound(massive, dimension, prizvisheFind);
			}
		}
	}
}
void choise(NavchProcc* massive, int dimension) {
	char prizvisheFind[N] = {0};
	int choose = 0, checking = choisePrizvishe(prizvisheFind, massive, dimension);
	do {
		printf("�������� ������ ������ �� ������� �������������:\n1.��������;\n2.��������;\n0.�����;\n��� �����: ");
		scanf_s("%d", &choose);
		if (choose == 1 && checking == 0)
			lineFound(massive, dimension, prizvisheFind);
		else if (choose == 2 && checking == 0)
			Binare(massive, dimension, prizvisheFind);
		else if (checking != 0)
			puts("������ �� �������!");
	} while (choose != 0);
}
void takeNoLection(NavchProcc* massive, int dimension) {
	int checkToWrite = 0, first = 0;
	char** charWrited = (char**)malloc(dimension * sizeof(char*));
	for (int i = 0; i < N; i++)
		charWrited[i] = (char*)malloc(N * sizeof(char));
	if (charWrited == NULL)
		return NULL;
	
	for (int i = 0, nomer = 1; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			if (strcmp(massive[i].surname, massive[j].surname) == 0 && (massive[i].view == 1 || massive[j].view == 1))
				checkToWrite = 1;
		}
		if (checkToWrite != 1) {
			if (first == 0) {
				puts("������� ��������������, ��� �� ������ ������:");
				first = 1;
			}
			printf("%d. %s;\n", nomer, massive[i].surname);
		}		
		checkToWrite = 0;	
	}
	if (first == 0)
		puts("��� ������������� ������ ������.");
}
void main(int argc, char* argv[]) {
	setlocale(LC_ALL, "");
	char dataName[N] = "data.txt";
	if (argc == 2) {
		printf("���� ���� �������� ����� ��������!\n");
		saveTo(dataName, argv[1]);
		checkFiles(dataName);
	}
	else {
		printf("��� �i������� ����, ����� ������ ���� ����� ���i: ");
		scanf_s("%s", dataName, N - 1);
		checkFiles(dataName);
	}
	int dimension = check(dataName), choose = 0;
	NavchProcc* massiveStruct = initArr(dimension, dataName);
	do {
		puts("\t� � � �\
		 \n1.������ �������;\
		 \n2.�������� ������ ��������;\
		 \n3.���������� �� �������� �����;\
		 \n4.����� �������;\
		 \n5.������ ������� ��������������, ��� �� ������ ������;\
		 \n0.Exit;\
		 \n��� ���i�: ");
		scanf_s("%d", &choose);
		if (choose == 1)
			displayAll(massiveStruct, dimension);
		else if (choose == 2) {
			dimension = chooseSize(check(dataName));
			massiveStruct = initArr(dimension, dataName);
		}
		else if (choose == 3)
			shellSort(massiveStruct, dimension);
		else if (choose == 4)
			choise(massiveStruct, dimension);
		else if (choose == 5)
			takeNoLection(massiveStruct, dimension);
	} while (choose != 0);
	saveArr(massiveStruct, dimension, dataName);
	free(massiveStruct); 
}
/*
			1.	��� ����� �������� � ���������� �����. ���� ���� ��� �� ���� ������, �� ���� ���������� ������ ��������� ������������.
			2.	��������������� �������� �������� ����� (����� ������ �������� ������������ ���� ���������� ������). 
			ϳ��� ������������ ������ ��� ���������� �������� ������.
			3.	����� ���������� ���������� ����� �������� � ������ �� �������.
			4.	������� ���������� �������� � ������ ������� � ���������� �� �����.
			5.	���������� ��� ������ ��� ������� � ���������.


			15.	� ���������� ��� ���������� ������: 
			����� ����� (���������, ʲ-19-1), 
			���� �����,
			��� ������� (������, �������� �� ���������� ������), 
			����� ����-����, 
			������� ���������. 
			������ ������� ����������, �� �� ������� ������. 
			������������ ���������� ��� ���������� ������ �� �������� ���� ������� ����� (Shell sort).
			����������� ����� �� �������� ���������.
*/