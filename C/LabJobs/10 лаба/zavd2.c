#include "source.h"
void zavdannya2()
{
	
	int chto = 0;
	do {
	SLASH;
	printf("����� ������� ��� ����� ���������?\n\
	��� ����� - ������� 1\n\
	��� �������������� - ������� 2\n\
	��� ������ - ������� 3\n\
	��� ������ �� ��������� - ������� 0.\n");
	scanf_s("%d", &chto);

	if (chto == 0)
		break;
	else if (chto == 1)
		s_krug();
	else if (chto == 2)
		s_pryamougolnik();
	else if (chto == 3)
		v_prizm();
	else;

	} while (1);
}
int s_krug()
{
	SLASH;
	double s = 0, r = 0;

	printf("������� ������ ��� ���������� ������� �����\n");
	scanf_s("%lg", &r);

	printf("S = Pi x r ^ 2\nS = %lg x %lg ^ 2 = %lg\n", PI, r, KRUG(r));
	return 0;
}
int s_pryamougolnik()
{
	SLASH;
	int a = 0, b = 0;

	printf("������� ��� ������ ��� ���������� ������� ��������������\n");
	printf("a = "); 
	scanf_s("%d", &a);
	printf("b = ");
	scanf_s("%d", &b);

	printf("S = a x b\nS = %d x %d = %d\n", a, b, PRYAMOUGOLNIK(a,b));
	return 0;
}
int v_prizm()
{
	SLASH;
	int a = 0, b = 0, h = 0;

	printf("������� ��� ������ � ������ ��� ���������� ������ ������������� ������\n");
	printf("a = ");
	scanf_s("%d", &a);
	printf("b = ");
	scanf_s("%d", &b);
	printf("h = ");
	scanf_s("%d", &h);

	printf("V = S x h\nS = a x b\nV = a x b x h\nS = %d x %d x %d = %d\n", a, b, h, PRIZMA(a,b,h));
	return 0;
}