//#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define N 50
#define S 3
//�������� � � �� b
void toAfromB(char a[], char b[]) {
	for (int i = 0; i < S; i++)
		a[i] = b[i];
}
//����� � �������� ����
void putsBinaryCode(int number)
{
	int i, mask = 1 << 15;

	for (i = 1; i <= 16; i++) {
		putchar(number & mask ? '1' : '0');
		number <<= 1;
		if (i % 4 == 0)
			putchar(' ');
	}
	puts("");
}
void pack_Char(char char1, char char2, char outName[])
{
	unsigned short int result;
	result = char1;
	printf("��������� � ��i������� ���i ������� %c: ", char1);
	putsBinaryCode(result);
	result <<= 8;
	printf("��������� � ��i������� ���i ������� %c: ", char2);
	putsBinaryCode(result);
	result |= char2;

	printf("��������� � ��i������� ���i: ");
	putsBinaryCode(result);
	printf("��������� � ����������� ���i: %d\n", result);
	

	putchar('\n');
	FILE* data;
	fopen_s(&data, outName, "w");
	if (!data) {
		puts("Failed to open file \n");
		exit(1);
	}
	fprintf(data, "%d ", &result);
	fclose(data);
}

void initArr(char inName[], char arr[]) {
	char str[S] = { 0 };
	FILE* data;
	fopen_s(&data, inName, "r");
	if (!data) {
		puts("Failed to open file \n");
		exit(1);
	}
	//��������� ����� � ��������� �����
	fscanf_s(data, "%s", str, S);//c������ � �����
	toAfromB(arr, str);//str �������� � arr
	fclose(data);//������� ����
}
int checkFile(char fileName[]) {
	FILE* data;
	char temp[3] = { 0 };
	fopen_s(&data, fileName, "rb+");
	if (!data) {
		printf("���� �� �i�������!\n");
		return 1;//������
	}
	else {
		if (fgets(temp, 2, data) == NULL) {//���� ������ �� �������
			fclose(data);
			printf("���� �� ������� �������.\n������� � ����i �� �� �����!\n");
			return 1;//������
		}
		fclose(data);
	}
	return 0;//��� ������
}
//������� ���������
void code(char inName[], char outName[]) {
	char arr[S] = {0};
	
	initArr(inName, arr);//������ � arr
	
	pack_Char(arr[0], arr[1], outName);//��������� + ������
	
	free(arr); //��������� ���'��
}
//������� �������
void main(int argc, char* argv[]) {
		setlocale(LC_ALL, "Rus"); //����������
		//Kur_24_3.exe data.txt out.txt
		int error = 0;
		char in[N] = "data.txt", out[N] = "out.txt";
		//if (argc == 2 || argc == 3) {//������� ���� ����������
		//	if (argc == 2) {//1 �������� = ������
		//		printf("���� �� ��� ������� ����� ��������� ��� �������!\n");
		//		error = 1;
		//	}
		//	if (argc == 3 && error == 0) {//���� 2 ���������, (data.txt and out.txt)
		//		error = checkFile(argv[1]);//��������� ���� �� ��������
		//		memcpy(in, argv[1], N);//���������� � argv[1] � in
		//		if (error == 0) {
		//			error = checkFile(argv[2]);//��������� ���� �� ��������
		//			memcpy(out, argv[2], N);//���������� � argv[2] � out
		//		}
		//	}
		//}
		//else {
		//	printf("������� � �������� ����� �� ���� �������� ����� ��������� ��� �������!\n");
		//	error = 1;
		//}
		if (error == 0)
			code(in, out);
		system("pause"); //���� �������
	
}
/*
* ������������ ��� ��������� 3-�� ��������:
1.	��� ������� �� �������� ����-���� ����� ��������� ��������� �������� ������� ��������-���������.
2.	��������� ��������� �������� �� ������ ������� ���� ������������� � ������ ����. 
���������, ��������� ������� �������� ��� �� ������� 57894 � 2 ����� ����������� ��������� �����:
	    57894 = 11100010 00100110
&			2 = 00000000 00000010
���������:  2 = 00000000 00000010
24.	
������� ��������, �� ������ ��� ������� � ��������� �� ������ �� ������� pack_char(),
��� ������� �� � ���� ����� ���� unsigned int. 
�������� ������� �������� �������� ������� �� ��������� � ����������� �� ��������� ������������.
*/