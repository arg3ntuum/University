format PE console
entry start

section '.data' data readable writeable
    n dd 4     ; ������ �������� n (���������� �����)
    sum dd 0    ; �������������� ���������� ��� �������� �����
    i dd 1      ; �������������� ���������� ��� �������� �������� ����� i

section '.code' code readable executable
start:
    mov ecx, [n]       ; ��������� n � ������� ecx
    mov ebx, 0         ; �������� ������� ebx ��� �������� �����
    mov esi, [i]       ; ��������� ��������� �������� i � ������� esi

    ; ���� ��� ���������� ����� ����� ����������� �����
    sum_loop:
        ; ���������� ���� �������� ����� � ���������� � �����
        mov eax, esi
        imul eax, eax     ; ������� �������� �����
        imul eax, esi     ; ��� �������� �����
        add ebx, eax

        inc esi           ; ���������� i

        loop sum_loop

    ; ��������� ��������� � �������� ebx (����� �����)
    mov [sum], ebx
    ; ������ � sum


    ; ���������� ���������
    mov     eax, 1
    xor     ebx, ebx
    int     0x80

;section '.idata' import data readable
;library kernel, 'kernel32.dll',\
;         msvcrt, 'msvcrt.dll'

;import kernel,\
;        ExitProcess, 'ExitProcess'

;import msvcrt,\
;        printf, 'printf'
