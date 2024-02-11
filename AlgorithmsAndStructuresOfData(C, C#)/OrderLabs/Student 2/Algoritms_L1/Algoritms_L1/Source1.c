#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "Source1.h"
#pragma GCC ignored -Wall
#define K 50
#define SIZE 6
void inputMatrixChar(char** massive, int N) {
    char temp[K];
    int pomilka = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            do {
                pomilka = 0;
                printf("�atrix[%d][%d] = ", i, j);
                scanf_s("%s", &temp, K - 1);
                for (int a = 0; a < strlen(temp); a++)
                    if (atoi(temp) == 0 && !(('0' <= temp[a]) && (temp[a] <= '9')))
                        pomilka = 1;
                if (pomilka == 1)
                    printf("������� ������ �����!\n");
                else {
                    massive[i][j] = temp;
                    break;
                }
            } while (1);
        }
}
void matrixOutPutChar(char** massive, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%4d", massive[i][j]);
        puts("");
    }
}
void MatrixFOutPut(float  massive_float[6])
{
    for (int i = 0; i < SIZE; i++)
        printf("%d. %3.3f\n", i, massive_float[i]);
}
int main()
{
    setlocale(LC_ALL, "Rus"); //����

    float massive_float[SIZE] = { 1.5, 2.2 ,3.9 ,4.0 ,5.5, 6.1 };
    float* ptr_massive_float;

    static char matrix_char[K] = "words";
    char* pointer_matrix_char;

    int matrix_3[2][3][2];
    int** matrix_3point;

    puts("\n2.1");
    MatrixFOutPut(massive_float);

    puts("\n2.2");
    puts("\n������� ������ �����: ");
    for (int i = 0; i < SIZE; i++) {
        printf("massive[%d] = ", i);
        scanf_s("%f", &massive_float[i]);
    }

    puts("\n2.3");
    MatrixFOutPut(massive_float);

    puts("\n2.4");
    ptr_massive_float = massive_float;
    printf("������ ��������� - %p\n", ptr_massive_float);
    printf("������ ������� - %p\n", massive_float);
    printf("���������� ���������: \n");
    MatrixFOutPut(ptr_massive_float);
     
    puts("\n2.5");
    for (int i = 0; i < SIZE; i++)
        printf("%d. %f\n", i, *(ptr_massive_float + i));


    puts("\n2.6");
    printf("\n������ �������� �����: ");
    puts(matrix_char);

    puts("\n������� ����� ��� ������ � ������: ");
    getchar();
    gets_s(matrix_char, K);

    printf("\n������ char �����: %s", matrix_char);

    puts("\n2.7");
    int size = K;
    pointer_matrix_char = (char*)malloc(size * sizeof(char));

    printf("������� ������ char: ");
    gets_s(pointer_matrix_char, size);


    puts("\n��������� ������: ");
    puts(pointer_matrix_char);

    puts("\n2.8");
    free(pointer_matrix_char);

    int N = 2;
    char** matrix_2d = (char**)malloc(N * sizeof(char*));
    for (int i = 0; i < N; i++)
        matrix_2d[i] = (char*)malloc(K * sizeof(char));
    printf("\n\n������� ����� ����� ��� ������ � ������(�� %d ����)(end ��� ����� �����): ", K);
    for(int i = 0; i < N; i++)
        gets_s(matrix_2d[i], K);
    puts("��������� �����: ");
    for (int i = 0; i < N; i++)
        puts(matrix_2d[i], K);

    free(matrix_2d);

    puts("\n2.9");
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 2; k++)
                matrix_3[i][j][k] = (int)i + j + k;
    printf("������� ����������� ������� �� �������: %d", matrix_3[1][2][1]);

    puts("\n2.10");
    printf("������� ����������� ������� �� ���������: %d", *(*(*(matrix_3 + 1) + 2) + 1));

    puts("\n2.11");
    matrix_3point = &matrix_3[1][2][1];
    printf("������� ����������� ������� �� ��������� ����� ���������: %d", *matrix_3point);
}