#include <stdio.h>
#include <locale.h>
#define N 30
char codes(char element) {
	int nomer_element = (int)element;
	if (nomer_element >= 97 && nomer_element <= 121)
		nomer_element++;
	else if (nomer_element == 122)
		nomer_element = 97;
	else if(nomer_element >= 65 && nomer_element <= 89)
		nomer_element++;
	else if (nomer_element == 90)
		nomer_element = 65;
	else nomer_element = 42;
	char element_return = nomer_element;
	return element_return;
}
void coding(char *s) {
	for (int i = 0; *(s + i) != '\0'; i++)
		printf ("%c",codes(*(s + i)));
}
void main() {
	setlocale(LC_ALL, "Rus"); 

	char s[N] = {0};

	printf("������� ������: ");
	scanf_s("%s", s, N - 1);

	printf("�������������� ������: "); 
	coding(s);
}
/*
1.	����� ��� ���������� ������� ������� � ������� ������� � ���������.
2.	����������� ������� ������� � ������� ��������� �� ������� �������.
3.	��������� ��� ������� ������ ������� � �������������:
�) ������������ ������;
�) ���������.
20.	 ������� coding(s)
�����������: ���� ���������� ����� s �� ��������� ��������:
a -> b
b -> c
c -> d
...
z -> a
����� ������ -> *
���������, ����� qwerty234 ���� ��������� ������ ������: rxfsuz***

*/