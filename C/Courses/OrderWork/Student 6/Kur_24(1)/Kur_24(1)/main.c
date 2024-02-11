#include <stdio.h>
#include <locale.h>
#define N 30
int strlenIndex(char massive[]){
	for (int i = 0; ; i++)
		if (massive[i] == '\0')
			return i;
}
int quantityIndex(char s[], char p[]) {
	int counter = 0, counter_P = strlenIndex(p);
	for (int i = 0; i < strlenIndex(s); i++) {
		if (s[i] == p[0])
			for (int j = 0, k = i;; j++, k++) {
				if (j == strlenIndex(p))
					counter++;
				if (s[k] != p[j])
					break;
			}
	}
	return counter;
}
int strlenVkazivnik(char *massive) {
	for (int i = 0; ; i++)
		if (*(massive + i ) == '\0')
			return i;
}
int quantityVkazivnik(char *s, char *p) {
	int counter = 0, counter_P = strlenVkazivnik(p);
	for (int i = 0; i < strlenVkazivnik(s); i++) {
		if (*(s + i) == *p)
			for (int j = 0, k = i;; j++, k++) {
				if (j == strlenVkazivnik(p))
					counter++;
				if (*(s + k) != *(p + j))
					break;
			}
	}
	return counter;
}
void main() {
	setlocale(LC_ALL, "Rus");
	int choose_function = 0;
	char s[N] = {0}, p[N] = { 0 };
	printf("����i�� ����� ��� ����i��: ");
	scanf_s("%s", s, N - 1);
	printf("����i�� �i������ ��� ����i��: ");
	scanf_s("%s", p, N - 1);
	system("cls");
	do {
		printf("�����i�� ���i��� �����i�:\n1.� i�������\n2.� ����i�������\n");
		scanf_s("%d", &choose_function);
		if (choose_function == 1 || choose_function == 2)
			break;
		else puts("����i�� ���������� ���i�!");
	} while (1);
	system("cls");
	if (quantityIndex(s, p) != 0) {
		if (choose_function == 1)
			printf("�i���i��� �������� � ����� '%s' �i������ '%s': %d", s, p, quantityIndex(s, p));
		else printf("�i���i��� �������� � ����� '%s' �i������ '%s': %d", s, p, quantityVkazivnik(s, p));
	}
	else printf("�i������ � ����� �� ��������.");
}

/*
* ��� �������� 1-�� �������� ���������:
1.	����� ��� ���������� ������� ������� � ������� ������� � ���������.
2.	����������� ������� ������� � ������� ��������� �� ������� �������.
3.	��������� ��� ������� ������ ������� � �������������:
�) ������������ ������;
�) ���������.
24.	 ������� quantity(s, p)
�����������: �������� ������� �������� ������� p � ����� s.
*/