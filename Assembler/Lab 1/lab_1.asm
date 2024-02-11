format PE console
entry main
include 'win32a.inc'

section '.data' data readable writeable
    num1    dd 5    ; ����� �����
    num2    dd 3    ; ����� �����
     strOf db "Overflow flag (OF) is set.", 0
     strCr db "Carry flag (CF) is set.", 0
     strZr db "Zero flag (ZF) is set." , 0
     strRs db  "Result: ", 0

section '.code' code readable executable
main:
    mov     eax, [num1]  ; ����������� ����� ����� � eax
    sub     eax, [num2]  ; ³����� ����� ����� �� �������

    ; ���������� ������� ������������, �������� �� ��������� ����������
    jo      overflow     ; �������� OF
    jc      carry        ; �������� CF
    jz      zero         ; �������� ZF

        ; ���� ����� � ������� �� �����������, ������� ���������
        ; push strRs
        ; push eax
        ; call [printf]
    jmp exit

overflow:
        ;  push  strOf
        ;  call [printf]
    jmp exit

carry:
        ;push  strCr
        ; call [printf]
    jmp exit

zero:
        ;push  strZr
        ;call [printf]
    jmp exit

exit:
     call [getch]

    invoke  ExitProcess, 0

section '.idata' import data readable
         library kernel, 'kernel32.dll',\
                 msvcrt, 'msvcrt.dll'

         import kernel,\
                ExitProcess, 'ExitProcess'

         import msvcrt,\
                printf, 'printf',\
                scanf, 'scanf',\
                getch, '_getch'