#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>
#define	N 50
#define TIRE puts("------------------------------------------------------------------------------------------------------")
#define TABLE puts("|  #  |       ��������       |  ���  ������  | ���������� |   ���������   |    �������    | �������� |")
#define TIRE_COMPLECT puts("-------------------------------------------------------------------------------")
typedef struct {//c��������
	char nazva[N];//�����
	int type;//���
	int amount;//���������� ������
	int cost;//c�������� ������
	int cost_market;//c�������� ������ � �������
	int guarantee;//�������� � �������
} Tovar;
void writeTo(char a[], char b[]) {
	for (int i = 0; i < N; i++)
		a[i] = b[i];
}
void FileCheckForError(char fileName[]) {
	setlocale(LC_ALL, "Russian");
	FILE* data;
	fopen_s(&data, fileName, "rb+");
	if (!data) {
		printf("���� %s �� ��������!\n", fileName);
		exit(0);
	}
	else {
		printf("���� %s ��������!\n", fileName);
		fclose(data);
	}
}
int takeSizeStruct(char file[]) {
	int i;
	Tovar tovar;
	FILE* data;
	fopen_s(&data, file, "r");
	if (!data) {
		puts("���� �� ��� ������.\n");
		exit(1);
	}
	for (i = 0; ; i++) {
		fscanf_s(data, "%s ", tovar.nazva, N);
		fscanf_s(data, "%d ", &tovar.type);
		fscanf_s(data, "%d ", &tovar.amount);
		fscanf_s(data, "%d ", &tovar.cost);
		fscanf_s(data, "%d ", &tovar.cost_market);
		fscanf_s(data, "%d ", &tovar.guarantee);
		if (tovar.amount == 0 && tovar.cost == 0 && tovar.cost_market == 0 && tovar.guarantee == 0 && tovar.type == 0)
			break;
	}
	fclose(data);
	return i;
}
Tovar initTovar(FILE* data) {
	Tovar tovar;
	fscanf_s(data, "%s ", tovar.nazva, N);
	fscanf_s(data, "%d ", &tovar.type);
	fscanf_s(data, "%d ", &tovar.amount);
	fscanf_s(data, "%d ", &tovar.cost);
	fscanf_s(data, "%d ", &tovar.cost_market);
	fscanf_s(data, "%d ", &tovar.guarantee);
	return tovar;
}
Tovar* initArr(int dimension, char dataName[]) {
	Tovar* massive = (Tovar*)malloc(dimension * sizeof(Tovar));
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
		massive[i] = initTovar(data);
	fclose(data);
	return massive;
}
void displayTovar(Tovar tovar, int i) {
	printf("|%4d.|  %19s | ", i + 1,tovar.nazva );
	switch(tovar.type){
	case 1: printf("     CPU     "); break;
	case 2: printf(" MotherBoard "); break;
	case 3: printf("     GPU     "); break;
	case 4: printf("     RAM     "); break;
	case 5: printf("     HDD     "); break;
	case 6: printf("  Comp Case  "); break;
	case 7: printf("    DVDRW    "); break;
	case 8: printf("   Monitor   "); break;
	} 
	printf(" | %7d �� |  %8d ��� | %9d ��� |  %3d ��� | \n", tovar.amount, tovar.cost, tovar.cost_market, tovar.guarantee);
	TIRE;
}
void display(Tovar* massive, int dimension) {
	TIRE;
	TABLE;
	TIRE;
	for (int i = 0; i < dimension; i++) {
		displayTovar(massive[i], i);
	}
}
int changeSizeMassive(int dimension) {
	int sizeOfMassive = 0;
	do {
		printf("������� ����� ������ �������: ");
		scanf_s("%d", &sizeOfMassive);
		if (sizeOfMassive > dimension)
			printf("������ �� ������ ��������� '%d'!\n", dimension);
		else if (sizeOfMassive <= 0)
			puts("������ �� ������ ���� ���� ��� �������������� � 0!", dimension);
	} while (!(sizeOfMassive > 0 && sizeOfMassive <= dimension));
	return sizeOfMassive;
}
void writingToFileTovar(Tovar kniga, FILE* data) {
	fprintf(data, "%s ", kniga.nazva);
	fprintf(data, "%d ", kniga.type);
	fprintf(data, "%d ", kniga.amount);
	fprintf(data, "%d ", kniga.cost);
	fprintf(data, "%d ", kniga.cost_market);
	fprintf(data, "%d\n", kniga.guarantee);
}
void writingToFileMassive(Tovar* massive, int dimension, char fileName[]) {
	FILE* data;
	fopen_s(&data, fileName, "w");
	if (!data) {
		puts("Failed to open file \n");
		exit(1);
	}
	for (int i = 0; i < dimension; i++)
		writingToFileTovar(massive[i], data);
	fprintf(data, "- 0 0 0 0 0\n");
	fclose(data);
}
void sortNazva(Tovar* massive, int dimension) {
	Tovar temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].nazva, massive[j - 1].nazva) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortCoctailByAmount(Tovar* massive, int dimension) {
	int left = 0, right = dimension - 1;
	int changesTrue = 1;
	Tovar temp;
	while ((left < right) && changesTrue > 0) {
		changesTrue = 0;
		for (int i = left; i < right; i++) {
			if (massive[i].amount > massive[i + 1].amount) {
				temp = massive[i];
				massive[i] = massive[i + 1];
				massive[i + 1] = temp;
				changesTrue = 1;
			}
		}
		right--;
		for (int i = right; i > left; i--) {
			if (massive[i - 1].amount > massive[i].amount) {
				temp = massive[i];
				massive[i] = massive[i - 1];
				massive[i - 1] = temp;
				changesTrue = 1;
			}
		}
		left++;
	}
}
//����� �������� ��� ������
void takeNazva(char nazva[]) {
	char nazvaFound[N] = {0};
	printf("������� �������� ��� ������ (��� ��������): ");
	scanf_s("%s", nazvaFound, N - 1);
	writeTo(nazva, nazvaFound);
}
void lineFound(Tovar* massive, int dimension, char findNazva[]) {
	int first = 0;
	for (int i = 0, nomer = 0; i < dimension; i++) {
		if (strstr(massive[i].nazva, findNazva)) {
			if (first == 0) {
				TIRE;
				TABLE;
				TIRE;
				first = 1;
			}
			displayTovar(massive[i], nomer++);
		}
	}
	if (first == 0)
		puts("������ �� �������!");
}
void BinareWhileUp(Tovar* massive, int dimension, char findNazva[], int center, int nomer) {
	for (int i = center; i < dimension; i++)
		if (strstr(massive[i].nazva, findNazva)) {
			if (nomer == 0) {
				TIRE;
				TABLE;
				TIRE;
			}
			displayTovar(massive[i], nomer++);
		}
}
void BinareWhileDown(Tovar* massive, int dimension, char findNazva[], int center, int nomer) {
	for (int i = center; i >= 0; i--)
		if (strstr(massive[i].nazva, findNazva)) {
			if (nomer == 0) {
				TIRE;
				TABLE;
				TIRE;
			}
			displayTovar(massive[i], nomer++);
		}
}
void Binare(Tovar* massive, int dimension, char findNazva[]) {
	int center = round(dimension / 2);
	static nomer = 0;
	sortNazva(massive, dimension);
	if (strcmp(massive[center].nazva, findNazva) < 0)
		BinareWhileUp(massive, dimension, findNazva, center, nomer);
	else if (strcmp(massive[center].nazva, findNazva) > 0)
		BinareWhileDown(massive, dimension, findNazva, center, nomer);
	else if (strcmp(massive[center].nazva, findNazva) == 0) {
		if (dimension == 1) {
			TIRE;
			TABLE;
			TIRE;
			displayTovar(massive[0], nomer++);
		}
		else if (dimension == 2) {
			nomer++;
			lineFound(massive, dimension, findNazva);
		}
		else if (dimension >= 3) {
			if (strcmp(massive[center].nazva, findNazva) == 0 && strcmp(massive[center - 1].nazva, findNazva) != 0 && strcmp(massive[center].nazva, findNazva) != 0) {
				TIRE;
				TABLE;
				TIRE;
				displayTovar(massive[0], nomer++);
			}
			else if (strcmp(massive[center].nazva, findNazva) == 0 && strcmp(massive[center - 1].nazva, findNazva) == 0 && strcmp(massive[center + 1].nazva, findNazva) != 0)
				BinareWhileDown(massive, dimension, findNazva, center, nomer);
			else if (strcmp(massive[center].nazva, findNazva) == 0 && strcmp(massive[center - 1].nazva, findNazva) != 0 && strcmp(massive[center + 1].nazva, findNazva)==0)
				BinareWhileUp(massive, dimension, findNazva, center, nomer);
			else if (strcmp(massive[center].nazva, findNazva) == 0 && strcmp(massive[center - 1].nazva, findNazva) == 0 && strcmp(massive[center + 1].nazva, findNazva) == 0) {
				nomer++;
				lineFound(massive, dimension, findNazva);
			}
		}
	}
}
void choise(Tovar* massive, int dimension) {
	int choose = 0;
	char nazva[N] = { 0 };
	takeNazva(nazva);
	do {
		printf("����\n1.�������� �����;\n2.�������� �����;\n0.�����;\n��� �����: ");
		scanf_s("%d", &choose);
		if (choose == 1)
			lineFound(massive, dimension, nazva);
		else if (choose == 2)
			Binare(massive, dimension, nazva);
	} while (choose != 0);
}
int MinCPU(Tovar* massive, int dimension, char minCPU_name[], int *minGeneral_cost_market,int *minPribil) {
	int min = 9999999999999, takeSizeStruct = min, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (min > massive[i].cost_market && massive[i].type == 1) {
			min = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(minCPU_name, massive[i].nazva);
		}	
	}
	if (takeSizeStruct != min) {
		*minPribil += pribil;
		*minGeneral_cost_market += min;
		return min;
	}
	else return 0;
}
int MaxCPU(Tovar* massive, int dimension, char maxCPU_name[], int* maxGeneral_cost_market, int* maxPribil) {
	int max = 0, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (max < massive[i].cost_market && massive[i].type == 1) {
			max = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(maxCPU_name, massive[i].nazva);
		}
	}
	*maxPribil += pribil;
	*maxGeneral_cost_market += max;
	return max;
}
int MinMotherBoard(Tovar* massive, int dimension, char minMotherBoard_name[], int* minGeneral_cost_market, int* minPribil) {
	int min = 9999999999999, takeSizeStruct = min, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (min > massive[i].cost_market && massive[i].type == 2) {
			min = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(minMotherBoard_name, massive[i].nazva);
		}
	}
	if (takeSizeStruct != min) {
		*minPribil += pribil;
		*minGeneral_cost_market += min;
		return min;
	}
	else return 0;
}
int MaxMotherBoard(Tovar* massive, int dimension, char maxMotherBoard_name[], int* maxGeneral_cost_market, int* maxPribil) {
	int max = 0, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (max < massive[i].cost_market && massive[i].type == 2) {
			max = massive[i].cost_market; 
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(maxMotherBoard_name, massive[i].nazva);
		}
	}
	*maxPribil += pribil;
	*maxGeneral_cost_market += max;
	return max;
}
int MinGPU(Tovar* massive, int dimension, char minGPU_name[], int* minGeneral_cost_market, int* minPribil) {
	int min = 9999999999999, takeSizeStruct = min, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (min > massive[i].cost_market && massive[i].type == 3) {
			min = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(minGPU_name, massive[i].nazva);
		}
	}
	if (takeSizeStruct != min) {
		*minPribil += pribil;
		*minGeneral_cost_market += min;
		return min;
	}
	else return 0;
}
int MaxGPU(Tovar* massive, int dimension, char maxGPU_name[], int* maxGeneral_cost_market, int* maxPribil) {
	int max = 0, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (max < massive[i].cost_market && massive[i].type == 3) {
			max = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(maxGPU_name, massive[i].nazva);
		}
	}
	*maxPribil += pribil;
	*maxGeneral_cost_market += max;
	return max;
}
int MinRAM(Tovar* massive, int dimension, char minRAM_name[], int* minGeneral_cost_market, int* minPribil) {
	int min = 9999999999999, takeSizeStruct = min, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (min > massive[i].cost_market && massive[i].type == 4) {
			pribil = massive[i].cost_market - massive[i].cost;
			min = massive[i].cost_market;
			writeTo(minRAM_name, massive[i].nazva);
		}
	}
	if (takeSizeStruct != min) {
		*minPribil += pribil;
		*minGeneral_cost_market += min;
		return min;
	}
	else return 0;
}
int MaxRAM(Tovar* massive, int dimension, char maxRAM_name[], int* maxGeneral_cost_market, int* maxPribil) {
	int max = 0, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (max < massive[i].cost_market && massive[i].type == 4) {
			max = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(maxRAM_name, massive[i].nazva);
		}
	}
	*maxPribil += pribil;
	*maxGeneral_cost_market += max;
	return max;
}
int MinHDD(Tovar* massive, int dimension, char minHDD_name[], int* minGeneral_cost_market, int* minPribil) {
	int min = 9999999999999, takeSizeStruct = min, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (min > massive[i].cost_market && massive[i].type == 5) {
			min = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(minHDD_name, massive[i].nazva);
		}
	}
	if (takeSizeStruct != min) {
		*minPribil += pribil;
		*minGeneral_cost_market += min;
		return min;
	}
	else return 0;
}
int MaxHDD(Tovar* massive, int dimension, char maxHDD_name[], int* maxGeneral_cost_market, int* maxPribil) {
	int max = 0, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (max < massive[i].cost_market && massive[i].type == 5) {
			max = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(maxHDD_name, massive[i].nazva);
		}
	}
	*maxPribil += pribil;
	*maxGeneral_cost_market += max;
	return max;
}
int MinCC(Tovar* massive, int dimension, char minCC_name[], int* minGeneral_cost_market, int* minPribil) {
	int min = 9999999999999, takeSizeStruct = min, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (min > massive[i].cost_market && massive[i].type == 6) {
			min = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(minCC_name, massive[i].nazva);
		}
	}
	if (takeSizeStruct != min) {
		*minPribil += pribil;
		*minGeneral_cost_market += min;
		return min;
	}
	else return 0;
}
int MaxCC(Tovar* massive, int dimension, char maxCC_name[], int* maxGeneral_cost_market, int* maxPribil) {
	int max = 0, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (max < massive[i].cost_market && massive[i].type == 6) {
			max = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(maxCC_name, massive[i].nazva);
		}
	}
	*maxPribil += pribil;
	*maxGeneral_cost_market += max;
	return max;
}
int MinDVD(Tovar* massive, int dimension, char minDVD_name[], int* minGeneral_cost_market, int* minPribil) {
	int min = 9999999999999, takeSizeStruct = min, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (min > massive[i].cost_market && massive[i].type == 7) {
			min = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(minDVD_name, massive[i].nazva);
		}
	}
	if (takeSizeStruct != min) {
		*minPribil += pribil;
		*minGeneral_cost_market += min;
		return min;
	}
	else return 0;
}
int MaxDVD(Tovar* massive, int dimension, char maxDVD_name[], int *maxGeneral_cost_market, int* maxPribil) {
	int max = 0, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (max < massive[i].cost_market && massive[i].type == 7) {
			max = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(maxDVD_name, massive[i].nazva);
		}
	}
	*maxPribil += pribil;
	*maxGeneral_cost_market += max;
	return max;
}
int MinMonitor(Tovar* massive, int dimension, char minMonitor_name[], int* minGeneral_cost_market, int* minPribil) {
	int min = 9999999999999, takeSizeStruct = min, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (min > massive[i].cost_market && massive[i].type == 8) {
			min = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(minMonitor_name, massive[i].nazva);
		}
	}
	if (takeSizeStruct != min) {
		*minPribil += pribil;
		*minGeneral_cost_market += min;
		return min;
	}
	else return 0;
}
int MaxMonitor(Tovar* massive, int dimension, char maxMonitor_name[], int* maxGeneral_cost_market, int* maxPribil) {
	int max = 0, pribil = 0;
	for (int i = 0; i < dimension; i++) {
		if (max < massive[i].cost_market && massive[i].type == 8) {
			max = massive[i].cost_market;
			pribil = massive[i].cost_market - massive[i].cost;
			writeTo(maxMonitor_name, massive[i].nazva);
		}
	}
	*maxPribil += pribil;
	*maxGeneral_cost_market += max;
	return max;
}
void foundMinMaxComplect(Tovar* massive, int dimension) {
	int minGeneral_cost_market = 0, maxGeneral_cost_market = 0, minPribil = 0, maxPribil = 0; 

	char minCPU_name[N] = "CPU �� �������.", maxCPU_name[N] = "CPU �� �������.";
	int minCPU_cost = MinCPU(massive, dimension, minCPU_name, &minGeneral_cost_market, &minPribil), maxCPU_cost = MaxCPU(massive, dimension, maxCPU_name, &maxGeneral_cost_market, &maxPribil);

	char minGPU_name[N] = "GPU �� �������.", maxGPU_name[N] = "GPU �� �������.";
	int minGPU_cost = MinGPU(massive, dimension, minGPU_name, &minGeneral_cost_market, &minPribil), maxGPU_cost = MaxGPU(massive, dimension, maxGPU_name, &maxGeneral_cost_market, &maxPribil);

	char minMother_name[N] = "MotherBoard �� ������a.", maxMother_name[N] = "MotherBoard �� ������a.";
	int minMother_cost = MinMotherBoard(massive, dimension, minMother_name, &minGeneral_cost_market, &minPribil), maxMother_cost = MaxMotherBoard(massive, dimension, maxMother_name, &maxGeneral_cost_market, &maxPribil);

	char minRAM_name[N] = "RAM �� �������.", maxRAM_name[N] = "RAM �� �������.";
	int minRAM_cost = MinRAM(massive, dimension, minRAM_name, &minGeneral_cost_market, &minPribil), maxRAM_cost = MaxRAM(massive, dimension, maxRAM_name, &maxGeneral_cost_market, &maxPribil);

	char minHDD_name[N] = "HDD �� �������.", maxHDD_name[N] = "HDD �� �������.";
	int minHDD_cost = MinHDD(massive, dimension, minHDD_name, &minGeneral_cost_market, &minPribil), maxHDD_cost = MaxHDD(massive, dimension, maxHDD_name, &maxGeneral_cost_market, &maxPribil);

	char minCC_name[N] = "CompCase �� ������.", maxCC_name[N] = "CompCase �� ������.";
	int minCC_cost = MinCC(massive, dimension, minCC_name, &minGeneral_cost_market, &minPribil), maxCC_cost = MaxCC(massive, dimension, maxCC_name, &maxGeneral_cost_market, &maxPribil);

	char minDVD_name[N] = "DVDRW �� �������.", maxDVD_name[N] = "DVDRW �� �������.";
	int minDVD_cost = MinDVD(massive, dimension, minDVD_name, &minGeneral_cost_market, &minPribil), maxDVD_cost = MaxDVD(massive, dimension, maxDVD_name, &maxGeneral_cost_market, &maxPribil);

	char minMonitor_name[N] = "Monitor �� �������.", maxMonitor_name[N] = "Monitor �� �������.";
	int minMonitor_cost = MinMonitor(massive, dimension, minMonitor_name, &minGeneral_cost_market, &minPribil), maxMonitor_cost = MaxMonitor(massive, dimension, maxMonitor_name, &maxGeneral_cost_market, &maxPribil);

	//TABLE
	TIRE_COMPLECT;
	puts("|        ����� ������� ��������        |        ����� ������� ��������        |");
	TIRE_COMPLECT;
	printf("| CPU: %31s | CPU: %31s |\n", minCPU_name, maxCPU_name);
	TIRE_COMPLECT;
	printf("| C��������: %21d ��� | C��������: %21d ��� |\n", minCPU_cost, maxCPU_cost);
	TIRE_COMPLECT;
	printf("| MotherBoard: %23s | MotherBoard: %23s |\n", minMother_name, maxMother_name);
	TIRE_COMPLECT;
	printf("| C��������: %21d ��� | C��������: %21d ��� |\n", minMother_cost, maxMother_cost);
	TIRE_COMPLECT;
	printf("| GPU: %31s | GPU: %31s |\n", minGPU_name, maxGPU_name);
	TIRE_COMPLECT;
	printf("| C��������: %21d ��� | C��������: %21d ��� |\n", minGPU_cost, maxGPU_cost);
	TIRE_COMPLECT;
	printf("| RAM: %31s | RAM: %31s |\n", minRAM_name, maxRAM_name);
	TIRE_COMPLECT;
	printf("| C��������: %21d ��� | C��������: %21d ��� |\n", minRAM_cost, maxRAM_cost);
	TIRE_COMPLECT;
	printf("| HDD: %31s | HDD: %31s |\n", minHDD_name, maxHDD_name);
	TIRE_COMPLECT;
	printf("| C��������: %21d ��� | C��������: %21d ��� |\n", minHDD_cost, maxHDD_cost);
	TIRE_COMPLECT;
	printf("| Computer case: %21s | Computer case: %21s |\n", minCC_name, maxCC_name);
	TIRE_COMPLECT;
	printf("| C��������: %21d ��� | C��������: %21d ��� |\n", minCC_cost, maxCC_cost);
	TIRE_COMPLECT;
	printf("| DVDRW: %29s | DVDRW: %29s |\n", minDVD_name, maxDVD_name);
	TIRE_COMPLECT;
	printf("| C��������: %21d ��� | C��������: %21d ��� |\n", minDVD_cost, maxDVD_cost);
	TIRE_COMPLECT;
	printf("| Monitor: %27s | Monitor: %27s |\n", minMonitor_name, maxMonitor_name);
	TIRE_COMPLECT;
	printf("| C��������: %21d ��� | C��������: %21d ��� |\n", minMonitor_cost, maxMonitor_cost);
	TIRE_COMPLECT;
	TIRE_COMPLECT;
	printf("| ����� ���������: %15d ��� | ����� ���������: %15d ��� |\n", minGeneral_cost_market, maxGeneral_cost_market);
	TIRE_COMPLECT;
	printf("| �������: %23d ��� | �������: %23d ��� |\n", minPribil, maxPribil);
	TIRE_COMPLECT;
}
void main(int argc, char* argv[]) {
	setlocale(LC_ALL, ""); //�����������
	char dataName[N] = "data.txt";
	if (argc == 2) {
		printf("���� ��������� ����� ��������!\n");
		writeTo(dataName, argv[1]);
		FileCheckForError(dataName);
	}
	else {
		printf("������� �������� ����� ��� ��������� ������: ");
		scanf_s("%s", dataName, N - 1);
		FileCheckForError(dataName);
	}
	system("pause");
	system("cls");
	int dimension = takeSizeStruct(dataName), choose = 0;
	Tovar* massiveStruct = initArr(dimension, dataName);
	do {
		puts("\t� � � �\
		 \n1.������ �������;\
		 \n2.�������� ������ �������;\
		 \n3.���������� �� ����������;\
		 \n4.������ ����� �������/������� ���������;\
		 \n5.����� �� ��������;\
		 \n0.Exit;\
		 \n��� ���i�: ");
		scanf_s("%d", &choose);
		if (choose == 1)
			display(massiveStruct, dimension);
		else if (choose == 2) {
			dimension = changeSizeMassive(takeSizeStruct(dataName));
			massiveStruct = initArr(dimension, dataName);
		}
		else if (choose == 3)
			sortCoctailByAmount(massiveStruct, dimension);
		else if (choose == 4)
			foundMinMaxComplect(massiveStruct, dimension);
		else if (choose == 5)
			choise(massiveStruct, dimension);
	} while (choose != 0);
	writingToFileMassive(massiveStruct, dimension, dataName);
	free(massiveStruct);
}
/*
		+1.	��� ����� �������� � ���������� �����. ���� ���� ��� �� ���� ������, �� ���� ���������� ������ ��������� ������������.
		+2.	��������������� �������� �������� ����� (����� ������ �������� ������������ ���� ���������� ������). 
		+ϳ��� ������������ ������ ��� ���������� �������� ������.
		+3.	����� ���������� ���������� ����� �������� � ������ �� �������.
		+4.	������� ���������� �������� � ������ ������� � ���������� �� �����.
		+5.	���������� ��� ������ ��� ������� � ���������.

		+6.	� ���������� ���� � ���������� ��� ������ 
		+(���������, ���������� �����, ���������, ����� �����, ������ �����, �������, DVD-RW, �������)
		+� ������ ������: ����� ������, ������� ������� ������,������ ������� ���-���� ������,�������� ����, ������� (����� ������). 

		����������� ������������ ������������ � ������������ ��������� (�� �������� ���) � ��� ���� ����-�� 
		�� ������ �������� ����� �� ������� ����� ���������.
		������������ ���������� �� ������� ������� ������ ������� ���������� ���������� (Cock-tail sort). 
		����������� ����� �� ������ ������.
*/