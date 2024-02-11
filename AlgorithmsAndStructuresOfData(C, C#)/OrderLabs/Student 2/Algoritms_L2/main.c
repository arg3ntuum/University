#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define N 50
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
			\n0. Exit");
		scanf_(&choose);

		if (choose == 1) {
			if (massiveStruct == NULL)
				massiveStruct = initArray(dimension);
			else puts("����� �� NULL!");
		}
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
	} while (choose != 0);
}
