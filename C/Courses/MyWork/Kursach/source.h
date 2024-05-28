#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define SLASH puts("///////////////////////////////////////")
#define TIRE puts("---------------------------------------------------------------------------------------")
#define N 30
#define E 7
#define ERROR printf("���� �� ��� ������!\n"); exit(1)
/*
������� ��������.

//� ����������:
//+������ �����
//+����� �����
//+�����, �� ����� �������� ��������� ������ ����(����������, �������, �������, ������� ����)
//+����, �� ����� �����
//+�� ����������� ����� �����.
//+���� ����� ���� ������ ��������, �� ��� ����������� ����, �� ���� ������� ������� ������������.


//��� ��������� ���� ��� ����������� �� ���������� �� ������� ;
//- �� �������� ������
//-�� ������ �����.


//����� ��� ����������
//-�� �������� ������
//-������ ����� (� ���� ��� � �� �������� �������)
//-�� �����.
//�������� ��������, ���� �� ��� ������ �� ��������� ������ ������ �� ��������.


����������� ��������, ���� �������� ����� ���� ��������� ��� ����� ��������� ��������.
*/
typedef struct {
	char autor[N];
	char nazva[N];
	char rozdil[N];
	int nomer_mesta;
	int vdoma;
	char prizvische_pozik[N];
} Book;