#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <windows.h>
#define N 50

//�������� �����
int checkFile(char fileName[]) {
	FILE* data;
	char temp[3] = {0};
	fopen_s(&data,fileName, "rb+");
	if (!data) {
		printf("���� �� �i�������!\n");
		return 1;
	}
	else {
		if (fgets(temp, 2, data) == NULL) {
			fclose(data);
			printf("���� �� ������� �������.\n������� � ����i �� �� �����!\n");
			return 1;
		}
		fclose(data);
	}
	return 0;
}

//ʳ������ �����
int fileSize(char fileName[]) {
	int counter = 0;
	FILE* data;
	fopen_s(&data, fileName, "r");
	while (!feof(data)) {
		if (fgetc(data) == '\n')
			counter++;
	}
	counter++;
	fclose(data);
	return counter;
}

//����� ������ � ����
void writeToFile(char** arr, int size, char fileName[]) {
	FILE* data;
	fopen_s(&data, fileName, "w");
	for (int i = 0; i < size; i++)
		if (size - i == 1) 
			fprintf(data, "%s", arr[i]);
		else fprintf(data, "%s\n", arr[i]);
	fclose(data);
}

//����������� ������
void initArr(char inName[], int size, char **arr) {
	char str[N] = {0};
	FILE* data;
	fopen_s(&data, inName, "r");

	//��������� ����� � ��������� �����
	for (int i = 0; i < size; i++) {
		fgets(str, N, data);
		if (strstr(str, "\n")) {
			str[strlen(str) - 1] = '\0';
		}
		strcpy(arr[i], str);
	}
	fclose(data);
}

//������� ���������
void codeOrDecode(char inName[], char outName[], int choose) {
	int size = fileSize(inName);

	char** arr = (char**)malloc(size * sizeof(char*));
	for (int i = 0; i < size; i++)
		arr[i] = (char*)malloc(N * sizeof(char));

	//initArr(inName, size, arr);

	//���� ���������/����������� �������
	for (int i = 0; i < size; i++) {
		printf("%s ->", arr[i]);
		for (int j = 0; j < strlen(arr[i]); j++) {
			unsigned char x;
			x = arr[i][j];
			x = (x << 7) | (x >> 7) | (x & 0x7E);
			arr[i][j] = x;
		}
		printf(" %s\n", arr[i]);
	}

	writeToFile(arr, size, outName); //����� � ����
	free(arr); //��������� ���'��
}

//������� ������� ��������
void main(int argc, char* argv[]) {
	//Kur_18_3.exe data.txt out.txt
	setlocale(LC_ALL, ""); //����������
	int choice, error = 0;
	char in[N] = { 0 }, out[N] = { 0 };
	if (argc == 2 || argc == 3) {
		if (argc == 2) {
		printf("���� �� ��� ������� ����� ��������� ��� �������!\n");
		error = 1;
		}
		if (argc == 3 && error == 0) {
			error = checkFile(argv[1]);
			memcpy(in, argv[1], N);
			if (error == 0) {
				error = checkFile(argv[2]);
				memcpy(out, argv[2], N);
			}	
		}
	}
	else {
		printf("������� � �������� ����� �� ���� �������� ����� ��������� ��� �������!\n");
		error = 1;
	}
	//���� ���������/�����������
	if (error == 0) {
		do {
			printf("� ����� '%s' �� '%s'\n�����i�� �i�:\n1-���������\n2-�����������\n�����i�� �i�: ", in, out);
			scanf_s("%d", &choice);
		} while (choice != 1 && choice != 2);
		codeOrDecode(in, out, choice);
	}
	system("pause"); //���� �������
}
/*
* ������������ ��� ��������� 3-�� ��������:
1.	��� ������� �� �������� ����-���� ����� ��������� ��������� �������� ������� ��������-���������.
2.	��������� ��������� �������� �� ������ ������� ���� ������������� � ������ ����. ���������, ��������� ������� �������� ��� �� ������� 57894 � 2 ����� ����������� ��������� �����:
	57894 = 11100010 00100110
&		2 = 00000000 00000010
���������:       	2 = 00000000 00000010

18.	������� ��������,
�� ���� ��������� ���������� ������������ ������� �� ���������� ��� � ����. 
����������� ��������� �����������. ��� ��������� ������� ������� �������.
*/