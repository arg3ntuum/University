#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define SLASH puts("///////////////////////////////////////")
#define N 30
#define E 7
/*
* ϳ� ��� ���������� ����������� �������� ������ ��������������� ������� ������ ��������. ���������� ���:
-- �������� ����� �� �������� ��������� (������� �� ����� ����� ���������, ��������� ������� ��� ����������� ���������� ������);
-- �������� ���������� �������� �� ������� �����.
������ � 9
�����: �����; ����� (�������, ���); �� �������; �����������; ����������; ����.
*/

typedef struct {
	char nazva[N];
	char autor[N];
	char vidavniztvo[N];
	int god;
	float sobivartist, cina;
} Kniga;
Kniga* initArray(int);
Kniga initKniga();
Kniga* initArray(int);
void displayArray(Kniga*, int); /* ����������� �������� */
//void displayChoise(Kniga*, int, char, int, int);
void displayKniga(Kniga);
//void sortLastName(Kniga*, int);
/* ��������� ���������� ������ �������� */
Kniga* initArray(int dimension) {
	int i;
	Kniga* massive = (Kniga*)malloc(dimension *sizeof(Kniga));
	if (massive == NULL)
		return NULL;
	for (i = 0; i < dimension; i++)
	{
		massive[i] = initKniga();
	}
	return massive;
}
/* ����������� �������� */
Kniga initKniga() {
	SLASH;
	Kniga kniga;
	printf("������� �������� �����: ");
	scanf_s("%s", &kniga.nazva, N);

	//printf("������� ��� ������ �����: ");
	//scanf_s("%s", kniga.autor_ima, N);
	printf("������� ������ �����: ");
	scanf_s("%s", &kniga.autor, N);

	printf("������� ��� ������� �����: ");
	scanf_s("%d", &kniga.god);

	printf("������� ������������ �����: ");
	scanf_s("%s", &kniga.vidavniztvo, N);

	printf("������� ������������� �����: ");
	scanf_s("%f", &kniga.sobivartist);
	
	printf("������� ���� �����: ");
	scanf_s("%f", &kniga.cina);
	
	return kniga;
}
/* �������� ��������� � ������� ��� ����� ���������� */
void displayArray(Kniga* massive, int dimension)
{
	for (int i = 0; i < dimension; i++)
	{
		displayKniga(massive[i]);
	}
}
/* ����������� ���������� ��� ��������� */
void displayKniga(Kniga kniga)
{
	SLASH;
	printf("��������: %s;\n�����:%s;\n���: %4d; ������������: %s;\n�������������: %5g; ����: %5g.\n", kniga.nazva, kniga.autor,/* kniga.autor_ima,*/ kniga.god, kniga.vidavniztvo, kniga.sobivartist, kniga.cina);
}
/* ���������� �������� */
void sortLastName(Kniga* massive, int dimension)
{
	Kniga temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].autor, massive[j - 1].autor) < 0)
			{
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortNazva(Kniga* massive, int dimension)
{
	Kniga temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].nazva, massive[j - 1].nazva) < 0)
			{
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortOsvita(Kniga* massive, int dimension)
{
	Kniga temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].vidavniztvo, massive[j - 1].vidavniztvo) < 0)
			{
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortYear(Kniga* massive, int dimension)
{
	Kniga temp;
	//for (int i = 0; i <= dimension; i++)
	//	for (int j = dimension - 1; j > i; j--)
	//		if (massive[j].god < massive[j - 1].god)//1 < 2
	//		{
	//			temp = massive[j];//1
	//			massive[j] = massive[j - 1];//1 = 2
	//			massive[j - 1] = temp;//1
	//		}
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (massive[j].god < massive[j - 1].god)//2 > 1
			{
				temp = massive[j - 1];//2
				massive[j- 1] = massive[j ];//2 = 1
				massive[j] = temp;//2
			}
}
void sortSebestoimost(Kniga* massive, int dimension)
{
	Kniga temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (massive[j].sobivartist < massive[j - 1].sobivartist)
			{
				temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
			}
}
void sortCena(Kniga* massive, int dimension)
{
	Kniga temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (massive[j].cina < massive[j - 1].cina)
			{
				temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
			}
}
/* ����� �������� */
int displayChoiseNazva(Kniga* massive, int dimension, int i, char* poisk_nazva)
{
	if (massive[i].nazva[0] == poisk_nazva[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].nazva[j] == '\0' && poisk_nazva[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].nazva[j] != poisk_nazva[j])
				return 0;
		}
	else return 0;
}
int displayChoiseFamilia(Kniga* massive, int dimension, int i, char *poisk_avtor)
{
	if (massive[i].autor[0] == poisk_avtor[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].autor[j] == '\0' && poisk_avtor[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].autor[j] != poisk_avtor[j])
				return 0;
		}
	else return 0;
}
int displayChoiseVidav(Kniga* massive, int dimension, int i, char* poisk_vidav)
{
	if (massive[i].vidavniztvo[0] == poisk_vidav[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].vidavniztvo[j] == '\0' && poisk_vidav[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].vidavniztvo[j] != poisk_vidav[j])
				return 0;
		}
	else return 0;
}
void displayChoise(Kniga* massive, int dimension)
{
	//�����; ����� (�������, ���); �� �������; �����������; ����������; ����.
	int sort_vibor[E] = { 0 }, o_1 = 0, o_2 = 0, o_3 = 0, o_4 = 0, o_5 = 0, o_6 = 0;
	printf("\n�������� ������ ������:\n1.��������;\n2.�����;\n3.��� �������;\n4.������������;\n5.C������������\n6.����;\n(0 - �����)��� �����: ");
	for (int i = 0; i < E; i++)
	{
		scanf_s("%d", &sort_vibor[i]);
		if (sort_vibor[i] == 0)
			break;
	}

	for (int i = 0; i < E; i++)
	{
		if (sort_vibor[i] == 0)
			break;
		else if (sort_vibor[i] == 1)
			o_1 = 1;
		else if (sort_vibor[i] == 2)
			o_2 = 1;
		else if (sort_vibor[i] == 3)
			o_3 = 1;
		else if (sort_vibor[i] == 4)
			o_4 = 1;
		else if (sort_vibor[i] == 5)
			o_5 = 1;
		else if (sort_vibor[i] == 6)
			o_6 = 1;
		else;
	}

	char poisk_nazva[N] = { 0 }, poisk_vidav[N] = { 0 }, poisk_avtor[N] = { 0 };
	int lowYear = 0, upperYear = 0;
	float lowSebestoimost = 0, upperSebestoimost = 0, lowCena = 0, upperCena = 0;
	for (int i = 0; i < E; i++) {
		if (o_1 == 1) {
			printf("\n��� ������ �� ��������� �������� ������� ���: ");
			scanf_s("%s", poisk_nazva, N);
			puts(poisk_nazva, N);
			o_1 = 2;
		}
		else if (o_2 == 1)
		{
			printf("\n��� ������ �� ������ ������� ��: ");
			scanf_s("%s", poisk_avtor, N);
			puts(poisk_avtor, N);
			o_2 = 2 ;
		}
		else if (o_3 == 1)
		{
			printf("\n��� ������ �� ���� ������� �� ������ �����������: ");
			scanf_s("%d", &lowYear);
			printf("\n��� ������ �� ���� ������� �� ������� �����������: ");
			scanf_s("%d", &upperYear);
			o_3 = 2;
		}
		else if (o_4 == 1) {
			printf("\n��� ������ �� ����������� ������� ��: ");
			scanf_s("%s", poisk_vidav, N);
			puts(poisk_vidav, N);
			o_4 = 2;
		}
		else if (o_5 == 1)
		{
			printf("\n��� ������ �� ������������� ������� �� ������ �����������: ");
			scanf_s("%g", &lowSebestoimost);
			printf("\n��� ������ �� ������������� ������� �� ������� �����������: ");
			scanf_s("%g", &upperSebestoimost);
			o_5 = 2;
		}
		else if (o_6 == 1)
		{
			printf("\n��� ������ �� ���� ������� �� ������ �����������: ");
			scanf_s("%g", &lowCena);
			printf("\n��� ������ �� ���� ������� �� ������� �����������: ");
			scanf_s("%g", &upperCena);
			o_6 = 2;
		}
	}

	int  kostil = 1, oshibka_poiska = 0;
	for (int i = 0, truue = 1; i < dimension; i++, truue = 1)
	{
		switch (kostil)
		{
		case 1:
		{
		if (o_1 == 2)
			truue = displayChoiseNazva(massive, dimension, i, poisk_nazva);
		}
		case 2:
		{
		if (o_2 == 2)
			truue = displayChoiseFamilia(massive, dimension, i, poisk_avtor);
		}
		case 3:
		{
			if (o_3 == 2)
			{
				if (massive[i].god <= upperYear && massive[i].god >= lowYear)
					truue = 1;
				else truue = 0;
			}
		}
		case 4: 
		{
		if (o_4 == 2)
			truue = displayChoiseVidav(massive, dimension, i, poisk_vidav);
		}
		case 5:
		{
			if (o_5 == 2) 
			{
				if (massive[i].sobivartist <= upperSebestoimost && massive[i].sobivartist >= lowSebestoimost)
					truue = 1;
				else truue = 0;
			}
		}
		case 6:
		{
		if (o_6 == 2)
		{
			if (massive[i].cina <= upperCena && massive[i].cina >= lowCena)
				truue = 1;
			else truue = 0;
		}
		}
		case 7: 
		{
			if (oshibka_poiska == 0 && (i == dimension - 1) && truue == 0) {
				SLASH;
				puts("\n� ���������, �� ������ �� �����(");
			}
				
			if (truue == 0)
				break;
			displayKniga(massive[i]);
			oshibka_poiska++;
		}
		}
	}
}
//������ �����
int vstup() 
{
	int segodnya = 0;
	puts("������ ����! ��� ������������ ���������� ��������! ���������� ��������, ������� ��� � ����!");
	puts("��������!��� ��������� ������ ������� ���� ���� ���������� ��������� �� ������������ ����.");
	do {
		puts("������� ��� �����, ���� ����������� ������� ��������� 30 ����!\n�� ������ ���������� ������� �����?(�� - 1, ��� 0)");
		scanf_s("%d", &segodnya);
		if (segodnya == 1 || segodnya == 0)
			break;
	} while (1);
	if (segodnya == 0)
	{
		SLASH;
		puts("�� �����. ��, �� ���� ��, ������!");
		SLASH;
		return 0;
	}
}
int main(void) 
{
setlocale(LC_ALL, "Rus");

int vstupi = vstup();
if (vstupi == 0)
return 0;

int dimension, choose = 0, sort_vibor = 0;
Kniga* massiveStruct;
SLASH;
printf("������� ���������� ������������ ����: ");
scanf_s("%d", &dimension);
if (dimension <=0)
{
	printf("���������� ���������!\n�� ���������...");
	return 0;
}
massiveStruct = initArray(dimension);
if (massiveStruct == NULL) {
	printf("������ ��������...\n");
	printf("�� ���������...");
}
SLASH;
printf("\n������ ����: \n");
displayArray(massiveStruct, dimension);
do {
	SLASH;
	puts("����������� ��� ������?(1 or 2, 0 - exit)");
	scanf_s("%d", &choose);
	if (choose == 0)
		break;
	else if (choose == 1)
	{
		//�����������
		//�����; ����� (�������, ���); �� �������; �����������; ����������; ����.
		puts("�������� ������ ����������:\n1.��������;\n2.�����;\n3.��� �������;\n4.������������;\n5.C������������\n6.����;\n��� �����: ");
		scanf_s("%d", &sort_vibor);
		if (sort_vibor == 1)
		{
			sortNazva(massiveStruct, dimension);
			displayArray(massiveStruct, dimension);
		}
		else if (sort_vibor == 2)
		{
			sortLastName(massiveStruct, dimension);
			displayArray(massiveStruct, dimension);
		}
		else if (sort_vibor == 3)
		{
			sortYear(massiveStruct, dimension);
			displayArray(massiveStruct, dimension);
		}
		else if (sort_vibor == 4)
		{
			sortOsvita(massiveStruct, dimension);
			displayArray(massiveStruct, dimension);
		}
		else if (sort_vibor == 5)
		{
			sortSebestoimost(massiveStruct, dimension);
			displayArray(massiveStruct, dimension);
		}
		else if (sort_vibor == 6)
		{
			sortCena(massiveStruct, dimension);
			displayArray(massiveStruct, dimension);
		}
	}
	else if (choose == 2)
	{
		//������
		//�����; ����� (�������, ���); �� �������; �����������; ����������; ����.
		displayChoise(massiveStruct, dimension);
	}
	else;
} while (1);
free(massiveStruct);
printf("\n����� ����� �����...\n");
return 0;
}