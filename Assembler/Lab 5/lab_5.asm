format PE console
entry main

;include 'win32a.inc'

section '.data' data readable writeable
    srcArray dd 1.0, 2.0, 3.0, 4.0, 5.0 ; ���������� �����
    dstArray dd 0.0, 0.0, 0.0, 0.0, 0.0 ; ����� �����������
    arraySize dd 5 ; ʳ������ �������� � �����

section '.text' code readable executable
main:
    push ebp
    mov ebp, esp

    ; ����������� ������ ����������� �� ������������ ������
    mov esi, srcArray
    mov edi, dstArray

    ; ����������� ������� �������� � �����
    mov ecx, [arraySize]

copyLoop:
    ; ������� �������� �������� � ����������� ������ �� ������������
    mov eax, [esi]
    mov [edi], eax

    ; �������� ��������� �� ��������� ������� � �������
    add esi, 4
    add edi, 4

    ; �������� ��������
    loop copyLoop

    ; ����� � ��������

  mov     eax, 0x1
  mov     ebx, 0
  int     0x80



