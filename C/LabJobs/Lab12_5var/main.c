#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define SLASH puts("///////////////////////////////////////")
#define N 30
#define E 13
/*
* ϳ� ��� ���������� ����������� �������� ������ ��������������� ������� ������ ��������. ���������� ���:
-- �������� ����� �� �������� ��������� (������� �� ����� ����� ���������, ��������� ������� ��� ����������� ���������� ������);
-- �������� ���������� �������� �� ������� �����.
������ � 5
�������: �������; ���; �� �������; 
������� ������ (�����, ����, ������, �������, ��������); 
���� ���������� (��, �����, �����);
� ����;
��������� �����;
�����;
�� ������� �� ������
*/

typedef struct {
	char people[3][N];
	char dom_address[5][N];
	int data[3];
	int numCeh;
	int tabl_num;
	char osvita[N];
	int god_priyoma;
} Robochiy;
Robochiy* initArray(int);
Robochiy initRabochiy();
Robochiy* initArray(int);
void displayArray(Robochiy*, int); /* ����������� �������� */
//void displayChoise(Kniga*, int, char, int, int);
void displayRabochiy(Robochiy);
//void sortLastName(Kniga*, int);
/* ��������� ���������� ������ �������� */
Robochiy* initArray(int dimension) {
	int i;
	Robochiy* massive = (Robochiy*)malloc(dimension *sizeof(Robochiy));
	if (massive == NULL)
		return NULL;
	for (i = 0; i < dimension; i++) {
		massive[i] = initRabochiy();
	}
	return massive;
}
/* ����������� �������� */
Robochiy initRabochiy() {
	SLASH;
	Robochiy trudyaschiysya;

	printf("������� �������, ��� � �������� ��������(����� ������): ");
	scanf_s("%s %s %s", &trudyaschiysya.people[0], N -1,
		&trudyaschiysya.people[1], N - 1, &trudyaschiysya.people[2], N - 1);

	printf("������� �������� ������: \
			\n������, �����, �����, ��� � �������� ��������(����� ������): ");
	scanf_s("%s %s %s %s %s", &trudyaschiysya.dom_address[0], N - 1,
		&trudyaschiysya.dom_address[1], N - 1,
		&trudyaschiysya.dom_address[2], N - 1,
		&trudyaschiysya.dom_address[3], N - 1,
		&trudyaschiysya.dom_address[4], N - 1);
	do {
		printf("������� ���� �������� ��������\
			\n���, �����, �����(�������� 2003.12.4): ");
		scanf_s("%d.%d.%d", &trudyaschiysya.data[0], &trudyaschiysya.data[1], & trudyaschiysya.data[2]);
		if (trudyaschiysya.data[0] >= 0 && trudyaschiysya.data[1] >= 1 && trudyaschiysya.data[1] <= 12 && trudyaschiysya.data[2] >= 1 && trudyaschiysya.data[2] <= 31)
			break;
		puts("������� ���������� ������!");
	} while (1);
	
	do {
		printf("������� ����� ���� ��������: ");
		scanf_s("%d", &trudyaschiysya.numCeh);
		if (trudyaschiysya.numCeh >= 1)
			break;
		puts("������� ���������� ������! ������ ��� ����� 1!");
	} while (1);

	do {
		printf("������� ��������� ����� ��������: ");
		scanf_s("%d", &trudyaschiysya.tabl_num);
		if (trudyaschiysya.tabl_num >= 1)
			break;
		puts("������� ���������� ������! ������ ��� ����� 1!");
	} while (1);

	printf("������� ����������� ��������: ");
	scanf_s("%s", &trudyaschiysya.osvita, N - 1);
	
	do {
		printf("������� ��� ������� ��������: ");
		scanf_s("%d", &trudyaschiysya.god_priyoma);
		if (trudyaschiysya.god_priyoma >= trudyaschiysya.data[0] + 16)
			break;
		puts("������� ���������� ������!");
	} while (1);

	return trudyaschiysya;
}
/* �������� ��������� � ������� ��� ����� ���������� */
void displayArray(Robochiy* massive, int dimension) {
	for (int i = 0; i < dimension; i++){
		displayRabochiy(massive[i]);
	}
}
/* ����������� ���������� ��� ��������� */
void displayRabochiy(Robochiy robochiy) {
	SLASH;
	printf("���: %s %s %s;", 
		robochiy.people[0], robochiy.people[1], robochiy.people[2]);
	printf("\n������ ����������: %s, �. %s, ��. %s, �. %s, ��. %s;", 
		robochiy.dom_address[0], robochiy.dom_address[1], robochiy.dom_address[2], robochiy.dom_address[3], robochiy.dom_address[4]);
	printf("\n���� ��������: %d.%d.%d;\t����� ����: %d;\t ��������� �����: %d;", 
		robochiy.data[0], robochiy.data[1], robochiy.data[2], robochiy.numCeh, robochiy.tabl_num);
	printf("\n�����������: %s;\t������ �� ������ � %d ����.\n",
		robochiy.osvita, robochiy.god_priyoma);
}
/* ���������� �������� */
void sortLastName(Robochiy* massive, int dimension) {
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].people[0], massive[j - 1].people[0]) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortName(Robochiy* massive, int dimension) {
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].people[1], massive[j - 1].people[1]) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortOtchestvo(Robochiy* massive, int dimension) {
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].people[2], massive[j - 1].people[2]) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortAddressNumHouse(Robochiy* massive, int dimension) {
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--) {
			if (strcmp(massive[j].dom_address[3], massive[j - 1].dom_address[3]) < 0)
			{
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
		}
}
void sortAddressDom(Robochiy* massive, int dimension){
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--) {
			if (strcmp(massive[j].dom_address[3], massive[j - 1].dom_address[3]) < 0)
			{
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
			else if (strcmp(massive[j].dom_address[3], massive[j - 1].dom_address[3]) == 0)
				sortAddressNumHouse(massive, dimension);
		}
}
void sortAddressVulica(Robochiy* massive, int dimension)
{
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--) {
			if (strcmp(massive[j].dom_address[2], massive[j - 1].dom_address[2]) < 0)
			{
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
			else if (strcmp(massive[j].dom_address[2], massive[j - 1].dom_address[2]) == 0)
				sortAddressDom(massive, dimension);
		}
}
void sortAddressTown(Robochiy* massive, int dimension)
{
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--) {
			if (strcmp(massive[j].dom_address[1], massive[j - 1].dom_address[1]) < 0)
			{
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
			else if (strcmp(massive[j].dom_address[1], massive[j - 1].dom_address[1]) == 0)
				sortAddressVulica(massive, dimension);
		}
}
void sortAddressCountry(Robochiy* massive, int dimension)
{
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--) {
			if (strcmp(massive[j].dom_address[0], massive[j - 1].dom_address[0]) < 0) {
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
			else if (strcmp(massive[j].dom_address[0], massive[j - 1].dom_address[0]) == 0)
				sortAddressTown(massive, dimension);
		}
}
void sortDate(Robochiy* massive, int dimension) {
	float dney1, dney2, dney_v_godu = 365.25f, dney_v_mesyace = 29.3f;
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--) {
			dney1 = (float) (massive[j].data[0] - 1) * dney_v_godu + (massive[j].data[1] - 1) * dney_v_mesyace + massive[j].data[2];
			dney2 = (float) (massive[j - 1].data[0] - 1) * dney_v_godu + (massive[j - 1].data[1] - 1) * dney_v_mesyace + massive[j - 1].data[2];
			if (dney1 < dney2) {
				temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
			}
		}
}
void sortNumCeh(Robochiy* massive, int dimension){
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (massive[j].numCeh < massive[j - 1].numCeh)
			{
				temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
			}
}
void sortTableNum(Robochiy* massive, int dimension) {
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (massive[j].tabl_num < massive[j - 1].tabl_num)
			{
				temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
			}
}
void sortOsvita(Robochiy* massive, int dimension)
{
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (strcmp(massive[j].osvita, massive[j - 1].osvita) < 0)
			{
				temp = massive[j];
				massive[j] = massive[j - 1];
				massive[j - 1] = temp;
			}
}
void sortYearAccept(Robochiy* massive, int dimension) {
	Robochiy temp;
	for (int i = 0; i <= dimension; i++)
		for (int j = dimension - 1; j > i; j--)
			if (massive[j].god_priyoma < massive[j - 1].god_priyoma)
			{
				temp = massive[j - 1];
				massive[j - 1] = massive[j];
				massive[j] = temp;
			}
}
void sortMenu(Robochiy* massive, int dimension) {
	int menu = 0;
	SLASH;
	do {
	printf("	���� ����������:\
			\n1.����������� �� �������;\
			\n2.����������� �� �����;\
			\n3.����������� �� ��������;\
			\n4.C���������� �� ������;\
			\n5.����������� �� ���� ��������;\
			\n6.����������� �� ������ ����;\
			\n7.����������� �� ���������� ������;\
			\n8.����������� �� �����������;\
			\n9.C���������� �� ���� �������� �� ������;\
			\n0.Exit\
			\n��� �����:");
	scanf_s("%d", &menu);
	if (menu == 0)
		break;
	else if (menu == 1)
		sortLastName(massive, dimension);
	else if (menu == 2)
		sortName(massive, dimension);
	else if (menu == 3)
		sortOtchestvo(massive, dimension);
	else if (menu == 4)
		sortAddressCountry(massive, dimension);
	else if (menu == 5)
		sortDate(massive, dimension);
	else if (menu == 6)
		sortNumCeh(massive, dimension);
	else if (menu == 7)
		sortTableNum(massive, dimension);
	else if (menu == 8)
		sortOsvita(massive, dimension);
	else if (menu == 9)
		sortYearAccept(massive, dimension);
	} while (1);
	
}

// ����� �������� 
int displayChoiseFamilia(Robochiy* massive, int dimension, int i, char* foundLastName)
{
	if (massive[i].people[0][0] == foundLastName[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].people[0][j] == '\0' && foundLastName[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].people[0][j] != foundLastName[j])
				return 0;
		}
	else return 0;
}
int displayChoiseImya(Robochiy* massive, int dimension, int i, char* foundName)
{
	if (massive[i].people[1][0] == foundName[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].people[1][j] == '\0' && foundName[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].people[1][j] != foundName[j])
				return 0;
		}
	else return 0;
}
int displayChoiseOtchestvo(Robochiy* massive, int dimension, int i, char* foundOtchestvo)
{
	if (massive[i].people[2][0] == foundOtchestvo[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].people[2][j] == '\0' && foundOtchestvo[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].people[2][j] != foundOtchestvo[j])
				return 0;
		}
	else return 0;
}
int displayChoiseAddressCountry(Robochiy* massive, int dimension, int i, char* foundCountry)
{
	if (massive[i].dom_address[0][0] == foundCountry[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].dom_address[0][j] == '\0' && foundCountry[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].dom_address[0][j] != foundCountry[j])
				return 0;
		}
	else return 0;
}
int displayChoiseAddressTown(Robochiy* massive, int dimension, int i, char* foundTown)
{
	if (massive[i].dom_address[1][0] == foundTown[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].dom_address[1][j] == '\0' && foundTown[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].dom_address[1][j] != foundTown[j])
				return 0;
		}
	else return 0;
}
int displayChoiseAddressVulica(Robochiy* massive, int dimension, int i, char* foundUlica)
{
	if (massive[i].dom_address[2][0] == foundUlica[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].dom_address[2][j] == '\0' && foundUlica[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].dom_address[2][j] != foundUlica[j])
				return 0;
		}
	else return 0;
}
int displayChoiseAddressHouse(Robochiy* massive, int dimension, int i, char* foundHouse)
{
	if (massive[i].dom_address[3][0] == foundHouse[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].dom_address[3][j] == '\0' && foundHouse[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].dom_address[3][j] != foundHouse[j])
				return 0;
		}
	else return 0;
}
int displayChoiseAddressKvartira(Robochiy* massive, int dimension, int i, char* foundKvartira)
{
	if (massive[i].dom_address[4][0] == foundKvartira[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].dom_address[4][j] == '\0' && foundKvartira[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].dom_address[4][j] != foundKvartira[j])
				return 0;
		}
	else return 0;
}
int displayChoiseOsvita(Robochiy* massive, int dimension, int i, char* foundOsvita)
{
	if (massive[i].osvita[0] == foundOsvita[0])
		for (int j = 0; j < N; j++)
		{
			if (massive[i].osvita[j] == '\0' && foundOsvita[j] == '\0')//
			{
				return 1;
			}
			else if (massive[i].osvita[j] != foundOsvita[j])
				return 0;
		}
	else return 0;
}
void displayChoise(Robochiy* massive, int dimension)
{
	SLASH;
	//�����; ����� (�������, ���); �� �������; �����������; ����������; ����.
	int sort_vibor[E + 1] = { 0 }, o_1 = 0, o_2 = 0, o_3 = 0, o_4 = 0, o_5 = 0, o_6 = 0, o_7 = 0, o_8 =0, o_9=0, o_10 =0, o_11 = 0, o_12 = 0, o_13 = 0;
	printf("\n�������� ������ ������:\
			\n1.���;			\t2.�������;			\t3.��������;	\
			\n4.������;		\t5.�����;			\t6.�����;\
			\n7.���;			\t8.��������;			\t9.���� ��������;\
			\n10.����� ����;		\t11.��������� �����;		\t12.�����������;\
			\n13.�� ���� �������� �� ������;\t0.�����;\
			\n��� �����: ");
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
		else if (sort_vibor[i] == 7)
			o_7 = 1;
		else if (sort_vibor[i] == 8)
			o_8 = 1;
		else if (sort_vibor[i] == 9)
			o_9 = 1;
		else if (sort_vibor[i] == 10)
			o_10 = 1;
		else if (sort_vibor[i] == 11)
			o_11 = 1;
		else if (sort_vibor[i] == 12)
			o_12 = 1;
		else if (sort_vibor[i] == 13)
			o_13 = 1;
	}
	//����� �� ���� �����
	char foundName[N] = { 0 }, foundLastName[N] = { 0 }, foundOtchestvo[N] = { 0 }, foundOsvita[N] = { 0 };
	char foundCountry[N] = { 0 }, foundTown[N] = { 0 }, foundUlica[N] = { 0 }, foundHouse[N] = { 0 }, foundKvartira[N] = { 0 };
	int lowDen = 0, upperDen = 0, lowMesyac = 0, upperMesyac = 0, lowYear = 0, upperYear = 0;
	float dney = 0, lowDney = 0, upperDney = 0, dney_v_godu = 365.25f, dney_v_mesyace = 29.3f;
	int lowNumCeh = 0, upperNumCeh = 0, lowTableNum = 0, upperTableNum = 0, lowAcceptToJop = 0, upperAcceptToJop = 0;
	for (int i = 0; i < E; i++) {
		if (o_1 == 1) {
			printf("\n��� ������ �� ����� ������� ���: ");
			scanf_s("%s", foundName, N);
			//puts(foundName, N);
			o_1 = 2;
		}
		else if (o_2 == 1) {
			printf("\n��� ������ �� ������� ������� ���: ");
			scanf_s("%s", foundLastName, N);
			//puts(foundLastName, N);
			o_2 = 2 ;
		}
		else if (o_3 == 1) {
			printf("\n��� ������ �� �������� ������� ���: ");
			scanf_s("%s", foundOtchestvo, N);
			
			o_3 = 2;
		}
		else if (o_4 == 1) {
			printf("\n��� ������ �� ������ ������� ��: ");
			scanf_s("%s", foundCountry, N);
			//puts(foundCountry, N);
			o_4 = 2;
		}
		else if (o_5 == 1) {
			printf("\n��� ������ �� ������ ������� ��: ");
			scanf_s("%s", foundTown, N);
			//puts(foundTown, N);
			/*printf("\n��� ������ �� ������������� ������� �� ������ �����������: ");
			scanf_s("%g", &lowSebestoimost);
			printf("\n��� ������ �� ������������� ������� �� ������� �����������: ");
			scanf_s("%g", &upperSebestoimost);*/
			o_5 = 2;
		}
		else if (o_6 == 1) {
			printf("\n��� ������ �� ����� ������� ��: ");
			scanf_s("%s", foundUlica, N);
			//puts(foundUlica, N);
			/*printf("\n��� ������ �� ���� ������� �� ������ �����������: ");
			scanf_s("%g", &lowCena);
			printf("\n��� ������ �� ���� ������� �� ������� �����������: ");
			scanf_s("%g", &upperCena);*/
			o_6 = 2;
		}
		else if (o_7 == 1) {
			printf("\n��� ������ �� ���� ������� ��: ");
			scanf_s("%s", foundHouse, N);
			//puts(foundHouse, N);
			o_7 = 2;
		}
		else if (o_8 == 1) {
			printf("\n��� ������ �� �������� ������� ��: ");
			scanf_s("%s", foundKvartira, N);
			//puts(foundKvartira, N);
			o_8 = 2;
		}
		else if (o_9 == 1) {
			printf("\n��� ������ �� ���� ������� �� ������ �����������(�������� 04.10.2000): ");
			scanf_s("%d.%d.%d", &lowDen, &lowMesyac, &lowYear);
			printf("\n��� ������ �� ���� ������� �� ������� �����������(�������� 20.09.2023): ");
			scanf_s("%d.%d.%d", &upperDen, &upperMesyac, &upperYear);
			upperDney = (float)(upperYear - 1) * dney_v_godu + (upperMesyac - 1) * dney_v_mesyace + upperDen;
			lowDney = (float)(lowYear - 1) * dney_v_godu + (lowMesyac - 1) * dney_v_mesyace + lowDen;
			dney =  (float)(massive[i].data[0] - 1) * dney_v_godu + (massive[i].data[1] - 1) * dney_v_mesyace + massive[i].data[2];
			o_9 = 2;
			//printf("low = %d.%d.%d		upper = %d.%d.%d", lowDen, lowMesyac, lowYear, upperDen, upperMesyac, upperYear);
		}
		else if (o_10 == 1) {
			printf("\n��� ������ �� ������ ���� ������� ��� ������ �����������: ");
			scanf_s("%d", &lowNumCeh);
			printf("\n��� ������ �� ������ ���� ������� ��� ������� �����������: ");
			scanf_s("%d", &upperNumCeh);
			o_10 = 2;
		}
		else if (o_11 == 1) {
			printf("\n��� ������ �� ���������� ������ ������� ��� ������ �����������: ");
			scanf_s("%d", &lowTableNum);
			printf("\n��� ������ �� ���������� ������ ������� ��� ������� �����������: ");
			scanf_s("%d", &upperTableNum);
			o_11 = 2;
		}
		else if (o_12 == 1) {
			printf("\n��� ������ �� ������� ������� ���: ");
			scanf_s("%s", foundOsvita, N);
			//puts(foundOsvita, N);
			o_12 = 2;
		}
		else if (o_13 == 1) {
			printf("\n��� ������ �� ���� �������� �� ������ ������� ��� ������ �����������: ");
			scanf_s("%d", &lowAcceptToJop);
			printf("\n��� ������ �� ���� �������� �� ������ ������� ��� ������� �����������: ");
			scanf_s("%d", &upperAcceptToJop);
			o_13 = 2;
		}
	}

	int  kostil = 1, erorr = 0;
	for (int i = 0, right = 1; i < dimension; i++, right = 1)
	{
		switch (kostil)
		{
		case 1: 
			if (o_1 == 2) right = displayChoiseImya(massive, dimension, i, foundName);
		case 2: 
			if (o_2 == 2) right = displayChoiseFamilia(massive, dimension, i, foundLastName);
		case 3:	
			if (o_3 == 2) right = displayChoiseOtchestvo(massive, dimension, i, foundOtchestvo);
		case 4: 
			if (o_4 == 2) right = displayChoiseAddressCountry(massive, dimension, i, foundCountry);
		case 5:	
			if (o_5 == 2) right = displayChoiseAddressTown(massive, dimension, i, foundTown);
		case 6:	
			if (o_6 == 2) right = displayChoiseAddressVulica(massive, dimension, i, foundUlica);
		case 7:	
			if (o_7 == 2) right = displayChoiseAddressHouse(massive, dimension, i, foundHouse);
		case 8:	
			if (o_8 == 2) right = displayChoiseAddressKvartira(massive, dimension, i, foundKvartira);
		case 9: {
			if (o_9 == 2)if (massive[i].data[0] *365+massive[i].data[1] * 30 + massive[i].data[2] <= upperYear *365 + upperMesyac * 30 + upperDen && massive[i].data[0] * 365 + massive[i].data[1] * 30 + massive[i].data[2] >= lowYear * 365 + lowMesyac * 30 + lowDen)
				right = 1;
			else right = 0;
		}
		case 10: 
			if (o_10 == 2) 
				if (massive[i].numCeh <= upperNumCeh && massive[i].numCeh >= lowNumCeh) 
				{right = 1;} 
				else right = 0;
		case 11:
			if (o_11 == 2) 
				if (massive[i].tabl_num <= upperTableNum && massive[i].tabl_num >= lowTableNum)
				{ right = 1; }
				else right = 0;
		case 12: 
			if (o_12 == 2)  right = displayChoiseOsvita(massive, dimension, i, foundOsvita);
		case 13: 
			if (o_13 == 2) 
				if (massive[i].god_priyoma <= upperAcceptToJop && massive[i].god_priyoma >= lowAcceptToJop)
				{ right = 1; }
				else right = 0;
		case 14: 
		{
			if (erorr == 0 && (i == dimension - 1) && right == 0) {
				SLASH;
				puts("\n� ���������, �� ������ �� �����(");
			}
				
			if (right == 0)
				break;
			displayRabochiy(massive[i]);
			erorr++;
		}
		}
	}
}

int main(void) 
{
setlocale(LC_ALL, "Rus");

int dimension, choose = 0, sort_vibor = 0;
Robochiy* massiveStruct;
SLASH;
printf("������� ���������� ����� �������: ");
scanf_s("%d", &dimension);
if (dimension <=0) {
	printf("�� �� ����� ������� %d �������. ����� ���������.", dimension);
	return 0;
}
massiveStruct = initArray(dimension);
if (massiveStruct == NULL) {
	printf("������ ��������...\n");
	printf("�� ���������...");
}
SLASH;
printf("\n������ �������: \n");
displayArray(massiveStruct, dimension);
do {
	SLASH;
	printf("\n	����\
			\n1.����������;\
			\n2.�����;\
			\n3.�����;\
			\n0.Exit;\
			\n��� �����: ");
	scanf_s("%d", &choose);
	if (choose == 0)
		break;
	else if (choose == 1)
		sortMenu(massiveStruct, dimension);
	else if (choose == 2)
		displayChoise(massiveStruct, dimension);
	else if (choose == 3){
		printf("\n������ �������: \n");
		displayArray(massiveStruct, dimension);
	}
} while (1);
free(massiveStruct);
printf("\n����� ����� �����...\n");
return 0;
}