#include <stdio.h>
#include <locale.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#define N 100
int strlen_my(char *massive) {
	for (int i = 0; ; i++)
		if (*(massive + i) == '\0')
			return i;
}
void SetColor(int nomer_change) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | nomer_change));
}
void word(char *str, int n, int l) {
    for (int i = 0; i < strlen_my(str); i++) {
        if(i == n)
            SetColor(l);
        printf("%c", *(str + i));
    }
    SetColor(7);
}
void main() {
	setlocale(LC_ALL, "Rus"); //����

    char str[N] = {0};
	int error = 1, n = 0, l = 0;
    
    do {
    printf("������� ����������� ��� ��� �������: ");
    gets(str, N - 1);
    } while (!(str[0] != '\0'));
	
    do {
    printf("������� ����� �������, � ������ ���������� �������: ");
    scanf_s("%d", &n);
    } while (!(n > 0 && n <= strlen_my(str)));
    
    do {
        printf("������� ����� �����: ");
        scanf_s("%d", &l);
    } while (!(l > 0));
    
    printf("����� ����������: "); 
    word(str, n, l);
}
/*
1.	����� ��� ���������� ������� ������� � ������� ������� � ���������.
2.	����������� ������� ������� � ������� ��������� �� ������� �������.
3.	��������� ��� ������� ������ ������� � �������������:
�) ������������ ������;
�) ���������.
15.	 ������� word(s, n, l)
�����������: ������ �������� l ��� � ����� s, ��������� � ����� � ������� n.


*/