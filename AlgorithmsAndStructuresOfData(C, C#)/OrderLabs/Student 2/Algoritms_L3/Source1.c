#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define N 50
FILE* data2;
typedef struct {
	char Name[N];
	char* SecondName;

	float SizeOfMassive;//nomer//���������� ������- ���� ����. 
	float* Massive;
	char GroupSymbol;
}Struct;
void writeToFrom(char a[], char b[]) {
	for (int i = 0; i < strlen(b) + 1; i++)
		a[i] = b[i];
}
void scanf_(int* a) {
	char temp[N];
	int error = 0;
	do {
		error = 0;
		scanf_s("%s", &temp, N - 1);
		for (int a = 0; a < strlen(temp); a++)
			if (atoi(temp) == 0 && !(('0' <= temp[a]) && (temp[a] <= '9')))
				error = 1;
		if (error == 1)
			printf("������ ����� ���� �����!\n");
		else {
			*a = atoi(temp);
			break;
		}
	} while (1);
}
Struct TakeElement() {
	Struct struct_;

	printf("\n����i�� i�'�: ");
	scanf_s("%s", &struct_.Name, N);

	char SName[N];
	printf("\n����i�� ��i�����: ");
	scanf_s("%s", &SName, N - 1);

	struct_.SecondName = (char*)malloc((strlen(SName) + 1) * sizeof(char));
	writeToFrom(struct_.SecondName, SName);

	struct_.SizeOfMassive = 0;

	char symbol[3];
	printf("\n����i�� ������, �� �i����i�� i�'� �����: ");
	scanf_s("%s", &symbol, 2);
	struct_.GroupSymbol = symbol[0];
	return struct_;
}
Struct* initArray(int dimension) {
	Struct* massive = (Struct*)malloc(dimension * sizeof(Struct));

	if (massive == NULL)
		return NULL;

	for (int i = 0; i < dimension; i++)
		massive[i] = TakeElement();

	return massive;
}
void ViewInfoElement(int i, Struct Struct) {
	printf("%d | %s - %s - %c\n",
		i, Struct.Name, Struct.SecondName, Struct.GroupSymbol);
}
void ViewInfo(Struct* Structs, int dimension) {
	for (int i = 0; i < dimension; i++)
		ViewInfoElement(i, Structs[i]);
}
int TakeDimension() {
	int chooseNum = 0;
	printf("������ dimension: ");
	do {
		scanf_(&chooseNum);
		if (chooseNum > 0 && chooseNum < 10)
			break;
		else if (chooseNum >= 10)
			printf("\n�� ����i��� ����� ��� �i���� 10)!\n");
	} while (1);
	return chooseNum;
}
Struct Change(Struct struct_) {
	int choose = 0;
	do {
		printf("����i�� �i���i��� �����, �� �� ������ �������� �� ������: ");
		scanf_(&choose);
		if (choose >= 1)
			break;
	} while (1);

	struct_.SizeOfMassive = (float)choose;
	struct_.Massive = (float*)malloc(struct_.SizeOfMassive * sizeof(float));
	float num = 0;
	for (int i = 0; i < struct_.SizeOfMassive; i++) {
		scanf_s("%f", &num);
		struct_.Massive[i] = num;
	}
	return struct_;
}
void ChooseChangeMassiveInStruct(Struct* Structs, int dimension) {
	int choosed = 0;
	do {
		printf("\n����i�� ����� �������� ��� ��i�: ");
		scanf_(&choosed);
		if (choosed >= 0 && choosed < dimension)
			break;
	} while (1);
	Structs[choosed] = Change(Structs[choosed]);
}
void MassiveOutPut(Struct Struct) {
	puts("����� �����: ");
	for (int i = 0; i < Struct.SizeOfMassive; i++)
		printf("%f ", Struct.Massive[i]);
}
void ChooseMassiveOutPut(Struct* Structs, int dimension) {
	int choosed = 0;
	do {
		printf("\n����i�� ����� �������� ��� ������: ");
		scanf_(&choosed);
		if (choosed >= 0 && choosed < dimension)
			break;
	} while (1);
	if (Structs[choosed].SizeOfMassive > 0)
		MassiveOutPut(Structs[choosed]);
	else puts("����� �mpty.");
}
void ChooseElementToChange(Struct* Structs, int dimension) {
	int choosed = 0;
	do {
		printf("\n����i�� ����� �������� ��� ��i�: ");
		scanf_(&choosed);
		if (choosed >= 0 && choosed < dimension)
			break;
	} while (1);
	Structs[choosed] = TakeElement();
}
Struct initKnigaFileR(FILE* data) {
	Struct list;

	fscanf_s(data, "%s ", list.Name, N);
	char SecondName[N];
	fscanf_s(data, "%s ", SecondName, N - 1);
	list.SecondName = (char*)malloc((strlen(SecondName) + 1) * sizeof(char));
	writeToFrom(list.SecondName, SecondName);
	list.SecondName[(strlen(SecondName))] = '\0';
	fscanf_s(data, "%c ", &list.GroupSymbol);
	fscanf_s(data, "%f ", &list.SizeOfMassive);
	float* Massive = (float*)malloc(list.SizeOfMassive * sizeof(float));
	for (int i = 0; i < list.SizeOfMassive; i++)
		fscanf_s(data, "%f ", &Massive[i]);
	list.Massive = Massive;
	return list;
}
Struct* initArrayFile(char fileName[], int dimension) {
	Struct* massive = (Struct*)malloc(dimension * sizeof(Struct));
	if (massive == NULL)
		return NULL;
	FILE* data;
	fopen_s(&data, fileName, "r");
	if (!data) {
		printf("Error");
		exit(1);
	}
	for (int i = 0; i < dimension; i++)
		massive[i] = initKnigaFileR(data);
	fclose(data);
	return massive;
}
Struct* ChooseOfInitMassiveStruct(Struct* massiveStruct, int dimension) {
	int choosed = 0;
	do {
		printf("\n�����i�� ����i� ��������� ������ ��������: \
				\n1. I�i�i��i���i� �������� ��������;\
				\n2. ���������� � �����;\
				\n�������: ");
		scanf_(&choosed);
	} while (choosed != 1 && choosed != 2);

	if (choosed == 1)
		massiveStruct = initArray(dimension);
	else massiveStruct = initArrayFile("data.txt", dimension);
	return massiveStruct;
}
void write(Struct list, FILE* data) {
	fprintf(data, "%s ", list.Name);
	fprintf(data, "%s ", list.SecondName);
	fprintf(data, "%c ", list.GroupSymbol);
	fprintf(data, "%f ", list.SizeOfMassive);
	for (int i = 0; i < list.SizeOfMassive; i++)
		fprintf(data, "%f ", list.Massive[i]);
	fprintf(data, "\n");
}
void initWrite(char fileName[], Struct* massive, int dimension) {
	FILE* data;
	fopen_s(&data, fileName, "w");//������ � ����� ����
	if (!data) {
		printf("Error");
		exit(1);
	}
	for (int i = 0; i < dimension; i++)
		write(massive[i], data);
	fprintf(data, "- - - 0 0 -\n");
	fclose(data);
	printf("����� ��� ���i����!");
}
void main()
{
	setlocale(LC_ALL, "Rus");
	Struct* massiveStruct = NULL;
	int choose = 0;
	int dimension = 4;
	do {
		puts("\n����: \
			\n1. �������� ���������;\
			\n2. ��i���� � �������i ����� �����;\
			\n3. ������� i�������i� ������;\
			\n4. ��i���� �������;\
			\n5. ������� i�������i� ��i� �������i�, ���i� �����;\
			\n6. ��i������ ���'���;\
			\n7. �������� i�������i� � ����; \
			\n0. Exit");
		scanf_(&choose);

		if (choose == 1) 
			massiveStruct = ChooseOfInitMassiveStruct(massiveStruct, dimension);
		else if (choose == 2 && massiveStruct != NULL)
			ChooseChangeMassiveInStruct(massiveStruct, dimension);
		else if (choose == 3 && massiveStruct != NULL)
			ChooseMassiveOutPut(massiveStruct, dimension);
		else if (choose == 4 && massiveStruct != NULL)
			ChooseElementToChange(massiveStruct, dimension);
		else if (choose == 5 && massiveStruct != NULL)
			ViewInfo(massiveStruct, dimension);
		else if (choose == 6)
		{
			free(massiveStruct);//�������� ���'��
			puts("������ �������!");
			massiveStruct = NULL;
		}
		else if (choose == 7 && massiveStruct != NULL)
			initWrite("data.txt", massiveStruct, dimension);
	} while (choose != 0);
}