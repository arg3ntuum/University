#include "source.h"
/*
��������� ��������
ϳ� ��� ��������� ������ ����������� �������� �������:
+�������� ������, � ����� � ������� ������ ������ ����������� �������� � 1 �� � 2;
+�������� ������� ���������� ����, ���������� � ����� ������ ��������������� ���� ����� �������;
+�� ��� ���������� �������� � 1 ��� ��������������� ����� � �������������� static (��� ������������ ������);
+�� ��� ���������� �������� � 2 ��� ��������������� ��������������� �� ��������� ���������.
������ � 1
�������� 1. �������� ������� ����������� �������� ����� �����, ������������ ��������.
�������� 2. ������� ����� ����� �� ������������, � ����� �ᒺ� ���������� ������.
*/
void main () 
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int vibor = 0;
	do 
	{
		SLASH;
		printf_s("����� ������� ������ ���������?(1 or 2)\n����� 0.\n");
		scanf_s("%d", &vibor);
		
		if (vibor == 0)
			break;
		else if (vibor == 1)
			zavdannya1();
		else if (vibor == 2)
			zavdannya2();
		else;
	} 
	while (1);

	for (int o = 0;o < 50;o++)
		printf_s("���������� ������. ");
	puts("");
}