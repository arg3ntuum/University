#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <math.h>
#define	N 50
#define TIRE puts("--------------------------------------------------------------------------")
#define TABLE puts("|  #  |     ����     |     �����     | �i������� |   ��������   |  �i��  |")
typedef struct {//c��������
	char virobnik[N];//������������ �����
	char marka[N];//����� ���������� �����
	int sizeDiagonal;//������ ��������� �����
	int data[3];//���� ����� �����(����.�����.���)
	int price;//���� �����
} TV;
//�������� � ����� � ������� B
void writeToFirstFromSecond(char a[], char b[]) {
	for (int i = 0; i < N; i++)
		a[i] = b[i];
}
//��������� �����
void checkFiles(char file[]) {
	setlocale(LC_ALL, "Russian");
	FILE* data;
	fopen_s(&data, file, "rb+");
	if (!data) {
		printf("���� %s �� �� �������!\n", file);
		exit(0);
	}
	else {
		printf("���� %s �� �i��������!\n", file);
		fclose(data);
	}
}
//��������� ������ � ���������� (- 0 0 0 0 0 -) � ���������� �� ����������.(���������� = ���������� ��������)
int foundHowMuchStructInFile(char file[]) {
	int i;
	TV tv;
	FILE* data;
	fopen_s(&data, file, "r");//������
	if (!data) {
		puts("���� �� ��i� �i��������.\n");
		exit(1);
	}
	for (i = 0;; i++) {
		fscanf_s(data, "%s ", tv.virobnik, N);
		fscanf_s(data, "%d ", &tv.sizeDiagonal);
		fscanf_s(data, "%d ", &tv.data[0]);
		fscanf_s(data, "%d ", &tv.data[1]);
		fscanf_s(data, "%d ", &tv.data[2]);
		fscanf_s(data, "%d ", &tv.price);
		fscanf_s(data, "%s ", tv.marka, N);
		if (tv.data[0] == 0 && tv.data[1] == 0 && tv.data[2] == 0 && tv.sizeDiagonal == 0)
			break;
	}
	fclose(data);
	return i;
}
//��������� � ����� ������ � ���������
TV initTV(FILE* data) {
	TV tv;//������� ��������� � ������� ��� �������
	fscanf_s(data, "%s ", tv.virobnik, N);
	fscanf_s(data, "%d ", &tv.sizeDiagonal);
	fscanf_s(data, "%d ", &tv.data[0]);
	fscanf_s(data, "%d ", &tv.data[1]);
	fscanf_s(data, "%d ", &tv.data[2]);
	fscanf_s(data, "%d ", &tv.price);
	fscanf_s(data, "%s ", tv.marka, N);
	return tv;//���������� ���������
}
//������� ����� �������
TV* initArr(int dimension, char dataName[]) {
	TV* massive = (TV*)malloc(dimension * sizeof(TV));//������� ����� �������
	if (massive == NULL)
		return NULL;
	int vubor = 0;
	//��������� ����
	FILE* data;
	fopen_s(&data, dataName, "r");
	if (!data) {
		puts("���� �� ��i� �i��������.\n");
		exit(1);
	}
	//������� ���� ��� ���������� ������
	for (int i = 0; i < dimension; i++)
		massive[i] = initTV(data);
	fclose(data);
	return massive;
}
//����� ����� ����� 
void displayTV(TV tv, int i) {
	printf("|%4d.|  %2d.%2d.%4d  | %13s |  %5d''  | %12s |  %5d | \n", i + 1, 
		tv.data[0], tv.data[1], tv.data[2], tv.marka, tv.sizeDiagonal, tv.virobnik, tv.price);
	TIRE;
}
//����� ������ �������
void displayAll(TV* massive, int dimension) {
	//�������� ����� �������
	TIRE;
	TABLE;
	TIRE;
	//����� ������� � �������. ���� �� ������ ������ ��������
	for (int i = 0; i < dimension; i++) {
		displayTV(massive[i], i);
	}
}
//���� ������ ������
int changeSizeStruct(int dimension) {
	int sizeStruct = 0;
	do {
		printf("����i�� ����i� ������������ ������: ");
		scanf_s("%d", &sizeStruct);
		if (sizeStruct > dimension)
			printf("����i� �� ���� ������������ ���� �������� '%d'!\n", dimension);
		else if (sizeStruct <= 0)
			puts("����i� �� ���� ���� ����� ��� ���i������� 0! �� �� �������!", dimension);
	} while (!(sizeStruct > 0 && sizeStruct <= dimension));//���� �� ������ ���������� ���������� � ������ ����
	return sizeStruct;
}
int COUNTdays(int date[]) {return date[2] * 365 + date[1] * 30 + date[0];}//������� ���-�� ���� �� �������: ��� * 365 + ����� * 30 + ����
int COUNTmonth(int element1, int element2) {return element1 + element2 * 12;}//������� ���-�� ������� �� �������: ��� * 12 + �����
//���������� ������� �������
void sortCoctailByDate(TV* massive, int dimension) {
	int left = 0, right = dimension - 1; 
	int changesTrue = 1;  
	TV temp;
	while ((left < right) && changesTrue > 0) {
		changesTrue = 0;
		for (int i = left; i < right; i++)  {
			if (COUNTdays(massive[i].data)> COUNTdays(massive[i + 1].data)) {             
				temp = massive[i];
				massive[i] = massive[i + 1];
				massive[i + 1] = temp;
				changesTrue = 1;      
			}
		}
		right--; 
		for (int i = right; i > left; i--) {
			if (COUNTdays(massive[i - 1].data) > COUNTdays(massive[i].data)) {          
				temp = massive[i];
				massive[i] = massive[i - 1];
				massive[i - 1] = temp;
				changesTrue = 1;    
			}
		}
		left++; 
	}
}
void sortDiagonal(TV* massive, int dimension) {
	TV temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (massive[j].sizeDiagonal < massive[j - 1].sizeDiagonal) {
				temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
			}
}
//����� ������
void chooseMonth(int downLim[], int massive[]) {
	int month[2] = { 0 };
	do {
		if (downLim[0] == 0)
			printf("����i�� ���� ��������� (�i����, �i�, 09.2003): ");
		else printf("����i�� ����� ��������� (�i����, �i�, 09.2003): ");
		scanf_s("%d.%d", &month[0], &month[1]);
	} while (!(month[0] >= 1 && month[0] <=12 && month[0] >= downLim[0] && month[1] > 0 && month[1] >= downLim[1] ));
	//������ ����������
	massive[0] = month[0];
	massive[1] = month[1];
}
//����� �����
void chooseMarka(char markFunk[], TV* massive, int dimension)
{
	char marka[N] = { 0 };
	int error = 0;
	do {
		printf("����i�� ����� �����: ");
		scanf_s("%s", marka, N - 1);
		for (int i = 0; i < dimension; i++) 
			if (strcmp(massive[i].marka, marka) == 0)//���� ����������
				error = 1;
		if (error == 0)
			puts("����� �� ��������!");
	} while (error == 0);
	writeToFirstFromSecond(markFunk, marka);//������
}
//����� �� �� �����
void foundTVforMonth(TV* massive, int dimension) {
	int clearmassive[2] = { 0, 0 }, dataDown[2] = { 0 }, dataUp[2] = { 0 }, matrixMonth = 0, maxMonth = 0, minMonth = 0, check = 0, num = 0;
	chooseMonth(clearmassive, dataDown);
	chooseMonth(dataDown, dataUp);
	char marka[N] = { 0 };
	chooseMarka(marka, massive, dimension);
	maxMonth = COUNTmonth(dataUp[0], dataUp[1]);
	minMonth = COUNTmonth(dataDown[0], dataDown[1]);
	for (int i = 0; i < dimension; i++) {
		matrixMonth = COUNTmonth(massive[i].data[1], massive[i].data[2]);
		if (matrixMonth >= minMonth && matrixMonth <= maxMonth && strcmp(massive[i].marka, marka) == 0){
			if (check == 0) {
				check = 1;
				TIRE;
				TABLE;
				TIRE;
			}
			displayTV(massive[i], num++);
		}
	}
}
//����� ��������� ��� ������
int writeDiagonal() {
	int diag = 0;
	do {
		printf("����i�� �i������� ��� ������: ");
		scanf_s("%d", &diag);
		if (diag > 0)
			break;
		else puts("����i�� ��������i ���i!");
	} while (1);
	return diag;
}
//�������� �����
void lineChoise(TV* massive, int dimension, int diagonalFind) {
	int first = 0;
	for (int i = 0, nomer = 0; i < dimension; i++) {
		if (massive[i].sizeDiagonal == diagonalFind) {
			if (first == 0) {
				TIRE;
				TABLE;
				TIRE;
				first = 1;
			}
			displayTV(massive[i], nomer++);
		}
	}
	if (first == 0)
		puts("�i���� �� ��������!");
}
//�������� ����� �� ������ �����
void BinareToUp(TV* massive, int dimension, int diagonalFind, int center, int nomer) {
	for (int i = center; i < dimension; i++)
		if (massive[i].sizeDiagonal == diagonalFind) {
			if (nomer == 0) {
				TIRE;
				TABLE;
				TIRE;
			}
			displayTV(massive[i], nomer++);
		}
}		
//�������� ����� �� ������ ����
void BinareToDown(TV* massive, int dimension, int diagonalFind, int center, int nomer) {
	for (int i = center; i >= 0; i--)
		if (massive[i].sizeDiagonal == diagonalFind) {
			if (nomer == 0) {
				TIRE;
				TABLE;
				TIRE;
			}
			displayTV(massive[i], nomer++);
		}
}
//�������� ����� ������� �������
void Binare(TV* massive, int dimension, int diagonalFind) {
	int center = round(dimension / 2);
	static nomer = 0;
	sortDiagonal(massive, dimension);
	if (massive[center].sizeDiagonal < diagonalFind)
		BinareToUp(massive, dimension, diagonalFind, center, nomer);
	else if (massive[center].sizeDiagonal > diagonalFind)
		BinareToDown(massive, dimension, diagonalFind, center, nomer);
	else if (massive[center].sizeDiagonal == diagonalFind) {
		if (dimension == 1) {
			TIRE;
			TABLE;
			TIRE;
			displayTV(massive[0], nomer++);
		}	
		else if (dimension == 2) {
			nomer++;
			lineChoise(massive, dimension, diagonalFind);
		}
		else if (dimension >= 3) { 
			if ((massive[center].sizeDiagonal == diagonalFind) && massive[center - 1].sizeDiagonal != diagonalFind && massive[center + 1].sizeDiagonal != diagonalFind) {
				TIRE;
				TABLE;
				TIRE;
				displayTV(massive[0], nomer++);
			}
			else if (massive[center].sizeDiagonal == diagonalFind && massive[center - 1].sizeDiagonal == diagonalFind && massive[center + 1].sizeDiagonal != diagonalFind)
				BinareToDown(massive, dimension, diagonalFind, center, nomer);
			else if (massive[center].sizeDiagonal == diagonalFind && massive[center - 1].sizeDiagonal != diagonalFind && massive[center + 1].sizeDiagonal == diagonalFind)
				BinareToUp(massive, dimension, diagonalFind, center, nomer);
			else if (massive[center].sizeDiagonal == diagonalFind && massive[center - 1].sizeDiagonal == diagonalFind && massive[center + 1].sizeDiagonal == diagonalFind) {
				nomer++;
				lineChoise(massive, dimension, diagonalFind);
			}
			
		}
	}
	//if (nomer <= 0) puts("�i���� �� ��������!");
}
//������ �������
void writingToFileTV(TV tv, FILE* data) {
	fprintf(data, "%s ", tv.virobnik);
	fprintf(data, "%d ", tv.sizeDiagonal);
	fprintf(data, "%d ", tv.data[0]);
	fprintf(data, "%d ", tv.data[1]);
	fprintf(data, "%d ", tv.data[2]);
	fprintf(data, "%d ", tv.price);
	fprintf(data, "%s ", tv.marka);
}
void writingToFileMassive(TV* massive, int dimension, char fileName[]) {
	FILE* data;
	fopen_s(&data, fileName, "w");
	if (!data) {
		puts("�� ��������.\n");
		exit(1);
	}
	for (int i = 0; i < dimension; i++)
		writingToFileTV(massive[i], data);
	fprintf(data, "- 0 0 0 0 0 -\n");
	fclose(data);
}
//������� ������ ������
void choise(TV* massive, int dimension) {
	int choose = 0, diagonalFind = writeDiagonal();
	do {
		printf("����\n1.�i�i���� ����� �� �i������i;\n2.�i������ ����� �� �i������i;\n0.Exit;\n��� ���i�: ");
		scanf_s("%d", &choose);
		if (choose == 1)
			lineChoise(massive, dimension, diagonalFind);
		else if (choose == 2)
			Binare(massive, dimension, diagonalFind);
	} while (choose != 0);
}
//������� �������
void main(int argc, char* argv[]) {
	setlocale(LC_ALL, ""); //�����������
	char dataName[N] = { 0 };
	if (argc == 2) {
		printf("���� ���� �������� ����� ��������!\n");
		writeToFirstFromSecond(dataName, argv[1]);
		checkFiles(dataName);
	}
	else {
		printf("��� �i������� ����, ����� ������ ���� ����� ���i: ");
		scanf_s("%s", dataName, N - 1);
		checkFiles(dataName);
	}
	system("pause");
	system("cls");
	int dimension = foundHowMuchStructInFile(dataName), choose = 0;
	TV* massiveStruct = initArr(dimension, dataName);
	do {
		puts("\t� � � �\
		 \n1.��i ������i�;\
		 \n2.���i���� ����i� ������;\
		 \n3.���������� �� �����;\
		 \n4.�i���i��� �������� �����i���i� ������ ����� � ������� ���i��;\
		 \n5.����� �� �i�������� �����i����;\
		 \n0.Exit;\
		 \n��� ���i�: ");
		scanf_s("%d", &choose);
		if (choose == 1)
			displayAll(massiveStruct, dimension);
		else if (choose == 2) {
			dimension = changeSizeStruct(foundHowMuchStructInFile(dataName));
			massiveStruct = initArr(dimension, dataName);
		}
		else if (choose == 3)
			sortCoctailByDate(massiveStruct, dimension);
		else if (choose == 4)
			foundTVforMonth(massiveStruct, dimension);
		else if (choose == 5)
			choise(massiveStruct, dimension);
	} while (choose != 0);
	writingToFileMassive(massiveStruct, dimension, dataName);//������ � ����
	free(massiveStruct); //������������ ������
}
/*
+1.	��� ����� �������� � ���������� �����. ���� ���� ��� �� ���� ������, �� ���� ���������� ������ ��������� ������������.
+2.	��������������� �������� �������� ����� (����� ������ �������� ������������ ���� ���������� ������). 
+ϳ��� ������������ ������ ��� ���������� �������� ������.
+3.	����� ���������� ���������� ����� �������� � ������ �� �������.
+4.	������� ���������� �������� � ������ ������� � ���������� �� �����.
+5.	���������� ��� ������ ��� ������� � ���������.
24 variant
+� ���������� ���� ������� ���������: �����-��������, �����, ����� �������, ���� �� ������� ������, ���� �������.
+��������� ������� �������� ��������� ����� LG �� ������ ��� �����.
+������������ ���������� �� ����� ������� ��������� ������� ���������� ���������� (Cocktail sort).
+����������� ����� ��������� �� ������� �������.
*/